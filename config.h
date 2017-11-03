#include <X11/XF86keysym.h>

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
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7" };

static const char pp_moni[]  = "pdfpc - presenter";
static const char pp_proj[]  = "pdfpc - presentation";

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     iscentered  isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            False,      True,        -1 },
	{ NULL,       NULL,       "Scratch",  0,            True,       True,        -1 },
	{ NULL,       NULL,       "mail",     1 << 3,       False,      False,       -1 },
	{ NULL,       NULL,       "irc",      1 << 2,       False,      False,       -1 },
	{ NULL,       NULL,       "Terminal", 1,            False,      False,       -1 },
	{ "chromium", NULL,       NULL,       1 << 1,       False,      False,       -1 },
	{ NULL, "Tor Browser",    NULL,       1 << 1,       False,      False,       -1 },
	{ "Spotify",  NULL,       NULL,       1 << 5,       False,      False,       -1 },
	{ NULL,       NULL,       pp_moni,    0,            False,      True,       2  },
	{ NULL,       NULL,       pp_proj,    0,            False,      True,       1  },
};

/* layout(s) */
static const float mfact     = 0.5;  /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TK(KEY,TAG) \
	{ KeyPress, MODKEY,                         KEY,  view,        {.ui = 1 << TAG} }, \
	{ KeyPress, MODKEY|ShiftMask,               KEY,  toggleview,  {.ui = 1 << TAG} }, \
	{ KeyPress, MODKEY|ControlMask,             KEY,  tag,         {.ui = 1 << TAG} }, \
	{ KeyPress, MODKEY|ControlMask|ShiftMask,   KEY,  toggletag,   {.ui = 1 << TAG} },
#define RK(MASK,KEY,ACTION) \
	{ KeyPress, MASK,                           KEY,  ACTION,      {.i  = +1 } }, \
	{ KeyPress, MASK|ShiftMask,                 KEY,  ACTION,      {.i  = -1 } },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }
#define ESHCMD(cmd) SHCMD("exec " cmd)

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-i", "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };

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
  TK(                     XK_apostrophe,   6               )
  RK( MODKEY,             XK_comma,        focusstack      )
  RK( MODKEY|ControlMask, XK_comma,        pushstack       )
  RK( MODKEY,             XK_period,       focusmon        )
  RK( MODKEY|ControlMask, XK_period,       tagmon          )

	{ KeyPress,   MODKEY,             XK_1,            spawn,          {.v = dmenucmd } },
	{ KeyPress,   MODKEY,             XK_2,            spawn,          {.v = passmenu } },
	{ KeyPress,   MODKEY,             XK_3,            spawn,          {.v = clipmenu } },
	{ KeyPress,   MODKEY,             XK_Return,       spawn,          ESHCMD("urxvtc -title Terminal") },
	{ KeyPress,   MODKEY|ShiftMask,   XK_Return,       spawn,          ESHCMD("urxvtc -title Scratch -geometry 160x40") },
	{ KeyPress,   MODKEY|ControlMask, XK_t,            setlayout,      {.v = &layouts[0] } },
	{ KeyPress,   MODKEY|ControlMask, XK_b,            setlayout,      {.v = &layouts[3] } },
	{ KeyPress,   MODKEY|ControlMask, XK_h,            setlayout,      {.v = &layouts[4] } },
	{ KeyPress,   MODKEY|ShiftMask,   XK_9,            setmfact,       {.f = -0.05} },
	{ KeyPress,   MODKEY|ShiftMask,   XK_0,            setmfact,       {.f = +0.05} },
	{ KeyPress,   MODKEY|ShiftMask,   XK_r,            setmfact,       {.f = 1.5} },  /* >1.0 sets absolute value */
	{ KeyPress,   MODKEY,             XK_backslash,    spawn,          ESHCMD("chromium") },
	{ KeyPress,   MODKEY|ControlMask, XK_backslash,    spawn,          ESHCMD("chromium --incognito") },
	{ KeyPress,   MODKEY|ShiftMask,   XK_backslash,    spawn,          ESHCMD("tor-browser-en") },
	{ KeyPress,   MODKEY,             XK_slash,        spawn,          {.v = mpdmenu_library } },
	{ KeyPress,   MODKEY|ControlMask, XK_slash,        spawn,          {.v = mpdmenu_playlist } },
	{ KeyPress,   MODKEY,             XK_Prior,        spawn,          ESHCMD("pulseaudio-ctl up") },
	{ KeyPress,   MODKEY,             XK_Next,         spawn,          ESHCMD("pulseaudio-ctl down") },
	{ KeyPress,   MODKEY,             XK_m,            spawn,          ESHCMD("pulseaudio-ctl mute") },
	{ KeyPress,   False,              XF86XK_AudioRaiseVolume, spawn,  ESHCMD("pulseaudio-ctl up") },
	{ KeyPress,   False,              XF86XK_AudioLowerVolume, spawn,  ESHCMD("pulseaudio-ctl down") },
	{ KeyPress,   False,              XF86XK_AudioMute,        spawn,  ESHCMD("pulseaudio-ctl mute") },
	{ KeyPress,   MODKEY,             XK_Down,         spawn,          ESHCMD("mpc toggle") },
	{ KeyPress,   MODKEY,             XK_Right,        spawn,          ESHCMD("mpc next") },
	{ KeyPress,   MODKEY,             XK_Left,         spawn,          ESHCMD("mpc prev") },
	{ KeyRelease, MODKEY|ControlMask, XK_F10,          spawn,          ESHCMD("screenshot --focused") },
	{ KeyRelease, MODKEY,             XK_F10,          spawn,          ESHCMD("screenshot --all") },
	{ KeyRelease, False,              XK_F10,          spawn,          ESHCMD("screenshot --select") },
	{ KeyPress,   MODKEY,             XK_Delete,       spawn,          ESHCMD("slock") },
	{ KeyPress,   MODKEY,             XK_Delete,       spawn,          SHCMD("sleep 1; xset dpms force off") },
	{ KeyPress,   MODKEY,             XK_t,            spawn,          ESHCMD("trello-popup") },
	{ KeyPress,   MODKEY,             XK_e,            spawn,          ESHCMD("nolock '1 hour'") },
	{ KeyPress,   MODKEY,             XK_d,            spawn,          ESHCMD("notify-send \"$(world-tz)\"") },
	{ KeyPress,   MODKEY,             XK_s,            spawn,          ESHCMD("xinput-toggle -r yubikey -n -e -t 10") },
	{ KeyPress,   MODKEY,             XK_Tab,          zoom,           {0} },
	{ KeyPress,   MODKEY,             XK_BackSpace,    killclient,     {0} },
	{ KeyPress,   MODKEY|ShiftMask,   XK_BackSpace,    killunsel,      {0} },
	{ KeyPress,   MODKEY|ShiftMask,   XK_space,        togglefloating, {0} },
	{ KeyPress,   Mod1Mask|ShiftMask, XK_q,            quit,           {0} },
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

/* vim: set noexpandtab: */
