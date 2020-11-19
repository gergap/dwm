dwm - dynamic window manager
============================
dwm is an extremely fast, small, and dynamic window manager for X.

This is _gergap's_ fork of dwm where I collect my patches, configuration  and
additional files for configuration. Also have a look at my
[cheatsheet](https://github.com/gergap/dwm/blob/gergap/dwm-cheatsheet.pdf).

When installed you can always open the cheatsheet by pressing F1.

Tools used
----------

My configuration makes use of some other tools which are:

- Chromium and firefox-esr - Web browsers
- GNOME Evolution E-Mail client (`sudo apt install evolution`)
- GNOME Nautilus File Manager (`sudo apt install nautilus`)
- Ranger - Console File Manager (`sudo apt install ranger`)
- pactl - for controlling audio volume (`sudo apt install pulseaudio-utils`)
- xbacklight - for controlling display brightness (`sudo apt install xbacklight`)
- mupdf - PDF viewer (`sudo apt install mupdf`)
- st - Small and fast terminal from suckless.org (`git clone https://github.com/gergap/st`)
- and scripts found in https://github.com/gergap/binfiles

Requirements
------------
In order to build dwm you need the Xlib header files.


Installation
------------
Edit config.mk to match your local setup (dwm is installed into
the /usr/local namespace by default).

Afterwards enter the following command to build and install dwm (if
necessary as root):

    make clean install


Running dwm
-----------
Add the following line to your .xinitrc to start dwm using startx:

    exec dwm

In order to connect dwm to a specific display, make sure that
the DISPLAY environment variable is set correctly, e.g.:

    DISPLAY=foo.bar:1 exec dwm

(This will start dwm on display :1 of the host foo.bar.)

In order to display status info in the bar, you can do something
like this in your .xinitrc:

    while xsetroot -name "`date` `uptime | sed 's/.*,//'`"
    do
    	sleep 1
    done &
    exec dwm


Configuration
-------------
The configuration of dwm is done by creating a custom config.h
and (re)compiling the source code.
