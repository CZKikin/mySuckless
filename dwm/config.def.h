/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Minecraft:size=14","monospace:size=14", "fontawesome:size=14", "symbola:pixelsize=14" };
static const char dmenufont[]       = "Minecraft:size=14";
static const unsigned int baralpha  = 125;
static const unsigned int borderalpha = OPAQUE;
static char normbgcolor[]           = "#000000"; /* Background of non-selected tag */
static char normbordercolor[]       = "#444444"; /* Border of non-active window    */
static char normfgcolor[]           = "#ff0000"; /* Color of non-active text       */
static char selfgcolor[]            = "#ffffff"; /* Color of active text           */
static char selbordercolor[]        = "#ff0000"; /* Border of selected program     */
static char selbgcolor[]            = "#000000"; /* Background of selected tag     */
static const char *colors[][3] = {
    /*               fg           bg           border   */
    [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
    [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
    [SchemeStatus]  = { normfgcolor, normbgcolor,  "#000000"  },    /* Statusbar right {text,background,not used but cannot be empty}            */
    [SchemeTagsSel]  = { selfgcolor,  selbgcolor,  "#000000"  },    /* Tagbar left selected {text,background,not used but cannot be empty}       */
    [SchemeTagsNorm]  = { normfgcolor, normbgcolor,  "#000000"  },  /* Tagbar left unselected {text,background,not used but cannot be empty}     */
    [SchemeInfoSel]  = { selfgcolor,  selbgcolor, "#000000"  },    /* infobar middle  selected {text,background,not used but cannot be empty}   */
    [SchemeInfoNorm]  = { normfgcolor, normbgcolor,  "#000000"  },  /* infobar middle  unselected {text,background,not used but cannot be empty} */
};

static const unsigned int alphas[][3]      = {
	/*               fg      bg        border     */
	[SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
	[SchemeStatus]  = { OPAQUE, baralpha, borderalpha },
	[SchemeTagsSel]  = { OPAQUE, baralpha, borderalpha },
    [SchemeTagsNorm]  = { OPAQUE, baralpha, borderalpha },
	[SchemeInfoSel]  = { OPAQUE, baralpha, borderalpha },
	[SchemeInfoSel]  = { OPAQUE, baralpha, borderalpha },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
		/* xprop(1):
		 * 	WM_CLASS(STRING) = instance, class
		 	WM_NAME(STRING) = title
		 */
		/* class      instance    title       tags mask     isfloating   monitor */
		{ "Gimp",     NULL,       NULL,       0,            0,           -1 },
        { "discord",  NULL,       NULL,       1 << 1,       0,           -1 },
        { "Steam",    NULL,       NULL,       1 << 2,       0,           -1 }, 
        { "St",       NULL,  "neomutt",       1 << 4,       0,           -1 },
        { "origin.exe", NULL,     NULL,       0,            1,           -1 },
        { "Signal",   NULL,       NULL,       1 << 3,       0,           -1 },
        { "Opera",    NULL,       NULL,       1 << 0,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

#include "fibonacci.c"
static const Layout layouts[] = {
		/* symbol     arrange function */
	 	{ "[\\]",      dwindle },/* first entry is default */
		{ "[M]",      monocle },
		{ "[]=",      tile }, 
	 	{ "[@]",      spiral },   
		{ "><>",      NULL },    /* no layout function means floating behavior */
};

/* key definitions */
#define MODKEY Mod4Mask
#define ALTKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
		{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
		{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
		{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
		{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* Longer commands deffinition */
#define VOLUME_DOWN "pactl set-sink-volume 0 -5% ; pkill -RTMIN+3 dwmblocks" 
#define VOLUME_UP "[ `pactl list sinks | awk '/\\WHlasitost/ {print $5}' | sed 's/%//g'` -lt 100 ] && { pactl set-sink-volume 0 +5% ; pkill -RTMIN+3 dwmblocks; }"
#define SHUTDOWN_MENU "exec `echo \"shutdown now\nreboot\nsystemctl suspend\nsystemctl hibernate\" | dmenu`" 

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbordercolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *opera[]  = { "opera", NULL };

static Key keys[] = {
		/* modifier             key    function        argument */
		{ MODKEY,               33,    spawn,          {.v = dmenucmd } },            // p
		{ MODKEY|ShiftMask,     36,    spawn,          {.v = termcmd } },             // Return
		{ MODKEY,               56,    togglebar,      {0} },                         // b
		{ MODKEY,               44,    focusstack,     {.i = +1 } },                  // j
		{ MODKEY,               45,    focusstack,     {.i = -1 } },                  // k
		{ MODKEY,               31,    incnmaster,     {.i = +1 } },                  // i
		{ MODKEY,               40,    incnmaster,     {.i = -1 } },                  // d 
        { MODKEY,               43,    setmfact,       {.f = -0.05} },                // h
		{ MODKEY,               46,    setmfact,       {.f = +0.05} },                // l
		{ MODKEY,               36,    zoom,           {0} },                         // Return
		{ MODKEY,               23,    view,           {0} },                         // Tab
		{ MODKEY|ShiftMask,     24,    killclient,     {0} },                         // q
		{ MODKEY,               28,    setlayout,      {.v = &layouts[2]} },          // t
		{ MODKEY,               41,    setlayout,      {.v = &layouts[4]} },          // f
		{ MODKEY,               57,    setlayout,      {.v = &layouts[0]} },          // n 
		{ MODKEY,               58,    setlayout,      {.v = &layouts[1]} },          // m
		{ MODKEY,		        116,   xrdb,	       {.v = NULL } },                // F5
		{ MODKEY,               65,    setlayout,      {0} },                         // space
		{ MODKEY|ShiftMask,     65,    togglefloating, {0} },                         // space
		{ MODKEY,               19,    view,           {.ui = ~0 } },                 // 0
		{ MODKEY|ShiftMask,     19,    tag,            {.ui = ~0 } },                 // 0
		{ MODKEY,               59,    focusmon,       {.i = -1 } },                  // comma
		{ MODKEY,               60,    focusmon,       {.i = +1 } },                  // period
		{ MODKEY|ShiftMask,     59,    tagmon,         {.i = -1 } },                  // comma
		{ MODKEY|ShiftMask,     60,    tagmon,         {.i = +1 } },                  // period
		{ MODKEY,	       	    26,    spawn,	       SHCMD("st -e ranger") },       // e
        { MODKEY|ControlMask,   46,    spawn,          SHCMD("slock") },              //l 
        { ControlMask|ShiftMask, 9,    spawn,          SHCMD("st -e htop") },               //esc
		{ MODKEY,	       	    25,    spawn,          {.v = opera } },               //w
		{ 0, 			        123,   spawn,	       SHCMD(VOLUME_UP) },            //Vol +
		{ 0,			        122,   spawn,	       SHCMD(VOLUME_DOWN) },          //Vol -
		{ MODKEY,		        60,    spawn,	       SHCMD("~/.scripts/pick_emo") },//.
        { MODKEY|ShiftMask,     40,    spawn,          SHCMD("discord") },            //d
        { MODKEY|ShiftMask,     58,    spawn,          SHCMD("st -e neomutt") },      //m
        { ALTKEY|ControlMask,   119,   spawn,          SHCMD(SHUTDOWN_MENU) },        //CTRL ALT DEL
		TAGKEYS(                10,                    0)                             // 1
		TAGKEYS(                11,                    1)                             // 2
		TAGKEYS(                12,                    2)                             // 3
		TAGKEYS(                13,                    3)                             // 4
		TAGKEYS(                14,                    4)                             // 5
		TAGKEYS(                15,                    5)                             // 6
		TAGKEYS(                16,                    6)                             // 7
		TAGKEYS(                17,                    7)                             // 8
		TAGKEYS(                18,                    8)                             // 9
		{ MODKEY|ShiftMask,     54,    quit,           {0} },                         // c
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

