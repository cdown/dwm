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
static const char selbgcolor[]      = "#839496";
static const char selfgcolor[]      = "#002b36";

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
	/* class      instance    title       tags mask     iscentered  isfloating  respectperiod  monitor */
	{ NULL,       NULL,       "Scratch",  0,            True,       True,       False,         -1 },
	{ NULL,       NULL,       "mail",     1 << 3,       False,      False,      True,          -1 },
	{ NULL,       NULL,       "irc",      1 << 2,       False,      False,      True,          -1 },
	{ NULL,       NULL,       "mattermost",  1 << 2,    False,      False,      True,          -1 },
	{ NULL,       NULL,       pp_moni,    0,            False,      True,       False,         2  },
	{ NULL,       NULL,       pp_proj,    0,            False,      True,       False,         1  },
	{ NULL,       "google-chrome", NULL,  1 << 1,       False,      False,      True,          -1 },
};
static const int ruleperiod = 5; /* number of seconds before rules are ignored */

static const KeyRule keyrules[] = {
	/* title      modifier     keysym */
	{ "QEMU",     AnyModifier, XK_F10 },
};

/* layout(s) */
static const float mfact     = 0.5;  /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 0; /* 1 will force focus on the fullscreen window */

static const LayoutMonitorRule lm_rules[] = {
	/* >=w, >=h, req'd layout, new nmaster, new mfact */
	{ 3000, 0,   0,            3,           3/4.0 },
	{ 2500, 0,   0,            2,           2/3.0 },
};

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "|||",      col },     /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "TTT",      bstack },
	{ "HHH",      gaplessgrid },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TK(KEY,TAG) \
	{ KeyPress, MODKEY,                         KEY,  view,        {.ui = 1 << TAG} }, \
	{ KeyPress, MODKEY|ShiftMask,               KEY,  toggleview,  {.ui = 1 << TAG} }, \
	{ KeyPress, MODKEY|ControlMask,             KEY,  tag,         {.ui = 1 << TAG} }, \
	{ KeyPress, MODKEY|ControlMask|ShiftMask,   KEY,  toggletag,   {.ui = 1 << TAG} }
#define RK(MASK,KEY,ACTION) \
	{ KeyPress, MASK,                           KEY,  ACTION,      {.i  = +1 } }, \
	{ KeyPress, MASK|ShiftMask,                 KEY,  ACTION,      {.i  = -1 } }

#define AM(KEY,FLAC) \
	{ KeyPress, MODKEY,             KEY, spawn, ESHCMD("systemctl --user start ambient@" #FLAC) }, \
	{ KeyPress, MODKEY|ControlMask, KEY, spawn, ESHCMD("systemctl --user stop ambient@" #FLAC) }

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }
#define ESHCMD(cmd) SHCMD("exec " cmd)

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-i", "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };

static const char *mpdmenu_library[]  = { "mpdmenu", "-l", "::", "-i", "-l", "20", "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *mpdmenu_playlist[] = { "mpdmenu", "-p", "::", "-i", "-l", "20", "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *btmenu_connect[]  = { "btmenu", "-c", "::", "-i", "-l", "20", "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *btmenu_disconnect[] = { "btmenu", "-d", "::", "-i", "-l", "20", "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *clipmenu[]         = { "clipmenu", "-i", "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *passmenu[]         = { "passmenu-wrap", "-i", "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };

static Key keys[] = {
	TK(                    XK_i,            0               ),
	TK(                    XK_o,            1               ),
	TK(                    XK_p,            2               ),
	TK(                    XK_k,            3               ),
	TK(                    XK_l,            4               ),
	TK(                    XK_semicolon,    5               ),
	TK(                    XK_apostrophe,   6               ),
	RK(MODKEY,             XK_comma,        focusstack      ),
	RK(MODKEY|ControlMask, XK_comma,        movestack       ),
	RK(MODKEY,             XK_period,       focusmon        ),
	RK(MODKEY|ControlMask, XK_period,       tagmon          ),
	RK(MODKEY|ControlMask, XK_n,            incnmaster      ),

	RK(MODKEY|Mod1Mask|ControlMask, XK_period, tagallmon),

	AM(XK_n, rain),
	AM(XK_c, forest),

	{ KeyPress,   MODKEY,             XK_1,                    spawn,          {.v = dmenucmd } },
	{ KeyPress,   MODKEY,             XK_2,                    spawn,          {.v = passmenu } },
	{ KeyPress,   MODKEY,             XK_3,                    spawn,          {.v = clipmenu } },
	{ KeyPress,   MODKEY,             XK_4,                    spawn,          {.v = btmenu_connect } },
	{ KeyPress,   MODKEY|ControlMask, XK_4,                    spawn,          {.v = btmenu_disconnect } },
	{ KeyPress,   MODKEY,             XK_Return,               spawn,          ESHCMD("st -t Terminal") },
	{ KeyPress,   MODKEY|ShiftMask,   XK_Return,               spawn,          ESHCMD("st -t Scratch -g 160x40") },
	{ KeyPress,   MODKEY|ControlMask, XK_t,                    setlayout,      {.v = &layouts[0] } },
	{ KeyPress,   MODKEY|ControlMask, XK_b,                    setlayout,      {.v = &layouts[2] } },
	{ KeyPress,   MODKEY|ControlMask, XK_g,                    setlayout,      {.v = &layouts[3] } },
	{ KeyPress,   MODKEY|ControlMask, XK_9,                    setmfact,       {.f = -0.05} },
	{ KeyPress,   MODKEY|ControlMask, XK_0,                    setmfact,       {.f = +0.05} },
	{ KeyPress,   MODKEY|ControlMask, XK_r,                    resetlayout,    {0} },
	{ KeyPress,   MODKEY,             XK_backslash,            spawn,          ESHCMD("browser") },
	{ KeyPress,   MODKEY|ControlMask, XK_backslash,            spawn,          ESHCMD("browser --incognito") },
	{ KeyPress,   MODKEY,             XK_slash,                spawn,          {.v = mpdmenu_library } },
	{ KeyPress,   MODKEY|ControlMask, XK_slash,                spawn,          {.v = mpdmenu_playlist } },
	{ KeyPress,   MODKEY,             XK_a,                    spawn,          ESHCMD("lock-sleep") },
	{ KeyPress,   MODKEY,             XK_Prior,                spawn,          ESHCMD("pulseaudio-ctl-xob up") },
	{ KeyPress,   False,              XF86XK_AudioRaiseVolume, spawn,          ESHCMD("pulseaudio-ctl-xob up") },
	{ KeyPress,   MODKEY,             XK_Next,                 spawn,          ESHCMD("pulseaudio-ctl-xob down") },
	{ KeyPress,   False,              XF86XK_AudioLowerVolume, spawn,          ESHCMD("pulseaudio-ctl-xob down") },
	{ KeyPress,   MODKEY,             XK_m,                    spawn,          ESHCMD("pulseaudio-ctl-xob mute") },
	{ KeyPress,   False,              XF86XK_AudioMute,        spawn,          ESHCMD("pulseaudio-ctl-xob mute") },
	{ KeyPress,   MODKEY,             XK_v,                    spawn,          ESHCMD("pulseaudio-ctl-xob noop") },
	{ KeyPress,   MODKEY,             XK_Down,                 spawn,          ESHCMD("playerctl -p mpd play-pause") },
	{ KeyRelease, False,              XF86XK_AudioPause,       spawn,          ESHCMD("playerctl play-pause") },
	{ KeyRelease, False,              XF86XK_AudioPlay,        spawn,          ESHCMD("playerctl play-pause") },
	{ KeyPress,   MODKEY,             XK_Right,                spawn,          ESHCMD("playerctl -p mpd next") },
	{ KeyPress,   False,              XF86XK_AudioNext,        spawn,          ESHCMD("playerctl next") },
	{ KeyPress,   MODKEY,             XK_Left,                 spawn,          ESHCMD("playerctl -p mpd previous") },
	{ KeyPress,   False,              XF86XK_AudioPrev,        spawn,          ESHCMD("playerctl previous") },
	{ KeyRelease, MODKEY|ControlMask, XK_F10,                  spawn,          ESHCMD("screenshot --focused") },
	{ KeyRelease, MODKEY,             XK_F10,                  spawn,          ESHCMD("screenshot --all") },
	{ KeyRelease, False,              XK_F10,                  spawn,          ESHCMD("screenshot --select") },
	{ KeyPress,   MODKEY,             XK_Delete,               spawn,          ESHCMD("lockphyslock") },
	{ KeyPress,   MODKEY,             XK_t,                    spawn,          ESHCMD("trello-popup") },
	{ KeyPress,   MODKEY,             XK_d,                    spawn,          ESHCMD("notify-send \"$(world-tz)\"") },
	{ KeyPress,   MODKEY,             XK_f,                    spawn,          ESHCMD("notify-send \"$(bats)\"") },
	{ KeyPress,   MODKEY,             XK_s,                    spawn,          ESHCMD("xinput-toggle -r yubikey -n -e -t 10") },
	{ KeyPress,   MODKEY,             XK_q,                    spawn,          ESHCMD("kill-idle-shells") },
	{ KeyPress,   MODKEY,             XK_r,                    spawn,          ESHCMD("nota-todo-reminder") },
	{ KeyPress,   MODKEY,             XK_Tab,                  zoom,           {0} },
	{ KeyPress,   MODKEY,             XK_BackSpace,            killclient,     {0} },
	{ KeyPress,   MODKEY|ShiftMask,   XK_BackSpace,            killunsel,      {0} },
	{ KeyPress,   MODKEY|ShiftMask,   XK_space,                togglefloating, {0} },
	{ KeyPress,   Mod1Mask|ShiftMask, XK_q,                    quit,           {0} },
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
};

/* vim: set noexpandtab: */
