/* See LICENSE file for copyright and license details. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* libX11 */
#include <X11/Xlib.h>
#include <X11/Xutil.h>

/*
 * Function declarations.
 */

static const char *getclass(Window);
static const char *getname(Window);
static void lsw(Window);

/*
 * Global variables.
 */

static Atom netwmname;
static Display *dpy;

/*
 * Function implementations.
 */

const char *
getclass(Window win)
{
	static char buf[BUFSIZ];
	XClassHint xch;

	if (XGetClassHint(dpy, win, &xch)) {
		if (xch.res_class)
			strncpy(buf, xch.res_class, sizeof buf);

		XFree(xch.res_class);
		XFree(xch.res_name);
	}

	return buf;
}

const char *
getname(Window win)
{
	static char buf[BUFSIZ];
	char **list;
	int n;
	XTextProperty prop;

	if (!XGetTextProperty(dpy, win, &prop, netwmname) || prop.nitems == 0) {
		if (!XGetWMName(dpy, win, &prop) || prop.nitems == 0)
			return "";
	}

	if (!XmbTextPropertyToTextList(dpy, &prop, &list, &n) && n > 0) {
		strncpy(buf, list[0], sizeof buf);
		XFreeStringList(list);
	} else
		strncpy(buf, (char *)prop.value, sizeof buf);

	XFree(prop.value);
	buf[sizeof buf - 1] = '\0';
	return buf;
}

void
lsw(Window win)
{
	unsigned int n;
	Window *wins, *w, dw;
	XWindowAttributes wa;

	if (!XQueryTree(dpy, win, &dw, &dw, &wins, &n))
		return;  /* XQueryTree err */

	if (!wins)
		return;  /* no children wins */

	for (w = &wins[n - 1]; w >= &wins[0]; w--) {
		if (XGetWindowAttributes(dpy, *w, &wa) &&
		    !wa.override_redirect && wa.map_state == IsViewable)
			printf("0x%07lx %s - %s\n", *w, getclass(*w), getname(*w));
	}

	XFree(wins);
}

int
main(int argc, char *argv[])
{
	int i;

	if (!(dpy = XOpenDisplay(NULL))) {
		fprintf(stderr, "%s: cannot open display\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	netwmname = XInternAtom(dpy, "_NET_WM_NAME", False);

	if (argc < 2)
		lsw(DefaultRootWindow(dpy));
	else {
		for (i = 1; i < argc; i++)
			lsw(strtol(argv[i], NULL, 0));
	}

	XCloseDisplay(dpy);
	return EXIT_SUCCESS;
}

/* End of file. */
