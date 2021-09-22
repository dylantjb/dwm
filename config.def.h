/* See LICENSE file for copyright and license details. */

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
static const char *fonts[]    = { "JetBrainsMono Nerd Font:size=10", 
  "JoyPixels:pixelsize=10:antialias=true:autohint=true" };
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

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
static const Rule rules[] = {
  /* xprop(1):
   *  WM_CLASS(STRING) = instance, class
   *  WM_NAME(STRING) = title
   */
  /* class      instance    title       tags mask     isfloating   monitor */
  { "St",       NULL,       NULL,           0,            0,         -1 },
  { NULL,       NULL,       "Event Tester", 0,            0,         -1 },
  { NULL,       NULL,       "SafeEyes-0",   0,            1,         -1 },
};

/* layout(s) */
static float mfact     = 0.55;
static int nmaster     = 1;
static int resizehints = 1;
static const int lockfullscreen = 1;

#define FORCE_VSPLIT 1
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

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-i", NULL };
static const char *termcmd[]  = { "st", NULL };

/*
 * Xresources preferences to load at startup
 */
ResourcePref resources[] = {
  { "color4",  STRING, &normfgcolor },
  { "color0",  STRING, &normbgcolor },
  { "color0",  STRING, &normbordercolor },
  { "color0",  STRING, &selfgcolor },
  { "color4",  STRING, &selbgcolor },
  { "color9",  STRING, &selbordercolor },
  { "color1",  STRING, &termcol1 },
  { "color2",  STRING, &termcol2 },
  { "color3",  STRING, &termcol3 },
  { "color4",  STRING, &termcol4 },
  { "color5",  STRING, &termcol5 },
  { "color6",  STRING, &termcol6 },
  { "color7",  STRING, &termcol7 },
};

#include <X11/XF86keysym.h>
#include "shiftview.c"
static Key keys[] = {
  /* modifier         key           function        argument */
  { MODKEY,           XK_0,         view,           {.ui = ~0 } },
  { MODKEY|ShiftMask, XK_0,         tag,            {.ui = ~0 } },
  { MODKEY,           XK_Tab,       view,           {0} },
  { MODKEY,           XK_d,         spawn,          {.v = dmenucmd } },
  { MODKEY,           XK_Return,    spawn,          {.v = termcmd } },
  { MODKEY,           XK_b,         togglebar,      {0} },
  { MODKEY,           XK_j,         focusstack,     {.i = +1 } },
  { MODKEY,           XK_k,         focusstack,     {.i = -1 } },
  { MODKEY,           XK_o,         incnmaster,     {.i = +1 } },
  { MODKEY|ShiftMask, XK_o,         incnmaster,     {.i = -1 } },
  { MODKEY,           XK_h,         setmfact,       {.f = -0.05} },
  { MODKEY,           XK_l,         setmfact,       {.f = +0.05} },
  { MODKEY,           XK_space,     zoom,           {0} },
  { MODKEY,           XK_q,         killclient,     {0} },
	{ MODKEY,           XK_f,         togglefullscr,  {0} },
  { MODKEY,           XK_t,         setlayout,      {.v = &layouts[0]} },
  { MODKEY|ShiftMask, XK_t,         setlayout,      {.v = &layouts[1]} },
  { MODKEY,           XK_y,         setlayout,      {.v = &layouts[2]} },
  { MODKEY|ShiftMask, XK_space,     togglefloating, {0} },
  { MODKEY,           XK_comma,     focusmon,       {.i = -1 } },
  { MODKEY,           XK_period,    focusmon,       {.i = +1 } },
  { MODKEY|ShiftMask, XK_comma,     tagmon,         {.i = -1 } },
  { MODKEY|ShiftMask, XK_period,    tagmon,         {.i = +1 } },
  { MODKEY|ShiftMask, XK_q,         quit,           {0} },
  
  /* shiftview */
  { MODKEY,           XK_semicolon, shiftview,      {.i = 1 } },
  { MODKEY|ShiftMask, XK_semicolon, shifttag,       {.i = 1 } },
  { MODKEY,           XK_g,         shiftview,      {.i = -1 } },
  { MODKEY|ShiftMask, XK_g,         shifttag,       {.i = -1 } },

  /* gaps */
  { MODKEY,           XK_z,         incrgaps,       {.i = +3} },
  { MODKEY,           XK_x,         incrgaps,       {.i = -3} },
	{ MODKEY,           XK_a,         togglegaps,     {0} },
	{ MODKEY|ShiftMask, XK_a,         defaultgaps,    {0} },

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

  TAGKEYS(                        XK_1,                      0)
  TAGKEYS(                        XK_2,                      1)
  TAGKEYS(                        XK_3,                      2)
  TAGKEYS(                        XK_4,                      3)
  TAGKEYS(                        XK_5,                      4)
  TAGKEYS(                        XK_6,                      5)
  TAGKEYS(                        XK_7,                      6)
  TAGKEYS(                        XK_8,                      7)
  TAGKEYS(                        XK_9,                      8)
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

