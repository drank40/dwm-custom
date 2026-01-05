/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel size of windows */
static const unsigned int gappx     = 3;        /* gaps size between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = {"sourcecodepro:size=14", "fontawesome:size=19"};
static const char dmenufont[]       = "sourcecodepro:size=12";
//background color
static const char col_gray1[]       = "#222222";
//inactive window border color
static const char col_gray2[]       = "#444444";
//font color
static const char col_gray3[]       = "#bbbbbb";
//current tag and current window font color
static const char col_gray4[]       = "#eeeeee";
//Top bar second color (blue) and active window border color
static const char col_cyan[]        = "#f2485a";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
//tag names (upper left)



static const char *tags[] = { "","", "", "", "", "", "", ""  };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class     instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
	{ "Gimp",    NULL,     NULL,           0,         1,          0,           0,        -1 },
	{ "Firefox", NULL,     NULL,           1 << 8,    0,          0,          -1,        -1 },
	{ "URxvt",      NULL,     NULL,           0,         0,          1,           0,        -1 },
	{ "St",      NULL,     "st"             , 0,         0,          1,           1,        -1 }, 
	{ "gdb",      NULL,     "gdb"             , 0,         0,          1,           1,        -1 }, 
	{ NULL,      NULL,     "TaxMan"        , 0,         1,          0,           1,        -1 }, 
	{ NULL,      NULL,     "Event Tester", 0,         0,          0,           1,        -1 }, /* xev */
	{ NULL,      NULL,     "svkbd", ((int)((1LL << LENGTH(tags)) - 1)),         1,          0,           1,        -1 }, /* xev */

};


/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
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

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
//static const char *filemanager[] = { "
//launches htop
static const char *monitor[] = { "/usr/bin/htop", NULL };
//sets st as the default terminal
//static const char *termcmd[]  = { "st", NULL };
//sets urxvt as the default terminal
static const char *termcmd[]  = { "st", NULL };
//volume controls
#include <X11/XF86keysym.h>
static const char *upvol[]   = { "pulsemixer", "--change-volume", "+5", NULL };
static const char *downvol[]   = { "pulsemixer", "--change-volume", "-5", NULL };
static const char *mutevol[] = { "pulsemixer", "--set-volume", "0", NULL };
static const char *nextsong[] = { "killall", "mpv", NULL };
static const char *killmpv[] = { "killall", "mpv","playmusic", NULL };
static const char *lightup[] = { "~/.local/bin/light", "+5", NULL };
static const char *lightdown[] = { "~/.local/bin/light", "-5", NULL };
static const char *cmdprintscreen[]  = { "scrot", "/home/renny/Pictures/screenshots/%Y-%m-%d-%s_$wx$h.jpg", NULL };  //change to your username
static const char *dragprintscreen[]  = { "import", "/home/renny/sos.png", NULL };  //change to your username
static const char *firefox[]  = { "brave", NULL }; 
static const char *steam[]  = { "steam", NULL }; 
static const char *keyboard[]  = { "toggle", "svkbd-en", NULL }; 
static const char *suspend[]  = { "systemctl", "suspend", NULL }; 

#include "shiftview.c"
static char *endx[] = { "/bin/sh", "-c", "endx", "externalpipe", NULL };
static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
    { MODKEY|ShiftMask,             XK_f,      togglefullscr,  {0} },
	{ MODKEY,	                    XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,	                    XK_w, spawn,          {.v = firefox } },
	{ MODKEY,	                    XK_s, spawn,          {.v = steam } },
	{ MODKEY,                       XK_t,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ 0,                       XF86XK_AudioPlay, focusstack, {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_u,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_z,	   zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,	                    XK_q,      killclient,     {0} },
	{ MODKEY|ShiftMask,             XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ShiftMask,             XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY|ShiftMask,             XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY|ShiftMask,             XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -1 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0  } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,              		    XK_n,      shiftview,  	   { .i = +1 } },
	{ MODKEY,              		    XK_b,      shiftview,      { .i = -1 } },
	{ 0,                            XK_Print,      spawn,          {.v = cmdprintscreen } },
	{ ShiftMask,                    XK_Print,      spawn,          {.v = dragprintscreen } },
    { 0,                            XF86XK_AudioLowerVolume,      spawn,          {.v = downvol } },
    { 0,                       XF86XK_AudioRaiseVolume, spawn, {.v = upvol   } },
    { 0,                       XK_F6, spawn, {.v = keyboard   } },
    { MODKEY,                       XK_F3,     spawn,          {.v = upvol   } },
    { MODKEY,                       XK_F2,     spawn,          {.v = downvol } },
    { MODKEY,                       XK_F7,     spawn,          {.v = lightdown } },
    { MODKEY,                       XK_F8,     spawn,          {.v = lightup } },
    { MODKEY,                       XK_F1,     spawn,          {.v = nextsong } },
    { MODKEY,                       XK_F10,     spawn,          {.v = suspend } },
    { MODKEY|ShiftMask,                       XK_F1,     spawn,          {.v = killmpv } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
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

