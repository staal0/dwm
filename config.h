/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int focusonwheel       = 0;
static const char *fonts[]          = { "monospace:size=13" };
static const char dmenufont[]       = "monospace:size=13";

//static const char col_gray1[]       = "#222222";
//static const char col_gray2[]       = "#444444";
//static const char col_gray3[]       = "#bbbbbb";
//static const char col_gray4[]       = "#eeeeee";
//static const char col_cyan[]        = "#005577";
//static const char *colors[][3]      = {
//	/*               fg         bg         border   */
//	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
//	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
//};

/*
DRACULA COLOR SCHEME
Background	#282a36	
Current Line	#44475a	
Foreground	#f8f8f2	
Comment		#6272a4	
Cyan		#8be9fd	
Green		#50fa7b	
Orange		#ffb86c	
Pink		#ff79c6	
Purple		#bd93f9	
Red		#ff5555	
Yellow		#f1fa8c
*/

static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#f8f8f2";
static const char col_cyan[]        = "#44475a";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_gray1,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class          instance  title  			tags mask  iscentered  isfloating   monitor */
	{ "st-256color",  NULL,     NULL,  			0,         0,		  0,           -1 },
	{ NULL,		  NULL,     "pulsemixer",	  	0,         1,		  1,           -1 },
	{ "qutebrowser",  NULL,     NULL,  			1 << 1,    0,		  0,           -1 },
	{ "Firefox-esr",  NULL,     NULL,  			1 << 3,    0,		  0,           -1 },
	{ "thunderbird",  NULL,     NULL,  			1 << 2,    0,		  0,           -1 },
	{ "Evolution",    NULL,     NULL,  			1 << 2,    0,		  0,           -1 },
	{ NULL,		  NULL,     "neomutt", 			1 << 2,    0,		  0,           -1 },
	{ NULL,		  NULL,     "newsboat",			1 << 2,    0,		  0,           -1 },
	{ NULL,		  NULL,     "calcurse",			1 << 2,    0,		  0,           -1 },
	{ "Signal",       NULL,     NULL,  			1,         0,		  0,           -1 },
	{ "MPlayer",	  NULL,     "cam1",	  		0,         1,		  1,           -1 },
	{ "MPlayer",	  NULL,     "cam2",	  		0,         1,		  1,           -1 },
	{ "MPlayer",	  NULL,     "cam3",	  		0,         1,		  1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

#include "maximize.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod1Mask
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
static const char *termcmd[]  = { "st", "-e", "fish", NULL };
static const char *lockcmd[] = { "slock", NULL };
static const char *soundupcmd[] = { "amixer", "-q", "sset", "Master", "5%+", NULL };
static const char *sounddowncmd[] = { "amixer", "-q", "sset", "Master", "5%-", NULL };
static const char *soundtogglecmd[] = { "amixer", "-q", "sset", "Master", "toggle", NULL };
static const char *mixercmd[] = { "st", "pulsemixer", NULL };
static const char *clipmenucmd[] = { "clipmenu", NULL };
static const char *showclipboardcmd[]  = { "show_clipboard.sh", NULL };
static const char *scrotcmd[]  = { "scrot", NULL };
static const char *scrotfocusedcmd[]  = { "scrot", "--focused", NULL };
static const char *officefancmd[]  = { "office_fan.sh", NULL };
static const char *cam1cmd[]  = { "cam.sh", "1", NULL };
static const char *cam2cmd[]  = { "cam.sh", "2", NULL };
static const char *cam4cmd[]  = { "cam.sh", "3", NULL };
static const char *camallcmd[]  = { "cam.sh", "all", NULL };

static Key keys[] = {
	/* modifier                     key        function        		argument */
	{ MODKEY,                       XK_p,      spawn,          		{.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          		{.v = termcmd } },
	{ MODKEY|ControlMask,           XK_l,      spawn,          		{.v = lockcmd } },
	{ ControlMask,                  XK_Up,     spawn,          		{.v = soundupcmd } },
	{ ControlMask,                  XK_Down,   spawn,          		{.v = sounddowncmd } },
	{ ControlMask,                  XK_space,  spawn,          		{.v = soundtogglecmd } },
	{ ControlMask,                  XK_m,  	   spawn,          		{.v = mixercmd } },
	{ MODKEY,                       XK_Insert, spawn,          		{.v = clipmenucmd } },
	{ MODKEY|ShiftMask,             XK_Insert, spawn,          		{.v = showclipboardcmd } },
	{ 0,                            XK_Print,  spawn,          		{.v = scrotcmd } },
	{ MODKEY,                       XK_Print,  spawn,          		{.v = scrotfocusedcmd } },
	{ MODKEY|ShiftMask,             XK_F1,     spawn,          		{.v = officefancmd } },
	{ MODKEY|ShiftMask,             XK_F2,     spawn,          		{.v = cam1cmd } },
	{ MODKEY|ShiftMask,             XK_F3,     spawn,          		{.v = cam2cmd } },
	{ MODKEY|ShiftMask,             XK_F4,     spawn,          		{.v = cam4cmd } },
	{ MODKEY|ShiftMask,             XK_F5,     spawn,          		{.v = camallcmd } },
	{ MODKEY|ControlMask|ShiftMask, XK_h,      togglehorizontalmax,	{0} },
	{ MODKEY|ControlMask|ShiftMask, XK_l,      togglehorizontalmax, {0} },
	{ MODKEY|ControlMask|ShiftMask, XK_j,      toggleverticalmax,   {0} },
	{ MODKEY|ControlMask|ShiftMask, XK_k,      toggleverticalmax,   {0} },
	{ MODKEY|ControlMask,           XK_m,      togglemaximize,      {0} },
	{ MODKEY,                       XK_b,      togglebar,      		{0} },
	{ MODKEY,                       XK_j,      focusstack,     		{.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     		{.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     		{.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     		{.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       		{.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       		{.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           		{0} },
	{ MODKEY,                       XK_Tab,    view,           		{0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     		{0} },
	{ MODKEY,                       XK_t,      setlayout,      		{.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      		{.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      		{.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      		{0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, 		{0} },
	{ MODKEY,                       XK_0,      view,           		{.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            		{.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       		{.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       		{.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         		{.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         		{.i = +1 } },
	TAGKEYS(                        XK_1,                      		0)
	TAGKEYS(                        XK_2,                      		1)
	TAGKEYS(                        XK_3,                      		2)
	TAGKEYS(                        XK_4,                      		3)
	TAGKEYS(                        XK_5,                      		4)
	TAGKEYS(                        XK_6,                      		5)
	TAGKEYS(                        XK_7,                      		6)
	TAGKEYS(                        XK_8,                      		7)
	TAGKEYS(                        XK_9,                      		8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           		{0} },
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
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

