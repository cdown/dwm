/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 0;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Terminus:size=8" };
static const char dmenufont[]       = "Terminus:size=8";
static const char normbordercolor[] = "#073642";
static const char normbgcolor[]     = "#002b36";
static const char normfgcolor[]     = "#839496";
static const char selbordercolor[]  = "#93a1a1";
static const char selbgcolor[]      = "#073642";
static const char selfgcolor[]      = "#93a1a1";

static const char *colors[][3]      = {
	/*               fg           bg           border   */
	[SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
	[SchemeSel] =  { selfgcolor,  selbgcolor,  selbordercolor },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6" };
 
static const char pp_moni[]  = "pdfpc - presenter";
static const char pp_proj[]  = "pdfpc - presentation";

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            True,        -1 },
	{ NULL,       NULL,       "mail",     1 << 3,       False,       -1 },
	{ NULL,       NULL,       "irc",      1 << 2,       False,       -1 },
	{ NULL,       NULL,       "Terminal", 1,            False,       -1 },
	{ "Firefox",  NULL,       NULL,       1 << 1,       False,       -1 },
	{ NULL, "Tor Browser",    NULL,       1 << 1,       False,       -1 },
	{ "Spotify",  NULL,       NULL,       1 << 5,       False,       -1 },
	{ NULL,       NULL,       pp_moni,    0,            False,       2  },
	{ NULL,       NULL,       pp_proj,    0,            False,       1  },
};

/* layout(s) */
static const float mfact     = 0.5;  /* factor of master area size [0.05..0.95] */
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
#define TK(KEY,TAG) \
	{ MODKEY,                         KEY,  view,        {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,               KEY,  toggleview,  {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,             KEY,  tag,         {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask,   KEY,  toggletag,   {.ui = 1 << TAG} },
#define RK(MASK,KEY,ACTION) \
	{ MASK,                           KEY,  ACTION,      {.i  = +1 } }, \
	{ MASK|ShiftMask,                 KEY,  ACTION,      {.i  = -1 } },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-i", "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { "urxvtc", NULL };

static const char *mpdmenu_library[]  = { "mpdmenu", "-l", "::", "-i", "-l", "3", "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *mpdmenu_playlist[] = { "mpdmenu", "-p", "::", "-i", "-l", "3", "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *clipmenu[]         = { "clipmenu", "-i", "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *passmenu[]         = { "passmenu", "-i", "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };

static Key keys[] = {
  TK(                     XK_i,            0               )
  TK(                     XK_o,            1               )
  TK(                     XK_p,            2               )
  TK(                     XK_k,            3               )
  TK(                     XK_l,            4               )
  TK(                     XK_semicolon,    5               )
  RK( MODKEY,             XK_comma,        focusstack      )
  RK( MODKEY,             XK_period,       focusmon        )
  RK( MODKEY|ControlMask, XK_period,       tagmon          )

	{ MODKEY,             XK_1,            spawn,          {.v = dmenucmd } },
	{ MODKEY,             XK_2,            spawn,          {.v = passmenu } },
	{ MODKEY,             XK_3,            spawn,          {.v = clipmenu } },
	{ MODKEY,             XK_Return,       spawn,          SHCMD("urxvtc -title Terminal") },
	{ MODKEY|ShiftMask,   XK_Return,       spawn,          SHCMD("urxvtc -title Scratch -geometry 160x40") },
	{ MODKEY|ControlMask, XK_b,            setlayout,      {.v = &layouts[1] } },
	{ MODKEY|ControlMask, XK_t,            setlayout,      {.v = &layouts[0] } },
	{ MODKEY|ControlMask, XK_g,            setlayout,      {.v = &layouts[4] } },
	{ MODKEY|ShiftMask,   XK_9,            setmfact,       {.f = -0.05} },
	{ MODKEY|ShiftMask,   XK_0,            setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,   XK_r,            setmfact,       {.f = 1.5} },  /* >1.0 sets absolute value */
	{ MODKEY,             XK_backslash,    spawn,          SHCMD("firefox") },
	{ MODKEY|ControlMask, XK_backslash,    spawn,          SHCMD("firefox --private-window") },
	{ MODKEY|ShiftMask,   XK_backslash,    spawn,          SHCMD("tor-browser-en") },
	{ MODKEY,             XK_slash,        spawn,          {.v = mpdmenu_library } },
	{ MODKEY|ControlMask, XK_slash,        spawn,          {.v = mpdmenu_playlist } },
	{ MODKEY,             XK_Prior,        spawn,          SHCMD("pulseaudio-ctl up") },
	{ MODKEY,             XK_Next,         spawn,          SHCMD("pulseaudio-ctl down") },
	{ MODKEY,             XK_m,            spawn,          SHCMD("pulseaudio-ctl mute") },
	{ MODKEY,             XK_Down,         spawn,          SHCMD("mpc toggle") },
	{ MODKEY,             XK_Right,        spawn,          SHCMD("mpc next") },
	{ MODKEY,             XK_Left,         spawn,          SHCMD("mpc prev") },
	{ MODKEY|ControlMask, XK_F10,          spawn,          SHCMD("screenshot --focused") },
	{ MODKEY,             XK_F10,          spawn,          SHCMD("screenshot --all") },
	{ False,              XK_F10,          spawn,          SHCMD("screenshot --select") },
	{ MODKEY,             XK_Delete,       spawn,          SHCMD("slock") },
	{ MODKEY,             XK_Delete,       spawn,          SHCMD("sleep 1; xset dpms force off") },
	{ MODKEY,             XK_t,            spawn,          SHCMD("trello-popup") },
	{ MODKEY,             XK_d,            spawn,          SHCMD("notify-send \"$(world-tz)\"") },
	{ MODKEY,             XK_s,            spawn,          SHCMD("xinput-toggle -r yubikey -n -e -t 10") },
	{ MODKEY,             XK_Tab,          zoom,           {0} },
	{ MODKEY,             XK_BackSpace,    killclient,     {0} },
	{ MODKEY|ShiftMask,   XK_space,        togglefloating, {0} },
	{ Mod1Mask|ShiftMask, XK_q,            quit,           {0} },
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

/* vim: set noexpandtab: */
