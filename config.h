/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 0;        /* 0 means no bar */
static const int topbar             = 0;        /* 0 means bottom bar */
static const char *fonts[]          = { "JetBrainsMono Nerd Font:size=9:style=bold" };
static const char dmenufont[]       = "JetBrainsMono Nerd Font Mono:size=10";
static const char col_gray1[]       = "#11111B";
static const char col_gray2[]       = "#282737";
static const char col_gray3[]       = "#585767";
static const char col_gray4[]       = "#282737";
static const char col_cyan[]        = "#96CDFB";

static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan },
};

/* tagging */
static const char *tags[] = { "", "", "󰀻", "", "", "󰇮", "", "󱓞" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class, instance                  title, tags mask, isfloating, monitor */
	{ "Zathura", NULL,                  NULL, 1 << 0, 0, -1 },
    { "st-256color", "st-256color",     NULL, 1 << 1, 0, -1 },
    { "qutebrowser", NULL,              NULL, 1 << 2, 0, -1 },
    { "qBittorrent", NULL,              NULL, 1 << 2, 0, -1 },

    /* Risk of Rain 2 */    { "steam_app_632360", NULL,         NULL, 1 << 3, 0, -1 },
    /* Green Hell */        { "steam_app_815370", NULL,         NULL, 1 << 3, 0, -1 },
    /* Project Zomboid */   { "Project Zomboid", NULL,         NULL, 1 << 3, 0, -1 },
    /* Hollow Knight */     { "hollow_knight.x86_64", NULL,         NULL, 1 << 3, 0, -1 },
    /* Deep Rock Galactic */        { "steam_app_548430", NULL,         NULL, 1 << 3, 0, -1 },

    /* Floating */
    { NULL, "steamwebhelper",           NULL, 1 << 7, 1, -1 }, 
    { NULL, "r2modman",                 NULL, 1 << 7, 1, -1},

    /* Other */
    { "mpv", NULL,                      NULL, 1 << 4, 0, -1 },
    { NULL, "neomutt",                  NULL, 1 << 5, 1, -1 },
    { NULL, "newsraft",                 NULL, 1 << 6, 1, -1 },
    
    { "scratchpad", NULL,               NULL,      0, 1, -1 },
};

static const char sticky_class[] = "mpv";

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#include "gaplessgrid.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
    /* first entry is default */
    { "HHH",      gaplessgrid },
    { "[]=",      tile },
    { "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define ALTGR Mod5Mask 

#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[]   = { "dmenu_run", NULL };
static const char *termcmd[]    = { "st", NULL };
static const char *mpcnext[]    = { "mpc", "next", NULL };
static const char *mpctoggle[]  = { "mpc", "toggle", NULL };
static const char *mpcprev[]    = { "mpc", "prev", NULL };

#include <X11/XF86keysym.h>
#include "toggleview_focus.c"
#include "togglefullscr.c"
#include "toggleview_scratchpad.c"
#include "movestack.c"

static const Key keys[] = {
	/* modifier                     key        function        argument */
    { MODKEY,                       XK_F4,     spawn,          SHCMD("notify-send Apagando...; pkill qutebrowser; pkill zathura; sleep 2; shutdown now") },
	{ MODKEY,                       XK_p,      spawn,          SHCMD("~/bin/scratchpad.sh launcher 60x15+600-20 ~/bin/startup/launcher-desktop.sh") },
	{ MODKEY,                       XK_KP_Begin,      spawn,   SHCMD("~/bin/scratchpad.sh utilities 60x15+600-20 ~/bin/utilities.sh") },
    { MODKEY,                       XK_KP_End, spawn,          SHCMD("~/bin/scratchpad.sh trans 50x12-200+0 'trans -4 -I'") },
    { MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
    { MODKEY|ShiftMask,             XK_Return, view,           {.ui = 1 << 1 } },
    { ALTGR,                        XK_p,      spawn,          {.v = mpctoggle } },
    { ALTGR,                        XK_Right,  spawn,          {.v = mpcnext } },
    { ALTGR,                        XK_Left,   spawn,          {.v = mpcprev } },
    { ALTGR,                        XK_Up,     spawn,          SHCMD("~/bin/startup/volume_notif.sh up; kill -RTMIN $(cat ~/.cache/pidofbar)") },
    { ALTGR,                        XK_Down,   spawn,          SHCMD("~/bin/startup/volume_notif.sh down; kill -RTMIN $(cat ~/.cache/pidofbar)") },
    { ALTGR,                        XK_Delete, spawn,          SHCMD("~/bin/startup/volume_notif.sh mute; kill -RTMIN $(cat ~/.cache/pidofbar)") },
    { MODKEY,                       XK_Delete, spawn,          SHCMD("~/bin/startup/volume_notif.sh mic") },
    { 0,                            XK_Print,  spawn,          SHCMD("maim | xclip -selection clipboard -t image/png") },
    { ShiftMask,                    XK_Print,  spawn,          SHCMD("maim -i $(xdotool getactivewindow) | xclip -selection clipboard -t image/png") },
    { ControlMask,                  XK_Print,  spawn,          SHCMD("maim -s | xclip -selection clipboard -t image/png") },
    { MODKEY,                       XK_Print,  spawn,          SHCMD("maim ~/Pictures/screenshots/$(date +%s).png") },
    { MODKEY|ShiftMask,             XK_Print,  spawn,          SHCMD("maim -i $(xdotool getactivewindow) ~/Pictures/screenshots/$(date +%s).png") },
    { MODKEY|ControlMask,           XK_Print,  spawn,          SHCMD("maim -s ~/Pictures/screenshots/$(date +%s).png") },
    
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
    { MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1 } },
    { MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
    { MODKEY,                       XK_g,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[1]} },
    { MODKEY,                       XK_f,      setlayout,      {.v = &layouts[2]} },
    { MODKEY|ShiftMask,             XK_f,      togglefullscr,  {0} },
  /*{ MODKEY,                       XK_f,      togglefullscr,  {0} },*/
    { MODKEY,                       XK_s,      togglesticky,    {0} },
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
    { MODKEY,                       XK_less,    toggleview_scratchpad,         {.ui = 1 << 4 } },
    { MODKEY,                       XK_KP_Down, toggleview_focus,   {.ui = 1 << 5} },
    { MODKEY,                       XK_KP_Next, toggleview_focus,   {.ui = 1 << 6} },
    { MODKEY,                       XK_KP_Left, toggleview_focus,   {.ui = 1 << 7} },
	{ MODKEY|ShiftMask,             XK_q,       quit,               {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

