
Debian
====================
This directory contains files used to package c2fcoind/c2fcoin-qt
for Debian-based Linux systems. If you compile c2fcoind/c2fcoin-qt yourself, there are some useful files here.

## c2fcoin: URI support ##


c2fcoin-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install c2fcoin-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your c2fcoinqt binary to `/usr/bin`
and the `../../share/pixmaps/c2fcoin128.png` to `/usr/share/pixmaps`

c2fcoin-qt.protocol (KDE)

