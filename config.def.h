/* See LICENSE file for copyright and license details. */

/* constants */
#define TERMINAL "st"
#define TERMCLASS "St"
#define FORCE_VSPLIT 1

/* appearance */
static unsigned int borderpx  = 2;
static unsigned int snap      = 16;
static int showbar            = 1;
static int topbar             = 1;
static int smartgaps          = 0;
static unsigned int gappih = 8;
static unsigned int gappiv = 8;
static unsigned int gappoh = 6;
static unsigned int gappov = 6;
static const char *fonts[]    = { 
  "JetBrainsMono Nerd Font:size=10", 
  "JoyPixels:pixelsize=10:antialias=true:autohint=true" 
};
static char normbgcolor[]     = "#222222";
static char normbordercolor[] = "#444444";
static char normfgcolor[]     = "#bbbbbb";
static char selfgcolor[]      = "#eeeeee";
static char selbordercolor[]  = "#005577";
static char selbgcolor[]      = "#005577";

static char termcol0[]  = "#000000";
static char termcol1[]  = "#ff0000";
static char termcol2[]  = "#33ff00";
static char termcol3[]  = "#ff0099";
static char termcol4[]  = "#0066ff";
static char termcol5[]  = "#cc00ff";
static char termcol6[]  = "#00ffff";
static char termcol7[]  = "#d0d0d0";
static char termcol8[]  = "#808080";
static char termcol9[]  = "#ff0000";
static char termcol10[] = "#33ff00";
static char termcol11[] = "#ff0099";
static char termcol12[] = "#0066ff";
static char termcol13[] = "#cc00ff";
static char termcol14[] = "#00ffff";
static char termcol15[] = "#ffffff";

static char *colors[][3] = {
  /*               fg           bg           border   */
  [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
  [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

static char *termcolor[] = {
  termcol0,
  termcol1,
  termcol2,
  termcol3,
  termcol4,
  termcol5,
  termcol6,
  termcol7,
  termcol8,
  termcol9,
  termcol10,
  termcol11,
  termcol12,
  termcol13,
  termcol14,
  termcol15,
};

static const char scratchpadname[] = TERMCLASS;
static const char *scratchpadcmd[] = { TERMINAL, "-t", scratchpadname, "-g", "120x34", NULL };

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
static const Rule rules[] = {
  /* xprop(1):
   *  WM_CLASS(STRING) = instance, class
   *  WM_NAME(STRING) = title
   */
  /* class      instance    title       tags mask     isfloating   monitor */
  { TERMCLASS,  NULL,       NULL,           0,            0,         -1 },
  { NULL,       NULL,       "Event Tester", 0,            0,         -1 },
  { NULL,       NULL,       "SafeEyes-0",   0,            1,         -1 },
};

/* layout(s) */
static float mfact     = 0.55;
static int nmaster     = 1;
static int resizehints = 0;
static const int lockfullscreen = 1;

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
#define STACKKEYS(MOD,ACTION) \
  { MOD, XK_j,     ACTION##stack, {.i = INC(+1) } }, \
  { MOD, XK_k,     ACTION##stack, {.i = INC(-1) } }, \
  { MOD, XK_v,     ACTION##stack, {.i = 0 } },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[]    =  { "dmenu_run", "-i", NULL };
static const char *j4menucmd[]   =  { "j4-dmenu-desktop", "--no-generic", NULL };
static const char *termcmd[]     =  { TERMINAL, NULL };

static const char *networkcmd[]  = { "networkmanager_dmenu", NULL };
static const char *bluetoothcmd[]= { "sh", "-c", "dmenu-bluetooth", NULL };
static const char *dmenumount[]  = { "dmenumount", NULL };
static const char *dmenuumount[] = { "dmenuumount", NULL };
static const char *browsercmd[]  = { "sh", "-c", "$BROWSER", NULL };
static const char *powercmd[]    = { "rofi", "-show", "p", "-modi", "p:rofi-power-menu", "-width", "20", 
                                     "-lines", "5", NULL };

static const char *rotatewal[]   = { "wallpaper", NULL };
static const char *lfcmd[]       = { TERMINAL, "-e", "lf", NULL };
static const char *newsboat[]    = { TERMINAL, "-e", "newsboat", NULL };
static const char *emacs[]       = { "sh", "-c", "em", NULL };
static const char *skippy[]      = { "sh", "-c", "sleep 0.2; skippy-xd", NULL };
static const char *dunsthist[]   = { "dunstctl", "history-pop", NULL };
static const char *dunstclose[]  = { "dunstctl", "close-all", NULL };
static const char *notifyctl[]   = { "notifyctl", "toggle", NULL };
static const char *ncmpcpp[]     = { TERMINAL, "-e", "ncmpcpp", NULL };
static const char *keepass[]     = { "sh", "-c", "keepmenu -d ~/.local/share/keepassxc/passwords.kdbx -k "
                                                 "~/.local/share/keepassxc/passwords -a {PASSWORD}{ENTER}", NULL };
static const char *keepotp[]     = { "sh", "-c", "keepmenu -d ~/.local/share/keepassxc/codes.kdbx -k "
                                                 "~/.local/share/keepassxc/codes -a {TOTP}{ENTER}", NULL };

static const char *volup[]       = { "volume", "up", NULL };
static const char *mpcup[]       = { "mpc", "volume", "+5", NULL };
static const char *voldown[]     = { "volume", "down", NULL };
static const char *mpcdown[]     = { "mpc", "volume", "-5", NULL };
static const char *volmute[]     = { "volume", "mute", NULL };

static const char *micup[]       = { "microphone", "up", NULL };
static const char *micdown[]     = { "microphone", "down", NULL };
static const char *micmute[]     = { "microphone", "mute", NULL };

static const char *playtoggle[]  = { "playerctl", "play-pause", NULL };
static const char *mpctoggle[]   = { "mpc", "toggle", NULL };
static const char *playstop[]    = { "playerctl", "stop", NULL };
static const char *mpcstop[]     = { "mpc", "stop", NULL };
static const char *playprev[]    = { "playerctl", "previous", NULL };
static const char *mpcprev[]     = { "mpc", "prev", NULL };
static const char *playnext[]    = { "playerctl", "next", NULL };
static const char *mpcnext[]     = { "mpc", "next", NULL };

static const char *lightup[]     = { "backlight", "up", NULL };
static const char *lightdown[]   = { "backlight", "down", NULL };
static const char *printarea[]   = { "printscr", "-s", NULL };
static const char *printscreen[] = { "printscr", NULL };

/*
 * Xresources preferences to load at startup
 */
ResourcePref resources[] = {
  { "color4", STRING, &normfgcolor },
  { "color0", STRING, &normbgcolor },
  { "color0", STRING, &normbordercolor },
  { "color0", STRING, &selfgcolor },
  { "color4", STRING, &selbgcolor },
  { "color9", STRING, &selbordercolor },
  { "color1", STRING, &termcol1 },
  { "color2", STRING, &termcol2 },
  { "color3", STRING, &termcol3 },
  { "color4", STRING, &termcol4 },
  { "color5", STRING, &termcol5 },
  { "color6", STRING, &termcol6 },
  { "color7", STRING, &termcol7 },
};

#include <X11/XF86keysym.h>
#include "shiftview.c"
static Key keys[] = {
  /* modifier         key           function        argument */
  { MODKEY,           XK_0,          view,            {.ui = ~0 } },
  { MODKEY|ShiftMask, XK_0,          tag,             {.ui = ~0 } },
  { MODKEY,           XK_Tab,        view,            {0} },
  { MODKEY,           XK_q,          killclient,      {0} },
  { MODKEY|ShiftMask, XK_Return,     togglescratch,   {.v = scratchpadcmd} },
  { MODKEY,           XK_t,          setlayout,       {.v = &layouts[0]} },
  { MODKEY|ShiftMask, XK_t,          setlayout,       {.v = &layouts[1]} },
  { MODKEY,           XK_y,          setlayout,       {.v = &layouts[2]} },
  { MODKEY|ShiftMask, XK_y,          setlayout,       {.v = &layouts[3]} },
  { MODKEY,           XK_u,          setlayout,       {.v = &layouts[4]} },
  { MODKEY|ShiftMask, XK_u,          setlayout,       {.v = &layouts[5]} },
  { MODKEY,           XK_i,          setlayout,       {.v = &layouts[6]} },
  { MODKEY|ShiftMask, XK_i,          setlayout,       {.v = &layouts[7]} },
  { MODKEY,           XK_comma,      focusmon,        {.i = -1 } },
  { MODKEY,           XK_period,     focusmon,        {.i = +1 } },
  { MODKEY|ShiftMask, XK_comma,      tagmon,          {.i = -1 } },
  { MODKEY|ShiftMask, XK_period,     tagmon,          {.i = +1 } },
  { MODKEY,           XK_o,          incnmaster,      {.i = +1} },
  { MODKEY|ShiftMask, XK_o,          incnmaster,      {.i = -1} },
  { MODKEY,           XK_a,          togglegaps,      {0} },
  { MODKEY|ShiftMask, XK_a,          defaultgaps,     {0} },
  { MODKEY,           XK_f,          togglefullscr,   {0} },
  { MODKEY|ShiftMask, XK_f,          setlayout,       {.v = &layouts[8]} },
  { MODKEY,           XK_g,          shiftview,       {.i = -1} },
  { MODKEY,           XK_semicolon,  shiftview,       {.i = 1} },
  { MODKEY|ShiftMask, XK_g,          shifttag,        {.i = -1} },
  { MODKEY|ShiftMask, XK_semicolon,  shifttag,        {.i = 1} },
  { MODKEY,           XK_h,          setmfact,        {.f = -0.05} },
  { MODKEY,           XK_l,          setmfact,        {.f = +0.05} },
  { MODKEY,           XK_Return,     spawn,           {.v = termcmd} },
  { MODKEY,           XK_d,          spawn,           {.v = dmenucmd} },
  { MODKEY|ShiftMask, XK_d,          spawn,           {.v = j4menucmd} },
  { MODKEY,           XK_z,          incrgaps,        {.i = +3} },
  { MODKEY,           XK_x,          incrgaps,        {.i = -3} },
  { MODKEY,           XK_c,          togglebar,       {0} },
  { MODKEY,           XK_space,      zoom,            {0} },
  { MODKEY|ShiftMask, XK_space,      togglefloating,  {0} },

  /* { MODKEY|Mod4Mask,             XK_l, incrgaps,    {.i = -1 } }, */
  /* { MODKEY|Mod4Mask|ShiftMask,   XK_h, incrogaps,   {.i = +1 } }, */
  /* { MODKEY|Mod4Mask|ShiftMask,   XK_l, incrogaps,   {.i = -1 } }, */
  /* { MODKEY|Mod4Mask|ControlMask, XK_h, incrigaps,   {.i = +1 } }, */
  /* { MODKEY|Mod4Mask|ControlMask, XK_l, incrigaps,   {.i = -1 } }, */
  /* { MODKEY|Mod4Mask|ShiftMask,   XK_0, defaultgaps, {0} }, */
  /* { MODKEY,                      XK_y, incrihgaps,  {.i = +1 } }, */
  /* { MODKEY,                      XK_o, incrihgaps,  {.i = -1 } }, */
  /* { MODKEY|ControlMask,          XK_y, incrivgaps,  {.i = +1 } }, */
  /* { MODKEY|ControlMask,          XK_o, incrivgaps,  {.i = -1 } }, */
  /* { MODKEY|Mod4Mask,             XK_y, incrohgaps,  {.i = +1 } }, */
  /* { MODKEY|Mod4Mask,             XK_o, incrohgaps,  {.i = -1 } }, */
  /* { MODKEY|ShiftMask,            XK_y, incrovgaps,  {.i = +1 } }, */
  /* { MODKEY|ShiftMask,            XK_o, incrovgaps,  {.i = -1 } }, */

  /* custom keybindings */
  { MODKEY,           XK_r,          spawn,           {.v = lfcmd} },
  { MODKEY,           XK_p,          spawn,           {.v = keepass} },
  { MODKEY|ShiftMask, XK_p,          spawn,           {.v = keepotp} },
  { MODKEY,           XK_BackSpace,  spawn,           {.v = skippy} },
  { MODKEY,           XK_b,          spawn,           {.v = newsboat} },
  { MODKEY,           XK_e,          spawn,           {.v = emacs} },
  { MODKEY,           XK_w,          spawn,           {.v = browsercmd} },
  { MODKEY|ShiftMask, XK_w,          spawn,           {.v = rotatewal} },
  { MODKEY,           XK_m,          spawn,           {.v = dmenumount} },
  { MODKEY|ShiftMask, XK_m,          spawn,           {.v = dmenuumount} },
  { MODKEY,           XK_n,          spawn,           {.v = networkcmd} },
  { MODKEY|ShiftMask, XK_n,          spawn,           {.v = ncmpcpp} },
  { MODKEY|ShiftMask, XK_l,          spawn,           {.v = notifyctl} }, 
  { MODKEY,           XK_s,          spawn,           {.v = dunsthist} }, 
  { MODKEY|ShiftMask, XK_s,          spawn,           {.v = dunstclose} }, 
  { MODKEY|ShiftMask, XK_b,          spawn,           {.v = bluetoothcmd} },
  { MODKEY,           XK_F5,         spawn,           {.v = lightdown} },
  { MODKEY,           XK_F6,         spawn,           {.v = lightup} },

  /* function keys */
  { 0,                XF86XK_AudioRaiseVolume,  spawn,       {.v = volup} },
  { 0|MODKEY,         XF86XK_AudioRaiseVolume,  spawn,       {.v = mpcup} },
  { 0,                XF86XK_AudioLowerVolume,  spawn,       {.v = voldown} },
  { 0|MODKEY,         XF86XK_AudioLowerVolume,  spawn,       {.v = mpcdown} },
  { 0,                XF86XK_AudioMute,         spawn,       {.v = volmute} },
  { 0|ShiftMask,      XF86XK_AudioRaiseVolume,  spawn,       {.v = micup} },
  { 0|ShiftMask,      XF86XK_AudioLowerVolume,  spawn,       {.v = micdown} },
  { 0,                XF86XK_AudioMicMute,      spawn,       {.v = micmute} },
  { 0,                XF86XK_AudioPlay,         spawn,       {.v = playtoggle} },
  { 0|ShiftMask,      XF86XK_AudioPlay,         spawn,       {.v = mpctoggle} },
  { 0,                XF86XK_AudioPause,        spawn,       {.v = playtoggle} },
  { 0|ShiftMask,      XF86XK_AudioPause,        spawn,       {.v = mpctoggle} },
  { 0,                XF86XK_AudioStop,         spawn,       {.v = playstop} },
  { 0|ShiftMask,      XF86XK_AudioStop,         spawn,       {.v = mpcstop} },
  { 0,                XF86XK_AudioPrev,         spawn,       {.v = playprev} },
  { 0|ShiftMask,      XF86XK_AudioPrev,         spawn,       {.v = mpcprev} },
  { 0,                XF86XK_AudioNext,         spawn,       {.v = playnext} },
  { 0|ShiftMask,      XF86XK_AudioNext,         spawn,       {.v = mpcnext} },
  { 0,                XK_Print,                 spawn,       {.v = printarea} },
  { 0|ShiftMask,      XK_Print,                 spawn,       {.v = printscreen} },

  /* exit */
  { MODKEY|ShiftMask, XK_Delete,     quit,            {0} },
  { MODKEY|ShiftMask, XK_q,          spawn,           {.v = powercmd} },

  TAGKEYS(                        XK_1,                      0)
  TAGKEYS(                        XK_2,                      1)
  TAGKEYS(                        XK_3,                      2)
  TAGKEYS(                        XK_4,                      3)
  TAGKEYS(                        XK_5,                      4)
  TAGKEYS(                        XK_6,                      5)
  TAGKEYS(                        XK_7,                      6)
  TAGKEYS(                        XK_8,                      7)
  TAGKEYS(                        XK_9,                      8)
  STACKKEYS(MODKEY,                          focus)
  STACKKEYS(MODKEY|ShiftMask,                push)
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

