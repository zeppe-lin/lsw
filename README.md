OVERVIEW
========

This directory contains lsw, a tiny utility that prints the XID, class and
title of X windows to stdout.

This distribution is a fork of suckless' lsw as of release 0.3 (20141129) with
the following differences:

- lswmenu, a simple perl script which uses lsw, dmenu and wmctrl or xdotool or
  xdo to list windows, select and jump to the specified one
- minor cleanups, segfault fixes

See git log for complete/further differences.

The original sources can be downloaded from:
https://dl.suckless.org/tools/lsw-0.3.tar.gz


REQUIREMENTS
============

Build time
----------
- C99 compiler
- POSIX sh(1p), make(1p) and "mandatory utilities"
- libX11

Runtime
-------
- lswmenu requires Perl, dmenu(1), and one of the following:
  wmctrl(1) or xdotool(1) or xdo(1)


INSTALL
=======

The shell commands `make && make install` should build and install this
package.

See `config.mk` file for configuration parameters.


LICENSE
=======

lsw is licensed through MIT/X Consortium License.
See LICENSE file for copyright and license details.
