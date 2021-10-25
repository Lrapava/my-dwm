/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 0;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0;   	/* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 0;     /* 0 means no systray */
static const unsigned int gappih    = 0;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 0;      /* vert inner gap between windows */
static const unsigned int gappoh    = 0;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 0;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 0;       /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int focusonwheel       = 0;
static const double activeopacity   = 1.0f;     /* Window opacity when it's focused (0 <= opacity <= 1) */
static const double inactiveopacity = 1.0f;   /* Window opacity when it's inactive (0 <= opacity <= 1) */
static const char *fonts[]          = { "monospace:size=10" };
static const char dmenufont[]       = "monospace:size=10";
static const char col_gray1[]       = "#232323"; // 222222
static const char col_gray2[]       = "#818588"; // 444444
static const char col_gray3[]       = "#dddddd";
static const char col_gray4[]       = "#ffffff";
static const char col_cyan[]        = "#31758A"; // "#656e95"; 7b78ac 0a5b54 7170AB 03414e 31758A 428397 18A1A8 4C5AD4 2782de 31758A 248495
static const unsigned int baralpha = 0xd0;
static const unsigned int borderalpha = OPAQUE;
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};
static const unsigned int alphas[][3]      = {
	/*               fg      bg        border     */
	[SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            0,           -1 },
	{ "Firefox",  NULL,       NULL,       0,       		0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int attachdirection = 1;   /* 0 default, 1 above, 2 aside, 3 below, 4 bottom, 5 top */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "[M]",      monocle },
	{ "[@]",      spiral },
	{ "[\\]",     dwindle },
	{ "H[]",      deck },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
	{ "HHH",      grid },
	{ "###",      nrowgrid },
	{ "---",      horizgrid },
	{ ":::",      gaplessgrid },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	{ "|+|",      tatami },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ NULL,       NULL },
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
// static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
// static const char *termcmd[]  = { "st", NULL };
static const char *dmenucmd[] = { "rofi", "-show", "drun", NULL };
static const char *termcmd[]  = { "alacritty", NULL };
static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = { "st", "-t", scratchpadname, "-g", "120x34", NULL };

#include "movestack.c"
#include "custom.c"
static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       39,      spawn,     	   {.v = screenshot} },
	// { MODKEY|ShiftMask,             39, 	   spawn, 		   {.v = rect_screenshot} },
	{ MODKEY,                       9, 		 spawn,          {.v = slock } },
	{ Mod1Mask|ShiftMask,           23,	   	 kbmanage, 	   {0}},
	{ MODKEY|ShiftMask,             23,	   	 kbmanage, 	   {0}},
	{ 0,              				121,     spawn,     	   {.v = mutecmd} },
	{ 0,              				122, 	 spawn,     	   {.v = voldowncmd} },
	{ 0,              				123, 	 spawn,          {.v = volupcmd} },
	{ 0,              				198,	 spawn,          {.v = mutemic} },
	// { MODKEY|ShiftMask,             XK_equal,  spawn,     	   {.v = volupcmd} },
	// { MODKEY|ShiftMask,             XK_minus,  spawn,          {.v = voldowncmd} },
	{ MODKEY|ShiftMask,             42,      skcomp,     	   {0} },
	{ MODKEY,             			42,		 spawn,		   {.v = steam} },
	{ MODKEY,                       25,      spawn,		   {.v = browser} },
	{ MODKEY|ShiftMask,             26,	   	 spawn,		   {.v = settings} },
	
	{ MODKEY,                       49,  	 togglescratch,  {.v = scratchpadcmd } },
	{ MODKEY,                       33,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             36, 	 spawn,          {.v = termcmd } },
	{ MODKEY,                       56,      togglebar,      {0} },
	{ MODKEY,                       44,      focusstack,     {.i = +1 } },
	{ MODKEY,                       45,      focusstack,     {.i = -1 } },
	{ MODKEY,                       31,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       40,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       43,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       46,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             43,      setcfact,       {.f = +0.25} },
	{ MODKEY|ShiftMask,             46,      setcfact,       {.f = -0.25} },
	{ MODKEY|ShiftMask,             32,      setcfact,       {.f =  0.00} },
	{ MODKEY|ShiftMask,             44,      movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,             45,      movestack,      {.i = -1 } },

	// normie shortcuts
	{ MODKEY,                       116,      focusstack,     {.i = +1 } },
	{ MODKEY,                       111,      focusstack,     {.i = -1 } },
	{ MODKEY,                       113,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       114,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             113,      setcfact,       {.f = +0.25} },
	{ MODKEY|ShiftMask,             114,      setcfact,       {.f = -0.25} },
	{ MODKEY|ShiftMask,             116,      movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,             111,      movestack,      {.i = -1 } },

	{ MODKEY,                       36, zoom,           {0} },

	// { MODKEY|Mod4Mask,              XK_u,      incrgaps,       {.i = +1 } },
	// { MODKEY|Mod4Mask|ShiftMask,    XK_u,      incrgaps,       {.i = -1 } },
	// { MODKEY|Mod4Mask,              XK_i,      incrigaps,      {.i = +1 } },
	// { MODKEY|Mod4Mask|ShiftMask,    XK_i,      incrigaps,      {.i = -1 } },
	// { MODKEY|Mod4Mask,              XK_o,      incrogaps,      {.i = +1 } },
	// { MODKEY|Mod4Mask|ShiftMask,    XK_o,      incrogaps,      {.i = -1 } },
	// { MODKEY|Mod4Mask,              XK_6,      incrihgaps,     {.i = +1 } },
	// { MODKEY|Mod4Mask|ShiftMask,    XK_6,      incrihgaps,     {.i = -1 } },
	// { MODKEY|Mod4Mask,              XK_7,      incrivgaps,     {.i = +1 } },
	// { MODKEY|Mod4Mask|ShiftMask,    XK_7,      incrivgaps,     {.i = -1 } },
	// { MODKEY|Mod4Mask,              XK_8,      incrohgaps,     {.i = +1 } },
	// { MODKEY|Mod4Mask|ShiftMask,    XK_8,      incrohgaps,     {.i = -1 } },
	// { MODKEY|Mod4Mask,              XK_9,      incrovgaps,     {.i = +1 } },
	// { MODKEY|Mod4Mask|ShiftMask,    XK_9,      incrovgaps,     {.i = -1 } },
	// { MODKEY|Mod4Mask,              XK_0,      togglegaps,     {0} },
	// { MODKEY|Mod4Mask|ShiftMask,    XK_0,      defaultgaps,    {0} },

	{ MODKEY|ShiftMask,             21,		incrgaps,       {.i = +1 } },
	{ MODKEY,    					20,		incrgaps,       {.i = -1 } },
	{ Mod1Mask|ShiftMask,           19,		togglegaps,     {0} },
	{ MODKEY|Mod1Mask,    			19,		defaultgaps,    {0} },
	
	{ Mod1Mask,                     23,		view,           {0} },
	{ MODKEY,                       23,		view,           {0} },
	{ MODKEY|ShiftMask,             54,		killclient,     {0} },
	{ MODKEY,                       28,		setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       58,		setlayout,      {.v = &layouts[1]} },
	// { MODKEY,                       XK_,      setlayout,      {.v = &layouts[2]} },
	// { MODKEY|ShiftMask,             XK_,      setlayout,      {.v = &layouts[3]} },
	// { MODKEY,                       XK_,      setlayout,      {.v = &layouts[4]} },
	// { MODKEY,                       XK_,      setlayout,      {.v = &layouts[5]} },
	// { MODKEY,                       XK_,      setlayout,      {.v = &layouts[6]} },
	// { MODKEY,                       XK_,      setlayout,      {.v = &layouts[7]} },
	// { MODKEY,                       XK_,      setlayout,      {.v = &layouts[8]} },
	// { MODKEY,                       XK_,      setlayout,      {.v = &layouts[9]} },
	// { MODKEY,                       XK_,      setlayout,      {.v = &layouts[10]} },
	// { MODKEY,                       XK_,      setlayout,      {.v = &layouts[11]} },
	// { MODKEY,                       XK_,      setlayout,      {.v = &layouts[12]} },
	// { MODKEY,                       XK_,      setlayout,      {.v = &layouts[13]} },
	{ MODKEY,                       41,		setlayout,      {.v = &layouts[14]} },
	{ MODKEY|ControlMask,			59,		cyclelayout,    {.i = -1 } },
	{ MODKEY|ControlMask,           60,		cyclelayout,    {.i = +1 } },
	{ MODKEY,                       65,		setlayout,      {0} },
	{ MODKEY|ShiftMask,             65,		togglefloating, {0} },
	{ MODKEY|ShiftMask,             41,		togglefullscr,  {0} },
	{ MODKEY,                       19,		view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             19,		tag,            {.ui = ~0 } },
	{ MODKEY,                       59,		focusmon,       {.i = -1 } },
	{ MODKEY,                       60,		focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             59,		tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             60,		tagmon,         {.i = +1 } },
	TAGKEYS(                        10,                      0)
	TAGKEYS(                        11,                      1)
	TAGKEYS(                        12,                      2)
	TAGKEYS(                        13,                      3)
	TAGKEYS(                        14,                      4)
	TAGKEYS(                        15,                      5)
	TAGKEYS(                        16,                      6)
	TAGKEYS(                        17,                      7)
	TAGKEYS(                        18,                      8)
	{ MODKEY|ShiftMask,             24,      quit,           {0} },
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
