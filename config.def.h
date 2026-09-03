/* See LICENSE file for copyright and license details. */
#include "instantwm.h"

/* appearance */
static const unsigned int borderpx       = 3;  /* border pixel of windows */
static const unsigned int snap           = 32; /* snap pixel */
static const unsigned int startmenusize  = 30; /* snap pixel */
static const unsigned int systraypinning = 0;  /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 0;  /* systray spacing */
static const int systraypinningfailfirst = 1;  /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray             = 1;  /* 0 means no systray */
static const int showbar                 = 1;  /* 0 means no bar */
static const int topbar                  = 1;  /* 0 means bottom bar */
static const char *fonts[]               = {"JetBrainsMonoNL Nerd Font:style=Medium:size=10", "FiraCode Nerd Font:size=10"};

static int barheight = 0;
static char xresourcesfont[30];

static char col_bg[]                 = "#282828";
static char col_text[]               = "#EBDBB2";
static char col_black[]              = "#1D2021";

/* background */
static char col_bg_accent[]          = "#3C3836";
static char col_bg_accent_hover[]    = "#504945";
static char col_bg_hover[]           = "#45403D";

/* blue */
static char col_light_blue[]         = "#83A598";
static char col_light_blue_hover[]   = "#8EC07C";
static char col_blue[]               = "#458588";
static char col_blue_hover[]         = "#689D6A";

/* green */
static char col_light_green[]        = "#B8BB26";
static char col_light_green_hover[]  = "#C9CA55";
static char col_green[]              = "#98971A";
static char col_green_hover[]        = "#A9A928";

/* yellow */
static char col_light_yellow[]       = "#FABD2F";
static char col_light_yellow_hover[] = "#FFD75F";
static char col_yellow[]             = "#D79921";
static char col_yellow_hover[]       = "#E0A72D";

/* red */
static char col_light_red[]          = "#FB4934";
static char col_light_red_hover[]    = "#FF6655";
static char col_red[]                = "#CC241D";
static char col_red_hover[]          = "#E53935";

/* orange */
static char col_light_orange[]       = "#FE8019";
static char col_light_orange_hover[] = "#FF9D3D";
static char col_orange[]             = "#D65D0E";
static char col_orange_hover[]       = "#E76F16";

/* aqua */
static char col_light_aqua[]         = "#8EC07C";
static char col_light_aqua_hover[]   = "#A9D18E";
static char col_aqua[]               = "#689D6A";
static char col_aqua_hover[]         = "#7FB77E";

static const char *tagcolors[2][5][3] = {
    [SchemeNoHover] = {
        [SchemeTagInactive] = {
            [ColFg] = col_text,
            [ColBg] = col_bg,
            [ColDetail] = col_bg,
        },
        [SchemeTagFilled] = {
            [ColFg] = col_text,
            [ColBg] = col_bg_accent,
            [ColDetail] = col_light_blue,
        },
        [SchemeTagFocus] = {
            [ColFg] = col_black,
            [ColBg] = col_light_green,
            [ColDetail] = col_green,
        },
        [SchemeTagNoFocus] = {
            [ColFg] = col_black,
            [ColBg] = col_light_yellow,
            [ColDetail] = col_yellow,
        },
        [SchemeTagEmpty] = {
            [ColFg] = col_black,
            [ColBg] = col_light_red,
            [ColDetail] = col_red,
        }
    },
    [SchemeHover] = {
        [SchemeTagInactive] = {
            [ColFg] = col_text,
            [ColBg] = col_bg_hover,
            [ColDetail] = col_bg_hover,
        },
        [SchemeTagFilled] = {
            [ColFg] = col_text,
            [ColBg] = col_bg_accent_hover,
            [ColDetail] = col_light_blue_hover,
        },
        [SchemeTagFocus] = {
            [ColFg] = col_black,
            [ColBg] = col_light_green_hover,
            [ColDetail] = col_green_hover,
        },
        [SchemeTagNoFocus] = {
            [ColFg] = col_black,
            [ColBg] = col_light_yellow_hover,
            [ColDetail] = col_yellow_hover,
        },
        [SchemeTagEmpty] = {
            [ColFg] = col_black,
            [ColBg] = col_light_red_hover,
            [ColDetail] = col_red_hover,
        }
    }
};

static const char *windowcolors[2][7][3] = {
    [SchemeNoHover] = {
        [SchemeWinFocus] = {
            [ColFg] = col_text,
            [ColBg] = col_bg_accent,
            [ColDetail] = col_light_blue,
        },
        [SchemeWinNormal] = {
            [ColFg] = col_text,
            [ColBg] = col_bg,
            [ColDetail] = col_bg,
        },
        [SchemeWinMinimized] = {
            [ ColFg ] = "#928374",
            [ ColBg ] = col_bg,
            [ ColDetail ] = col_bg,
        },
        [SchemeWinSticky] = {
            [ ColFg ] = col_black,
            [ ColBg ] = col_light_yellow,
            [ ColDetail ] = col_yellow,
        },
        [ SchemeWinStickyFocus ] = {
            [ ColFg ] = col_black,
            [ ColBg ] = col_light_aqua,
            [ ColDetail ] = col_aqua
        },
        [SchemeWinOverlay] = {
            [ ColFg ] = col_black,
            [ ColBg ] = col_light_yellow,
            [ ColDetail ] = col_yellow,
        },
        [SchemeWinOverlayFocus] = {
            [ ColFg ] = col_black,
            [ ColBg ] = col_light_green,
            [ ColDetail ] = col_green,
        },
    },
    //TODO: different hover colors
    [SchemeHover] = {
        [SchemeWinFocus] = {
            [ColFg] = col_text,
            [ColBg] = col_bg_accent_hover,
            [ColDetail] = col_light_blue_hover,
        },
        [SchemeWinNormal] = {
            [ColFg] = col_text,
            [ColBg] = col_bg_hover,
            [ColDetail] = col_bg_hover,
        },
        [SchemeWinMinimized] = {
            [ ColFg ] = col_text,
            [ ColBg ] = col_bg,
            [ ColDetail ] = col_bg,
        },
        [SchemeWinSticky] = {
            [ ColFg ] = col_black,
            [ ColBg ] = col_light_yellow_hover,
            [ ColDetail ] = col_yellow_hover,
        },
        [ SchemeWinStickyFocus ] = {
            [ ColFg ] = col_black,
            [ ColBg ] = col_light_aqua_hover,
            [ ColDetail ] = col_aqua_hover
        },
        [SchemeWinOverlay] = {
            [ ColFg ] = col_black,
            [ ColBg ] = col_light_yellow_hover,
            [ ColDetail ] = col_yellow_hover,
        },
        [SchemeWinOverlayFocus] = {
            [ ColFg ] = col_black,
            [ ColBg ] = col_light_green_hover,
            [ ColDetail ] = col_green_hover,
        },
    }
};

static const char *closebuttoncolors[2][3][3] = {
    [SchemeNoHover] = {
        [ SchemeCloseNormal ] = {
            [ColFg] = col_text,
            [ColBg] = col_light_red,
            [ColDetail] = col_red,
        },
        [ SchemeCloseLocked ] = {
            [ ColFg ] = col_text,
            [ ColBg ] = col_light_orange,
            [ ColDetail ] = col_orange,
        },
        [ SchemeCloseFullscreen ] = {
            [ColFg] = col_text,
            [ColBg] = col_light_red,
            [ColDetail] = col_red,
        },
    },
    [ SchemeHover ] = {
        [ SchemeCloseNormal ] = {
            [ColFg] = col_text,
            [ColBg] = col_light_red_hover,
            [ColDetail] = col_red_hover,
        },
        [ SchemeCloseLocked ] = {
            [ ColFg ] = col_text,
            [ ColBg ] = col_light_orange_hover,
            [ ColDetail ] = col_orange_hover
        },
        [ SchemeCloseFullscreen ] = {
            [ColFg] = col_text,
            [ColBg] = col_light_red_hover,
            [ColDetail] = col_red_hover,
        },
    }
};

static const char *bordercolors[] = {
    [ SchemeBorderNormal ] = col_bg_accent,
    [ SchemeBorderTileFocus ] = col_light_blue,
    [ SchemeBorderFloatFocus ] = col_light_green,
    [ SchemeBorderSnap ] = col_light_yellow
};

static const char *statusbarcolors[] = {
    [ ColFg ] = col_text,
    [ ColBg ] = col_bg,
    [ ColDetail ] = col_bg
};

SchemePref schemehovertypes[] = {
    { "hover", SchemeHover },
    { "nohover", SchemeNoHover }
};

SchemePref schemewindowtypes[] = {
    {"normal", SchemeWinNormal},
    {"minimized", SchemeWinMinimized},
    {"sticky", SchemeWinSticky},
    {"focus", SchemeWinFocus},
    {"stickyfocus", SchemeWinStickyFocus},
    {"overlay", SchemeWinOverlay},
    {"overlayfocus", SchemeWinOverlayFocus},
};

SchemePref schemetagtypes[] = {
    {"inactive", SchemeTagInactive},
    {"filled", SchemeTagFilled},
    {"focus", SchemeTagFocus},
    {"nofocus", SchemeTagNoFocus},
    {"empty", SchemeTagEmpty},
};

SchemePref schemeclosetypes[] = {
    {"normal", SchemeCloseNormal},
    {"locked", SchemeCloseLocked},
    {"fullscreen", SchemeCloseFullscreen},
};

SchemePref schemecolortypes[] = {
    {"fg", ColFg},
    {"bg", ColBg},
    {"detail", ColDetail},
};


/* tagging */
#define MAX_TAGLEN 16
static const char *tags_default[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
static char tags[][MAX_TAGLEN] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
/* ffox, programming1, term, music, steam, folder, play icon, document, message  */
static const char *tagsalt[] = { "", "", "", "", "", "", "", "󰈙", "" };

static const char scratchpadname[] = "instantscratchpad";
static const char *downvol[] = {"pactl", "set-sink-volume", "@DEFAULT_SINK@", "-10%", NULL};
static const char *upvol[] = {"pactl", "set-sink-volume", "@DEFAULT_SINK@", "+10%", NULL};
static const char *mutevol[] = {"pactl", "set-sink-mute", "@DEFAULT_SINK@", "toggle ", NULL};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class                        instance  title  tags mask  isfloating  monitor */
	{"Pavucontrol",                 NULL,     NULL,  0,         1,          -1},
	{"Onboard",                     NULL,     NULL,  0,         1,          -1},
	{"floatmenu",                   NULL,     NULL,  0,         1,          -1},
	{"Welcome.py",                  NULL,     NULL,  0,         1,          -1},
	{"Pamac-installer",             NULL,     NULL,  0,         1,          -1},
	{"xpad",                        NULL,     NULL,  0,         1,          -1},
	{"Guake",                       NULL,     NULL,  0,         1,          -1},
	{"instantfloat",                NULL,     NULL,  0,         2,          -1},
	{scratchpadname,                NULL,     NULL,  0,         4,          -1},
	{"kdeconnect.daemon",           NULL,     NULL,  0,         3,          -1},
	{"Panther",                     NULL,     NULL,  0,         3,          -1},
	{"org-wellkord-globonote-Main", NULL,     NULL,  0,         1,          -1},
	{"Peek",                        NULL,     NULL,  0,         1,          -1},
	{"ROX-Filer",                   NULL,     NULL,  0,         0,          -1},
};

/* layout(s) */
static const float mfact = 0.55;     /* factor of master area size [0.05..0.95] */
static const int nmaster = 1;        /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int decorhints  = 0;    /* 1 means respect decoration hints */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "HHH",      grid },
	{ "|||",      tcl },
	{ "H[]",      deck },
	{ "O",        overviewlayout },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
	{ NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY, TAG)                                               \
		{ MODKEY,                       KEY, view,       {.ui = 1 << TAG} }, \
		{ MODKEY|ControlMask,           KEY, toggleview, {.ui = 1 << TAG} }, \
		{ MODKEY|ShiftMask,             KEY, tag,        {.ui = 1 << TAG} }, \
		{ MODKEY|Mod1Mask,              KEY, followtag,  {.ui = 1 << TAG} }, \
		{ MODKEY|ControlMask|ShiftMask, KEY, toggletag,  {.ui = 1 << TAG} }, \
		{ MODKEY|Mod1Mask|ShiftMask,    KEY, swaptags,   {.ui = 1 << TAG} },


#define SHCMD(cmd)                                           \
	{                                                          \
		.v = (const char *[]) { "/bin/sh", "-c", cmd, NULL }     \
	}

/* commands */
static char instantmenumon[2] = "0"; /* component of instantmenucmd, manipulated in spawn() */
static const char *instantmenucmd[]     = {"instantmenu_run", NULL};
static const char *instantkeybindscmd[] = {"rofi-custom", "dwmkeybinds", NULL};
static const char *instantshutdowncmd[] = {"rofi-custom", "power", NULL};
static const char *instantswitchcmd[]   = {"rofi-custom", "window", NULL};
static const char *iswitchcmd[]         = {"iswitch", NULL};
static const char *notifycmd[]          = {"instantnotify", NULL};
static const char *onboardcmd[]         = {"onboard", NULL};
static const char *pcmanfm[]            = {"pcmanfm", NULL};
static const char *quickmenucmd[]       = {"rofi-custom", NULL};
static const char *screenshotcmd[]      = {"rofi-custom", "screenshot", NULL};
static const char *startmenucmd[]       = {"rofi-custom", "app", NULL};
static const char *termcmd[]            = {"st", NULL};
static const char *termscratchcmd[]     = {"st", "-c", scratchpadname, NULL};

#include "push.c"

ResourcePref resources[] = {
    { "barheight",        INTEGER, &barheight },
    { "font",             STRING,  &xresourcesfont },
    // set tag labels
    { "tag1",             STRING,  &tags[0] },
    { "tag2",             STRING,  &tags[1] },
    { "tag3",             STRING,  &tags[2] },
    { "tag4",             STRING,  &tags[3] },
    { "tag5",             STRING,  &tags[4] },
    { "tag6",             STRING,  &tags[5] },
    { "tag7",             STRING,  &tags[6] },
    { "tag8",             STRING,  &tags[7] },
    { "tag9",             STRING,  &tags[8] },
};

// instantwmctrl commands
static Xcommand commands[] = {
	/* signum       function        default argument  arg handler*/
	// 0 means off, 1 means toggle, 2 means on
    // arg handlers:
    // 0  no argument
    // 1  binary toggle
    // 3  tag number (bitmask)
    // 4  string
    // 5  integer
	{ "overlay",                setoverlay,                   {0}, 0 },
	{ "warpfocus",              warpfocus,                    {0}, 0 },
	{ "tag",                    view,                         {.ui = 2 }, 3 },
	{ "animated",               toggleanimated,               {.ui = 2 }, 1 },
	{ "border",                 setborderwidth,               {.i =  borderpx }, 5 },
	{ "focusfollowsmouse",      togglefocusfollowsmouse,      {.ui = 2 }, 1 },
	{ "focusfollowsfloatmouse", togglefocusfollowsfloatmouse, {.ui = 2 }, 1 },
	{ "alttab",                 alttabfree,                   {.ui = 2 }, 1 },
	{ "layout",                 commandlayout,                {.ui = 0}, 1 },
	{ "alttag",                 togglealttag,                 {.ui = 0}, 1 },
	{ "hidetags",               toggleshowtags,               {.ui = 0}, 1 },
	{ "specialnext",            setspecialnext,               {.ui = 0}, 3 },
	{ "tagmon",                 tagmon,                       {.i = +1}, 0 },
	{ "followmon",              followmon,                    {.i = +1}, 0 },
	{ "focusmon",               focusmon,                     {.i = +1}, 0 },
	{ "focusnmon",              focusnmon,                   {.i = 0}, 5 },
	{ "nametag",                nametag,                      {.v = "tag" }, 4 },
	{ "resetnametag",           resetnametag,                 {0}, 0 },
};

static const Key dkeys[] = {
	/* modifier  key        function     argument */
  {0,          XK_space,  spawn,       {.v = startmenucmd} },
	{0,          XK_q,      spawn,       {.v = instantshutdowncmd} },
	{0,          XK_p,      spawn,       {.v = pcmanfm} },
	{0,          XK_t,      spawn,       {.v = termcmd} },
	{0,          XK_s,      spawn,       {.v = instantswitchcmd} },
	{0,          XK_plus,   spawn,       {.v = upvol} },
	{0,          XK_minus,  spawn,       {.v = downvol} },
	{0,          XK_equal,  spawn,       {.v = mutevol} },

	{0,          XK_Left,   viewtoleft,  {0} },
	{0,          XK_Right,  viewtoright, {0} },
	{0,          XK_Up,     shiftview,   {.i = +1} },
	{0,          XK_Down,   shiftview,   {.i = -1} },

	{0,          XK_1,      view,        {.ui = 1 << 0} },
	{0,          XK_2,      view,        {.ui = 1 << 1} },
	{0,          XK_3,      view,        {.ui = 1 << 2} },
	{0,          XK_4,      view,        {.ui = 1 << 3} },
	{0,          XK_5,      view,        {.ui = 1 << 4} },
	{0,          XK_6,      view,        {.ui = 1 << 5} },
	{0,          XK_7,      view,        {.ui = 1 << 6} },
	{0,          XK_8,      view,        {.ui = 1 << 7} },
	{0,          XK_9,      view,        {.ui = 1 << 8} },

};

static Key keys[] = {
	/* modifier                     key            function                  argument */
	{ MODKEY,                       XK_Up,           upkey,                  {.i = -1} },
	{ MODKEY|Mod1Mask,              XK_Up,           directionfocus,         {.ui = 0} },
	{ MODKEY|ShiftMask,             XK_Up,           uppress,                {0} },
	{ MODKEY|ControlMask,           XK_Up,           pushup,                 {0} },
	{ MODKEY|ShiftMask|Mod1Mask,    XK_Up,           moveresize,             {.i = 1} },
  { MODKEY|ShiftMask|ControlMask, XK_Up,           keyresize,              {.i = 1} },
	{ MODKEY,                       XK_Down,         downkey,                {.i = +1} },
	{ MODKEY|Mod1Mask,              XK_Down,         directionfocus,         {.ui = 2 } },
	{ MODKEY|ShiftMask,             XK_Down,         downpress,              {0} },
	{ MODKEY|ControlMask,           XK_Down,         pushdown,               {0} },
	{ MODKEY|ShiftMask|Mod1Mask,    XK_Down,         moveresize,             {.i = 0} },
  { MODKEY|ShiftMask|ControlMask, XK_Down,         keyresize,              {.i = 0} },
	{ MODKEY,                       XK_Left,         animleft,               {0} },
	{ MODKEY|Mod1Mask,              XK_Left,         moveleft,               {0} },
	{ MODKEY|ShiftMask,             XK_Left,         tagtoleft,              {0} },
	{ MODKEY|Mod1Mask,              XK_Left,         directionfocus,         {.ui = 3 } },
	{ MODKEY|ControlMask,           XK_Left,         shiftview,              {.i = -1} },
	{ MODKEY|ShiftMask|Mod1Mask,    XK_Left,         moveresize,             {.i = 3} },
  { MODKEY|ShiftMask|ControlMask, XK_Left,         keyresize,              {.i = 3} },
	{ MODKEY,                       XK_Right,        animright,              {0} },
	{ MODKEY|Mod1Mask,              XK_Right,        moveright,              {0} },
	{ MODKEY|ShiftMask,             XK_Right,        tagtoright,             {0} },
	{ MODKEY|Mod1Mask,              XK_Right,        directionfocus,         {.ui = 1} },
	{ MODKEY|ControlMask,           XK_Right,        shiftview,              {.i = +1} },
	{ MODKEY|ShiftMask|Mod1Mask,    XK_Right,        moveresize,             {.i = 2} },
  { MODKEY|ShiftMask|ControlMask, XK_Right,        keyresize,              {.i = 2} },
	{ MODKEY,                       XK_Home,         setmfact,               {.f = -0.05} },
	{ MODKEY|Mod1Mask,              XK_Home,         incnmaster,             {.i = -1} },
	{ MODKEY|ShiftMask,             XK_Home,         incnmaster,             {.i = -1} },
	{ MODKEY|ShiftMask|Mod1Mask,    XK_Home,         moveresize,             {.i = 1} },
  { MODKEY|ShiftMask|ControlMask, XK_Home,         keyresize,              {.i = 1} },
  { MODKEY,                       XK_End,          setmfact,               {.f = +0.05} },
	{ MODKEY|Mod1Mask,              XK_End,          incnmaster,             {.i = +1} },
	{ MODKEY|ShiftMask,             XK_End,          incnmaster,             {.i = +1} },
	{ MODKEY|ShiftMask|Mod1Mask,    XK_End,          moveresize,             {.i = 1} },
  { MODKEY|ShiftMask|ControlMask, XK_End,          keyresize,              {.i = 1} },
	{ MODKEY,                       XK_Prior,        focusstack,             {.i = -1} },
	{ MODKEY,                       XK_Next,         focusstack,             {.i = +1} },
	{ MODKEY,                       XK_Return,       spawn,                  {.v = termcmd} },
	{ MODKEY|Mod1Mask,              XK_Return,       togglefakefullscreen,   {0} },
	{ MODKEY|ShiftMask,             XK_Return,       zoom,                   {0} },
  { MODKEY|ControlMask,           XK_Return,       tempfullscreen,         {0} },
	{ MODKEY|ShiftMask|Mod1Mask,    XK_Return,       distributeclients,      {0} },
	{ MODKEY|ShiftMask|ControlMask, XK_Return,       centerwindow,           {0} },
	{ MODKEY,                       XK_Tab,          lastview,               {0} },
	{ MODKEY|Mod1Mask,              XK_Tab,          spawn,                  {.v = iswitchcmd} },
	{ MODKEY|ShiftMask,             XK_Tab,          followview,             {0} },
	{ MODKEY|ControlMask,           XK_Tab,          focuslastclient,        {0} },
	{ MODKEY|ShiftMask|Mod1Mask,    XK_Tab,          alttabfree,             {0} },
	{ MODKEY|ShiftMask|ControlMask, XK_Tab,          desktopset,             {0} },
  { MODKEY,                       XK_space,        spacetoggle,            {0} },
  { MODKEY|ShiftMask,             XK_space,        togglefloating,         {0} },

	{ Mod1Mask,                     XK_F4,           killclient,             {0} },
	{ MODKEY,                       XK_Escape,       shutkill,               {0} },
  { MODKEY|ControlMask,           XK_Escape,       quit,                   {0} },
	{ MODKEY,                       XK_grave,        movemouse,              {0} },
	{ MODKEY|ShiftMask,             XK_grave,        resizemouse,            {0} },
	{ MODKEY|ControlMask,           XK_grave,        resizemouse,            {0} },
	{ MODKEY|ShiftMask|Mod1Mask,    XK_grave,        forceresizemouse,       {0} },
	{ MODKEY|ShiftMask|ControlMask, XK_grave,        resizeaspectmouse,      {0} },
	{ MODKEY,                       XK_apostrophe,   cyclelayout,            {.ui = 0} },
	{ MODKEY|Mod1Mask,              XK_apostrophe,   cyclelayout,            {.ui = 1} },
	{ MODKEY|ShiftMask,             XK_apostrophe,   cyclelayout,            {.ui = 2} },
	{ MODKEY|ShiftMask|Mod1Mask,    XK_apostrophe,   cyclelayout,            {.ui = 3} },
	{ MODKEY|ShiftMask|ControlMask, XK_apostrophe,   setlayout,              {.ui = 4} },
	{ MODKEY,                       XK_minus,        setoverlay,             {0} },
	{ MODKEY|Mod1Mask,              XK_minus,        toggleshowtags,         {.ui = 2 } },
	{ MODKEY|ShiftMask,             XK_minus,        createoverlay,          {0} },
	{ MODKEY|ControlMask,           XK_minus,        togglesticky,           {0} },
	{ MODKEY|ShiftMask|Mod1Mask,    XK_minus,        toggleanimated,         {.ui = 2 } },
	{ MODKEY|ShiftMask|ControlMask, XK_minus,        drawwindow,             {0} },
	{ MODKEY,                       XK_equal,        togglescratchpad,       {0} },
	{ MODKEY|Mod1Mask,              XK_equal,        togglealttag,           {.ui = 2 } },
	{ MODKEY|ShiftMask,             XK_equal,        createscratchpad,       {0} },
	{ MODKEY|ControlMask,           XK_equal,        warpfocus,              {0} },
	{ MODKEY|ShiftMask|Mod1Mask,    XK_equal,        toggledoubledraw,       {0} },
	{ MODKEY|ShiftMask|ControlMask, XK_equal,        redrawwin,              {0} },
	{ MODKEY,                       XK_slash,        spawn,                  {.v = startmenucmd} },
	{ MODKEY|Mod1Mask,              XK_slash,        spawn,                  {.v = screenshotcmd} },
	{ MODKEY|ShiftMask,             XK_slash,        spawn,                  {.v = quickmenucmd} },
	{ MODKEY|ControlMask,           XK_slash,        spawn,                  {.v = notifycmd} },
	{ MODKEY|ShiftMask|Mod1Mask,    XK_slash,        spawn,                  {.v = instantshutdowncmd} },
	{ MODKEY|ShiftMask|ControlMask, XK_slash,        spawn,                  {.v = instantkeybindscmd} },
	{ MODKEY,                       XK_backslash,    overtoggle,             {.ui = ~0} },
	{ MODKEY|Mod1Mask,              XK_backslash,    tag,                    {.ui = ~0} },
	{ MODKEY|ShiftMask,             XK_backslash,    fullovertoggle,         {.ui = ~0} },
	{ MODKEY|ControlMask,           XK_backslash,    view,                   {.ui = ~0} },
	{ MODKEY,                       XK_0,            winview,                {0} },
	{ MODKEY|Mod1Mask,              XK_0,            setlayout,              {0} },
	{ MODKEY|ShiftMask,             XK_0,            hidewin,                {0} },
	{ MODKEY|ControlMask,           XK_0,            unhideall,              {0} },
	{ MODKEY|ShiftMask|Mod1Mask,    XK_0,            togglebar,              {0} },
	{ MODKEY,                       XK_bracketleft,  focusmon,               {.i = -1} },
	{ MODKEY|Mod1Mask,              XK_bracketleft,  followmon,              {.i = -1} },
	{ MODKEY|ShiftMask,             XK_bracketleft,  tagmon,                 {.i = -1} },
	{ MODKEY,                       XK_bracketright, focusmon,               {.i = +1} },
	{ MODKEY|Mod1Mask,              XK_bracketright, followmon,              {.i = +1} },
	{ MODKEY|ShiftMask,             XK_bracketright, tagmon,                 {.i = +1} },
	TAGKEYS(XK_1, 0)
	TAGKEYS(XK_2, 1)
	TAGKEYS(XK_3, 2)
	TAGKEYS(XK_4, 3)
	TAGKEYS(XK_5, 4)
	TAGKEYS(XK_6, 5)
	TAGKEYS(XK_7, 6)
	TAGKEYS(XK_8, 7)
	TAGKEYS(XK_9, 8)
	{0}
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click          event mask          button   function           argument */
	{ ClkLtSymbol,    0,                  Button1, cyclelayout,       {.ui = 0} },
	{ ClkLtSymbol,    0,                  Button3, cyclelayout,       {.ui = 1} },
	{ ClkLtSymbol,    MODKEY,             Button1, setoverlay,        {0} },
	{ ClkLtSymbol,    MODKEY,             Button3, togglescratchpad,  {0} },
	{ ClkWinTitle,    0,                  Button1, dragmouse,         {0} },
	{ ClkWinTitle,    0,                  Button2, closewin,          {0} },
	{ ClkWinTitle,    0,                  Button3, dragrightmouse,    {0} },
	{ ClkWinTitle,    0,                  Button4, pushup,            {0} },
	{ ClkWinTitle,    0,                  Button5, pushdown,          {0} },
	{ ClkWinTitle,    MODKEY,             Button1, createoverlay,     {0} },
	{ ClkWinTitle,    MODKEY,             Button2, togglesticky,      {0} },
	{ ClkWinTitle,    MODKEY,             Button3, createscratchpad,  {0} },
	{ ClkWinTitle,    MODKEY,             Button4, upscaleclient,     {0} },
	{ ClkWinTitle,    MODKEY,             Button5, downscaleclient,   {0} },
	{ ClkCloseButton, 0,                  Button1, togglelocked,      {0} },
	{ ClkCloseButton, 0,                  Button2, killclient,        {0} },
	{ ClkCloseButton, 0,                  Button3, togglefloating,    {0} },
	{ ClkStatusText,  0,                  Button1, spawn,             {.v = startmenucmd} },
	{ ClkStatusText,  0,                  Button2, spawn,             {.v = termcmd} },
	{ ClkStatusText,  0,                  Button3, spawn,             {.v = quickmenucmd} },
	{ ClkStatusText,  MODKEY,             Button1, spawn,             {.v = instantswitchcmd} },
	{ ClkStatusText,  MODKEY,             Button3, spawn,             {.v = notifycmd} },
	{ ClkRootWin,     MODKEY,             Button1, setoverlay,        {0} },
	{ ClkRootWin,     0,                  Button1, spawn,             {.v = startmenucmd} },
	{ ClkRootWin,     0,                  Button3, spawn,             {.v = termcmd} },
	{ ClkRootWin,     0,                  Button4, hideoverlay,       {0} },
	{ ClkRootWin,     0,                  Button5, showoverlay,       {0} },
	{ ClkClientWin,   MODKEY,             Button1, movemouse,         {0} },
	{ ClkClientWin,   MODKEY,             Button2, togglefloating,    {0} },
  { ClkClientWin,   MODKEY,             Button3, resizemouse,       {0} },
	{ ClkClientWin,   MODKEY|Mod1Mask,    Button3, forceresizemouse,  {0} },
	{ ClkClientWin,   MODKEY|ShiftMask,   Button3, resizeaspectmouse, {0} },
  { ClkClientWin,   MODKEY,             Button4, focusstack,        {.i = -1} },
  { ClkClientWin,   MODKEY,             Button5, focusstack,        {.i = +1} },
  { ClkTagBar,      0,                  Button1, dragtag,           {0} },
  { ClkTagBar,      0,                  Button2, followtag,         {0} },
  { ClkTagBar,      0,                  Button3, toggleview,        {0} },
  { ClkTagBar,      0,                  Button4, viewtoleft,        {0} },
  { ClkTagBar,      0,                  Button5, viewtoright,       {0} },
  { ClkTagBar,      MODKEY,             Button1, tag,               {0} },
  { ClkTagBar,      MODKEY,             Button3, toggletag,         {0} },
  { ClkTagBar,      MODKEY,             Button4, shiftview,         {.i = -1} },
  { ClkTagBar,      MODKEY,             Button5, shiftview,         {.i = +1} },
  { ClkSideBar,     0,                  Button1, gesturemouse,      {0} },
  { ClkStartMenu,   0,                  Button1, spawn,             {.v = startmenucmd} },
  { ClkStartMenu,   0,                  Button2, spawn,             {.v = termcmd} },
  { ClkStartMenu,   0,                  Button3, spawn,             {.v = quickmenucmd} },
	{ ClkShutDown,    0,                  Button1, spawn,             {.v = instantshutdowncmd} },
};
