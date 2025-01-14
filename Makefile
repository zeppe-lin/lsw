.POSIX:

include config.mk

all: lsw

install: all
	mkdir -p ${DESTDIR}${PREFIX}/bin
	mkdir -p ${DESTDIR}${MANPREFIX}/man1
	cp -f lsw lswmenu ${DESTDIR}${PREFIX}/bin/
	cp -f lsw.1 ${DESTDIR}${MANPREFIX}/man1/
	ln -sf lsw.1 ${DESTDIR}${MANPREFIX}/man1/lswmenu.1
	chmod 0755 ${DESTDIR}${PREFIX}/bin/lsw
	chmod 0755 ${DESTDIR}${PREFIX}/bin/lswmenu
	chmod 0644 ${DESTDIR}${MANPREFIX}/man1/lsw.1

uninstall:
	rm -f ${DESTDIR}${PREFIX}/bin/lsw
	rm -f ${DESTDIR}${PREFIX}/bin/lswmenu
	rm -f ${DESTDIR}${MANPREFIX}/man1/lsw.1
	rm -f ${DESTDIR}${MANPREFIX}/man1/lswmenu.1

clean:
	rm -f lsw
	rm -f ${DIST}.tar.gz

release:
	git tag -a v$(VERSION) -m v$(VERSION)

dist: clean
	git archive --format=tar.gz -o ${DIST}.tar.gz --prefix=${DIST}/ HEAD

.PHONY: all install uninstall clean release dist
