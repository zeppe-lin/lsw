# project metadata
NAME      = lsw
VERSION   = 0.3
DIST      = lsw-${VERSION}

# paths
PREFIX    = /usr/local
MANPREFIX = ${PREFIX}/share/man

# DragonFlyBSD, FreeBSD
#X11INC   = /usr/local/include
#X11LIB   = /usr/local/lib

# NetBSD, OpenBSD
#X11INC   = /usr/X11R6/include
#X11LIB   = /usr/X11R6/lib

# Linux
X11INC    = /usr/include
X11LIB    = /usr/lib

# includes and libs
INCS      = -I${X11INC}
LIBS      = -L${X11LIB} -lX11

# flags
CPPFLAGS  = -DVERSION=\"${VERSION}\"
CFLAGS    = -ansi -pedantic -Wall -Wextra -Wformat ${CPPFLAGS} ${INCS}
LDFLAGS   = ${LIBS}
