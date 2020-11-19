dwm - dynamic window manager
============================
dwm is an extremely fast, small, and dynamic window manager for X.

This is gergap's fork of dwm where I collect my patches, configuration  and
additional files for configuration. Also have a look at my
[cheatsheet](https://github.com/gergap/dwm/blob/gergap/dwm-cheatsheet.pdf).

When installed you can always open the cheatshet by pressing F1.

Tools used
----------

My configuration makes use of some other tools which are:

- chromium and firefox-esr
- evolution
- nautilus
- ranger
- pactl
- xbacklight
- mupd
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
