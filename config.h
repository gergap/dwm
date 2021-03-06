/* See LICENSE file for copyright and license details. */

#include <X11/XF86keysym.h>

#define TERMINAL "st"
#define TERMCLASS "St"

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int gappx     = 10;       /* gap pixel between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "FontAwesome:size=12" };
static const char dmenufont[]       = "Hack:size=12";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char col_black[]       = "#000000";
static const char col_red[]         = "#ff0000";
static const char col_green[]       = "#00ff00";
static const char col_orange[]      = "#d75f00";
static const char col_yellow[]      = "#ffff00";
static const char col_white[]       = "#ffffff";
static const unsigned int baralpha = 0xd0;
static const unsigned int borderalpha = OPAQUE;
static const char *colors[][3]      = {
    /*               fg         bg         border   */
    [SchemeNorm]   = { col_gray3,  col_gray1,   col_gray2 },
    [SchemeSel]    = { col_gray4,  col_cyan,    col_orange },
    [SchemeWarn]   = { col_yellow, col_gray1,   col_yellow },
    [SchemeUrgent] = { col_red,    col_gray1,   col_red },
    [SchemeOn]     = { col_green,  col_gray1,   col_gray2 },
    [SchemeOff]    = { col_red,    col_gray1,   col_gray2 },
};
static const unsigned int alphas[][3]      = {
       /*               fg      bg        border     */
       [SchemeNorm]   = { OPAQUE, baralpha, borderalpha },
       [SchemeSel]    = { OPAQUE, baralpha, borderalpha },
       [SchemeWarn]   = { OPAQUE, baralpha, borderalpha },
       [SchemeUrgent] = { OPAQUE, baralpha, borderalpha },
       [SchemeOn]     = { OPAQUE, baralpha, borderalpha },
       [SchemeOff]    = { OPAQUE, baralpha, borderalpha },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       1 << 7,       1,           -1 },
	{ "XOsview",  NULL,       NULL,       0,            1,           -1 },
	{ "XClock",   NULL,       NULL,       0,            1,           -1 },
	{ "XEyes",    NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
	{ "Chromium", NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

#include "fibonacci.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "=[]",      tile_mirrored },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "[@]",      spiral },
	{ "[\\]",     dwindle },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }
#define CMD(cmd) { .v = (const char*[]){ cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { TERMINAL, NULL };
static const char *webcmd[]   = { "google-chrome", NULL };
static const char *webaltcmd[] = { "firefox-esr", NULL };
static const char *mailcmd[] = { "/usr/bin/evolution", NULL };
static const char *fmcmd[] = { "/usr/bin/nautilus", NULL };
static const char *upvol[]   = { "/usr/bin/pactl", "set-sink-volume", "0", "+5%",     NULL };
static const char *downvol[] = { "/usr/bin/pactl", "set-sink-volume", "0", "-5%",     NULL };
static const char *mutevol[] = { "/usr/bin/pactl", "set-sink-mute",   "0", "toggle",  NULL };
static const char *playpause[] = { "/usr/bin/rhythmbox-client", "--play-pause", NULL };
static const char *passcmd[] = { "passmenu", "--type", NULL };
static const char *passonlycmd[] = { "passmenu", "--type", "--pass-only", NULL };
static const char *speccmd[] = { "specs", NULL };
static const char *brightup[]   = { "xbacklight", "-inc", "10", NULL};
static const char *brightdown[] = { "xbacklight", "-dec", "10", NULL};
static const char *vpntoggle[] = { "vpn_toggle", NULL};
static const char *showhelp[] = { "/usr/bin/mupdf", "/usr/local/share/doc/dwm/dwm-cheatsheet.pdf", NULL};
static const char *scrotcmd[]  = { "scrot", "-t", "25", "-e", "mv $f /home/gergap/Screenshots", NULL };
static const char *scrotfocusedcmd[]  = { "scrot", "--focused", "-e", "mv $f /home/gergap/Screenshots", NULL };

#include "selfrestart.c"

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_p,      spawn,          {.v = passonlycmd } },
	{ MODKEY|ShiftMask,             XK_l,      spawn,          {.v = passcmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_w,      spawn,          {.v = webcmd } },
	{ MODKEY|ShiftMask,             XK_w,      spawn,          {.v = webaltcmd } },
	{ MODKEY,                       XK_e,      spawn,          {.v = mailcmd } },
	{ MODKEY,                       XK_n,      spawn,          {.v = fmcmd } },
	{ MODKEY,                       XK_r,      spawn,          SHCMD(TERMINAL " -e /bin/sh /usr/bin/ranger") },
	{ MODKEY,                       XK_s,      spawn,          {.v = speccmd } },
	{ MODKEY,                       XK_v,      spawn,          {.v = vpntoggle } },
	{ 0,                            XK_F1,     spawn,          {.v = showhelp } },
	{ 0,                            XK_Print,  spawn,          {.v = scrotcmd } },
	{ ShiftMask,                    XK_Print,  spawn,          {.v = scrotfocusedcmd } },
	{ ControlMask,                  XK_Print,  spawn,          SHCMD("sleep 1s;scrot --select -e 'mv $f /home/gergap/Screenshots'") },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ Mod1Mask,                     XK_F4,     killclient,     {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ShiftMask,             XK_t,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_y,      setlayout,      {.v = &layouts[4]} },
	{ MODKEY|ShiftMask,             XK_y,      setlayout,      {.v = &layouts[5]} },
	{ MODKEY,                       XK_u,      setlayout,      {.v = &layouts[6]} },
	{ MODKEY,                       XK_o,      setlayout,      {.v = &layouts[7]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY,                       XK_q,      self_restart,   {0} },
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
	{ 0,                            XF86XK_AudioPlay,          spawn, { .v = playpause } },
	{ 0,                            XF86XK_AudioLowerVolume,   spawn, { .v = downvol } },
	{ 0,                            XF86XK_AudioMute,          spawn, { .v = mutevol } },
	{ 0,                            XF86XK_AudioRaiseVolume,   spawn, {.v = upvol } },
    { 0,                            XF86XK_MonBrightnessUp,    spawn,            {.v = brightup } },
    { 0,                            XF86XK_MonBrightnessDown,  spawn,            {.v = brightdown } },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[3]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

