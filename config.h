/* See LICENSE file for copyright and license details. */
#ifndef CONFIG_H
#define CONFIG_H

#include "instantwm.h"
#include "layouts.h"
#include "mouse.h"
#include "push.h"
#include "colors.h"
#include <X11/XF86keysym.h>

/* appearance */
#define BORDERPX 1                            /* border pixel of windows */
unsigned int borderpx             = BORDERPX; /* border pixel of windows */
const unsigned int snap           = 32;       /* snap pixel */
const unsigned int startmenusize  = 30;       /* snap pixel */
const unsigned int systraypinning = 0;        /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
const unsigned int systrayspacing = 0;        /* systray spacing */
const int systraypinningfailfirst = 1;        /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
int showsystray                   = 1;        /* 0 means no systray */
int showbar                       = 1;        /* 0 means no bar */
int topbar                        = 1;        /* 0 means bottom bar */
const char *fonts[]               = {"JetBrainsMonoNL Nerd Font:style=Medium:size=10", "FiraCode Nerd Font:size=10"};

/* tagging */
#define MAX_TAGLEN 16
const char *tags_default[] = {"1",  "2",  "3",  "4",  "5",  "6",  "7", "8",  "9",  "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "s"};
char tags[][MAX_TAGLEN] = {"1",  "2",  "3",  "4",  "5",  "6",  "7", "8",  "9",  "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "s"};
/* ffox, programming1, term, music, steam, folder, play icon, document, message */
const char *tagsalt[] = { "", "", "", "", "", "", "", "󰈙", "" };

const char scratchpadclass[] = "scratchpad_default";

const char *upvol[] = {"/usr/share/instantassist/utils/p.sh", "+", NULL};
const char *downvol[] = {"/usr/share/instantassist/utils/p.sh", "-", NULL};
const char *mutevol[] = {"/usr/share/instantassist/utils/p.sh", "m", NULL};

/* NOTE:
 * `rules` must be defined in exactly one .c translation unit (see `config.c`)
 * and only declared as `extern` in headers (see `globals.h`).
 *
 * Keeping a non-static definition in this header causes multiple/duplicate
 * declarations across the project, and can conflict with `extern` declarations.
 */
extern const Rule rules[];

/* layout(s) */
float mfact           = 0.55;/* factor of master area size [0.05..0.95] */
int nmaster           = 1;   /* number of clients in master area */
const int resizehints = 1;   /* 1 means respect size hints in tiled resizals */
int decorhints        = 0;   /* 1 means respect decoration hints */

const Layout layouts[] = {
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
		{ MODKEY,                       KEY, keyview,    {.ui = 1 << TAG}}, \
		{ MODKEY|ControlMask,           KEY, toggleview, {.ui = 1 << TAG}}, \
		{ MODKEY|ShiftMask,             KEY, tag,        {.ui = 1 << TAG}}, \
		{ MODKEY|Mod1Mask,              KEY, followtag,  {.ui = 1 << TAG}}, \
		{ MODKEY|ControlMask|ShiftMask, KEY, toggletag,  {.ui = 1 << TAG}}, \
		{ MODKEY|Mod1Mask|ShiftMask,    KEY, swaptags,   {.ui = 1 << TAG}},

#define SHCMD(cmd)                                                             \
    {                                                                          \
        .v = (const char *[]) { "/bin/sh", "-c", cmd, NULL }                   \
    }

/* commands */
char instantmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
const char *instantmenucmd[]     = { "dmenu_run", "-m", instantmenumon, "-c", "-l", "30", "-g", "2", "-bw", "2", NULL };
const char *instantshutdowncmd[] = {"rofi-custom", "power", NULL};
const char *quickmenucmd[]       = {"rofi-custom", NULL};
const char *startmenucmd[]       = {"rofi", "-show", "drun", "-hover-select", "-me-select-entry", "", "-me-accept-entry", "MousePrimary", NULL};
const char *termcmd[]            = {"st", NULL};
const char *slockcmd[]           = {"slock", NULL};
const char *termscratchcmd[]     = {"st", "-c", scratchpadclass, NULL};

#include "push.c"

ResourcePref resources[] = {
    {"barheight", INTEGER, &barheight},
    {"font", STRING, &xresourcesfont},

    // set tag labels
    {"tag1", STRING, &tags[0]},
    {"tag2", STRING, &tags[1]},
    {"tag3", STRING, &tags[2]},
    {"tag4", STRING, &tags[3]},
    {"tag5", STRING, &tags[4]},
    {"tag6", STRING, &tags[5]},
    {"tag7", STRING, &tags[6]},
    {"tag8", STRING, &tags[7]},
    {"tag9", STRING, &tags[8]},

};

// instantwmctl commands
Xcommand commands[] = {
    /* signum       function        default argument  arg handler*/
    // 0 means off, 1 means toggle, 2 means on
    // arg handlers:
    // 0  no argument
    // 1  binary toggle
    // 3  tag number (bitmask)
    // 4  string
    // 5  integer
    {"overlay",                setoverlay,                   {0},             0},
    {"warpfocus",              warp_to_focus,                {0},             0},
    {"tag",                    view,                         {.ui = 2},       3},
    {"animated",               toggleanimated,               {.ui = 2},       1},
    {"border",                 setborderwidth,               {.i = BORDERPX}, 5},
    {"focusfollowsmouse",      togglefocusfollowsmouse,      {.ui = 2},       1},
    {"focusfollowsfloatmouse", togglefocusfollowsfloatmouse, {.ui = 2},       1},
    {"alttab",                 alttabfree,                   {.ui = 2},       1},
    {"layout",                 commandlayout,                {.ui = 0},       1},
    {"prefix",                 commandprefix,                {.ui = 1},       1},
    {"alttag",                 togglealttag,                 {.ui = 0},       1},
    {"hidetags",               toggleshowtags,               {.ui = 0},       1},
    {"specialnext",            setspecialnext,               {.ui = 0},       3},
    {"tagmon",                 tagmon,                       {.i = +1},       0},
    {"followmon",              followmon,                    {.i = +1},       0},
    {"focusmon",               focusmon,                     {.i = +1},       0},
    {"focusnmon",              focusnmon,                    {.i = 0},        5},
    {"nametag",                nametag,                      {.v = "tag"},    4},
    {"resetnametag",           resetnametag,                 {0},             0},
    {"scratchpad-make",        scratchpad_make,              {0},             4},
    {"scratchpad-unmake",      scratchpad_unmake,            {0},             0},
    {"scratchpad-toggle",      scratchpad_toggle,            {0},             4},
    {"scratchpad-show",        scratchpad_show,              {0},             4},
    {"scratchpad-hide",        scratchpad_hide,              {0},             4},
    {"scratchpad-status",      scratchpad_status,            {0},             4},
};

Key dkeys[] = {
    /* modifier  key        function     argument */
    {0, XK_h,      viewtoleft,  {0}},
    {0, XK_l,      viewtoright, {0}},
    {0, XK_k,      shiftview,   {.i = +1}},
    {0, XK_j,      shiftview,   {.i = -1}},

    {0, XK_Left,   viewtoleft,  {0}},
    {0, XK_Right,  viewtoright, {0}},
    {0, XK_Up,     shiftview,   {.i = +1}},
    {0, XK_Down,   shiftview,   {.i = -1}},

    {0, XK_1,      view,        {.ui = 1 << 0}},
    {0, XK_2,      view,        {.ui = 1 << 1}},
    {0, XK_3,      view,        {.ui = 1 << 2}},
    {0, XK_4,      view,        {.ui = 1 << 3}},
    {0, XK_5,      view,        {.ui = 1 << 4}},
    {0, XK_6,      view,        {.ui = 1 << 5}},
    {0, XK_7,      view,        {.ui = 1 << 6}},
    {0, XK_8,      view,        {.ui = 1 << 7}},
    {0, XK_9,      view,        {.ui = 1 << 8}},

};

Key keys[] = {
    /* modifier                             key                       function                    argument */
    {MODKEY|Mod1Mask,                       XK_j,                     keyresize,                  {.i = 0}},
    {MODKEY|Mod1Mask,                       XK_k,                     keyresize,                  {.i = 1}},
    {MODKEY|Mod1Mask,                       XK_l,                     keyresize,                  {.i = 2}},
    {MODKEY|Mod1Mask,                       XK_h,                     keyresize,                  {.i = 3}},
    {MODKEY|ControlMask,                    XK_d,                     distributeclients,          {0}},
    {MODKEY|ShiftMask,                      XK_d,                     drawwindow,                 {0}},

    {MODKEY|ControlMask|Mod1Mask,           XK_r,                     redrawwin,                  {0}},
    {MODKEY,                                XK_w,                     setoverlay,                 {0}},
    {MODKEY|ControlMask,                    XK_w,                     createoverlay,              {0}},
    {MODKEY|Mod1Mask|ControlMask|ShiftMask, XK_Tab,                   alttabfree,                 {0}},
    {MODKEY|ControlMask,                    XK_h,                     hide_window,                {0}},
    {MODKEY|Mod1Mask|ControlMask,           XK_h,                     unhide_all,                 {0}},
    {MODKEY,                                XK_b,                     togglebar,                  {0}},
    {MODKEY,                                XK_j,                     focusstack,                 {.i = +1}},
    {MODKEY,                                XK_Down,                  downkey,                    {.i = +1}},
    {MODKEY|ShiftMask,                      XK_Down,                  downpress,                  {0}},
    {MODKEY,                                XK_k,                     focusstack,                 {.i = -1}},
    {MODKEY,                                XK_Up,                    upkey,                      {.i = -1}},
    {MODKEY|ShiftMask,                      XK_Up,                    uppress,                    {0}},
    {MODKEY|ControlMask,                    XK_j,                     pushdown,                   {0}},
    {MODKEY|ControlMask,                    XK_k,                     pushup,                     {0}},
    {MODKEY|Mod1Mask,                       XK_s,                     togglealttag,               {.ui = 2}},
    {MODKEY|ShiftMask|Mod1Mask,             XK_s,                     toggleanimated,             {.ui = 2}},
    {MODKEY|ControlMask,                    XK_s,                     togglesticky,               {0}},
    {MODKEY|ShiftMask,                      XK_s,                     scratchpad_make,            {.v = "default"}},
    {MODKEY,                                XK_s,                     scratchpad_toggle,          {.v = "default"}},
    {MODKEY|ShiftMask,                      XK_f,                     togglefakefullscreen,       {0}},
    {MODKEY|ControlMask,                    XK_f,                     temp_fullscreen,            {0}},
    {MODKEY|ShiftMask|Mod1Mask,             XK_d,                     toggledoubledraw,           {0}},
    {MODKEY|ShiftMask,                      XK_w,                     warp_to_focus,              {0}},
    {MODKEY|Mod1Mask,                       XK_w,                     center_window,              {0}},
    {MODKEY|ShiftMask|ControlMask,          XK_s,                     toggleshowtags,             {.ui = 2}},
    {MODKEY,                                XK_i,                     incnmaster,                 {.i = +1}},
    {MODKEY,                                XK_d,                     incnmaster,                 {.i = -1}},
    {MODKEY,                                XK_h,                     setmfact,                   {.f = -0.05}},
    {MODKEY,                                XK_l,                     setmfact,                   {.f = +0.05}},
    {MODKEY|ShiftMask,                      XK_Return,                zoom,                       {0}},
    {MODKEY,                                XK_Tab,                   lastview,                   {0}},
    {MODKEY|ShiftMask,                      XK_Tab,                   focus_last_client,          {0}},
    {MODKEY|Mod1Mask,                       XK_Tab,                   followview,                 {0}},
    {MODKEY,                                XK_q,                     shutkill,                   {0}},
    {Mod1Mask,                              XK_F4,                    killclient,                 {0}},
    {MODKEY,                                XK_F2,                    toggleprefix,               {0}},
    {MODKEY,                                XK_t,                     setlayout,                  {.v = &layouts[0]}},
    {MODKEY,                                XK_f,                     setlayout,                  {.v = &layouts[2]}},
    {MODKEY,                                XK_m,                     setlayout,                  {.v = &layouts[3]}},
    {MODKEY|ShiftMask,                      XK_m,                     movemouse,                  {0}},
    {MODKEY|Mod1Mask,                       XK_m,                     resizemouse,                {0}},
    {MODKEY,                                XK_c,                     setlayout,                  {.v = &layouts[1]}},

    {MODKEY,                                XK_Left,                  animleft,                   {0}},
    {MODKEY,                                XK_Right,                 animright,                  {0}},

    {MODKEY,                                XK_e,                     toggle_overview,            {.ui = ~0}},
    {MODKEY|ShiftMask,                      XK_e,                     toggle_fullscreen_overview, {.ui = ~0}},

    {MODKEY|ControlMask,                    XK_Left,                  direction_focus,            {.ui = 3}},
    {MODKEY|ControlMask,                    XK_Right,                 direction_focus,            {.ui = 1}},
    {MODKEY|ControlMask,                    XK_Up,                    direction_focus,            {.ui = 0}},
    {MODKEY|ControlMask,                    XK_Down,                  direction_focus,            {.ui = 2}},

    {MODKEY|ShiftMask|ControlMask,          XK_Right,                 shiftview,                  {.i = +1}},
    {MODKEY|ShiftMask|ControlMask,          XK_Left,                  shiftview,                  {.i = -1}},

    {MODKEY|Mod1Mask,                       XK_Left,                  moveleft,                   {0}},
    {MODKEY|Mod1Mask,                       XK_Right,                 moveright,                  {0}},

    {MODKEY|ShiftMask,                      XK_Left,                  tagtoleft,                  {0}},
    {MODKEY|ShiftMask,                      XK_Right,                 tagtoright,                 {0}},

    {MODKEY|ShiftMask,                      XK_j,                     moveresize,                 {.i = 0}},
    {MODKEY|ShiftMask,                      XK_k,                     moveresize,                 {.i = 1}},
    {MODKEY|ShiftMask,                      XK_l,                     moveresize,                 {.i = 2}},
    {MODKEY|ShiftMask,                      XK_h,                     moveresize,                 {.i = 3}},

    {MODKEY|ControlMask,                    XK_comma,                 cyclelayout,                {.i = -1}},
    {MODKEY|ControlMask,                    XK_period,                cyclelayout,                {.i = +1}},
    {MODKEY,                                XK_p,                     setlayout,                  {0}},
    {MODKEY|ShiftMask,                      XK_space,                 spacetoggle,                {0}},
    {MODKEY,                                XK_0,                     view,                       {.ui = ~0}},
    {MODKEY|ShiftMask,                      XK_0,                     tag,                        {.ui = ~0}},
    {MODKEY,                                XK_comma,                 focusmon,                   {.i = -1}},
    {MODKEY,                                XK_period,                focusmon,                   {.i = +1}},
    {MODKEY|ShiftMask,                      XK_comma,                 tagmon,                     {.i = -1}},
    {MODKEY|ShiftMask,                      XK_period,                tagmon,                     {.i = +1}},
    {MODKEY|Mod1Mask,                       XK_comma,                 followmon,                  {.i = -1}},
    {MODKEY|Mod1Mask,                       XK_period,                followmon,                  {.i = +1}},
    {MODKEY|ShiftMask|ControlMask|Mod1Mask, XK_period,                desktopset,                 {0}},
    TAGKEYS(XK_1,                           0)
    TAGKEYS(XK_2,                           1)
    TAGKEYS(XK_3,                           2)
    TAGKEYS(XK_4,                           3)
    TAGKEYS(XK_5,                           4)
    TAGKEYS(XK_6,                           5)
    TAGKEYS(XK_7,                           6)
    TAGKEYS(XK_8,                           7)
    TAGKEYS(XK_9,                           8)
    {MODKEY|ShiftMask|ControlMask,          XK_q,                     quit,                       {0}},
    {MODKEY,                                XK_o,                     winview,                    {0}},

};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
Button buttons[] = {
    /* click          event mask          button   function                          argument */
    {ClkLtSymbol,     0,                  Button1, cyclelayout,                      {.i = -1}},
    {ClkLtSymbol,     0,                  Button3, cyclelayout,                      {.i = +1}},
    {ClkLtSymbol,     MODKEY,             Button1, createoverlay,                    {0}},
    {ClkLtSymbol,     0,                  Button2, setlayout,                        {.v = &layouts[0]}},
    {ClkWinTitle,     0,                  Button1, window_title_mouse_handler,       {0}},
    {ClkWinTitle,     MODKEY,             Button1, setoverlay,                       {0}},
    {ClkWinTitle,     0,                  Button2, closewin,                         {0}},
    {ClkCloseButton,  0,                  Button1, killclient,                       {0}},
    {ClkCloseButton,  0,                  Button3, togglelocked,                     {0}},
    {ClkResizeWidget, 0,                  Button1, drawwindow,                       {0}},
    {ClkWinTitle,     0,                  Button3, window_title_mouse_handler_right, {0}},
    {ClkWinTitle,     0,                  Button5, focusstack,                       {.i = +1}},
    {ClkWinTitle,     0,                  Button4, focusstack,                       {.i = -1}},
    {ClkWinTitle,     ShiftMask,          Button5, pushdown,                         {0}},
    {ClkWinTitle,     ShiftMask,          Button4, pushup,                           {0}},
    {ClkWinTitle,     ControlMask,        Button5, downscaleclient,                  {0}},
    {ClkWinTitle,     ControlMask,        Button4, upscaleclient,                    {0}},
    {ClkStatusText,   0,                  Button1, spawn,                            {.v = startmenucmd}},
    {ClkStatusText,   0,                  Button2, spawn,                            {.v = termcmd}},
    {ClkStatusText,   0,                  Button3, spawn,                            {.v = quickmenucmd}},
    {ClkRootWin,      MODKEY,             Button1, setoverlay,                       {0}},
    {ClkRootWin,      0,                  Button1, spawn,                            {.v = startmenucmd} },
    {ClkRootWin,      0,                  Button3, spawn,                            {.v = termcmd} },
    {ClkRootWin,      0,                  Button4, hideoverlay,                      {0} },
    {ClkRootWin,      0,                  Button5, showoverlay,                      {0} },
    {ClkClientWin,    MODKEY,             Button1, movemouse,                        {0}},
    {ClkClientWin,    MODKEY,             Button2, toggle_floating,                  {0}},
    {ClkClientWin,    MODKEY,             Button3, resizemouse,                      {0}},
    {ClkClientWin,    MODKEY | Mod1Mask,  Button3, forceresizemouse,                 {0}},
    {ClkClientWin,    MODKEY | ShiftMask, Button3, resizeaspectmouse,                {0}},
    {ClkTagBar,       0,                  Button1, dragtag,                          {0}},
    {ClkTagBar,       0,                  Button5, viewtoright,                      {0}},
    {ClkTagBar,       MODKEY,             Button4, shiftview,                        {.i = -1}},
    {ClkTagBar,       MODKEY,             Button5, shiftview,                        {.i = +1}},
    {ClkTagBar,       0,                  Button4, viewtoleft,                       {0}},
    {ClkTagBar,       0,                  Button3, toggleview,                       {0}},
    {ClkTagBar,       MODKEY,             Button1, tag,                              {0}},
    {ClkTagBar,       Mod1Mask,           Button1, followtag,                        {0}},
    {ClkTagBar,       MODKEY,             Button3, toggletag,                        {0}},
    {ClkSideBar,      0,                  Button1, gesturemouse,                     {0}},
    {ClkShutDown,     0,                  Button1, spawn,                            {.v = instantshutdowncmd}},
    {ClkShutDown,     0,                  Button3, spawn,                            {.v = slockcmd}},
    {ClkStartMenu,    ShiftMask,          Button1, toggleprefix,                     {0}},
};
#endif
