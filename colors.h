int barheight = 0;
char xresourcesfont[30];

char col_bg[] = "#282828";
char col_text[] = "#EBDBB2";
char col_black[] = "#1D2021";

/* background */
char col_bg_accent[] = "#3C3836";
char col_bg_accent_hover[] = "#504945";
char col_bg_hover[] = "#45403D";

/* blue */
char col_light_blue[] = "#83A598";
char col_light_blue_hover[] = "#8EC07C";
char col_blue[] = "#458588";
char col_blue_hover[] = "#689D6A";

/* green */
char col_light_green[] = "#B8BB26";
char col_light_green_hover[] = "#C9CA55";
char col_green[] = "#98971A";
char col_green_hover[] = "#A9A928";

/* yellow */
char col_light_yellow[] = "#FABD2F";
char col_light_yellow_hover[] = "#FFD75F";
char col_yellow[] = "#D79921";
char col_yellow_hover[] = "#E0A72D";

/* red */
char col_light_red[] = "#FB4934";
char col_light_red_hover[] = "#FF6655";
char col_red[] = "#CC241D";
char col_red_hover[] = "#E53935";

/* orange */
char col_light_orange[] = "#FE8019";
char col_light_orange_hover[] = "#FF9D3D";
char col_orange[] = "#D65D0E";
char col_orange_hover[] = "#E76F16";

/* aqua */
char col_light_aqua[] = "#8EC07C";
char col_light_aqua_hover[] = "#A9D18E";
char col_aqua[] = "#689D6A";
char col_aqua_hover[] = "#7FB77E";

const char
    *tagcolors[2]
              [5][3] = {[SchemeNoHover] = {[SchemeTagInactive] =
                                               {
                                                   [ColFg] = col_text,
                                                   [ColBg] = col_bg,
                                                   [ColDetail] = col_bg,
                                               },
                                           [SchemeTagFilled] =
                                               {
                                                   [ColFg] = col_text,
                                                   [ColBg] = col_bg_accent,
                                                   [ColDetail] = col_light_blue,
                                               },
                                           [SchemeTagFocus] =
                                               {
                                                   [ColFg] = col_black,
                                                   [ColBg] = col_light_green,
                                                   [ColDetail] = col_green,
                                               },
                                           [SchemeTagNoFocus] =
                                               {
                                                   [ColFg] = col_black,
                                                   [ColBg] = col_light_yellow,
                                                   [ColDetail] = col_yellow,
                                               },
                                           [SchemeTagEmpty] =
                                               {
                                                   [ColFg] = col_black,
                                                   [ColBg] = col_light_red,
                                                   [ColDetail] = col_red,
                                               }},
                        [SchemeHover] =
                            {[SchemeTagInactive] =
                                 {
                                     [ColFg] = col_text,
                                     [ColBg] = col_bg_hover,
                                     [ColDetail] = col_bg_hover,
                                 },
                             [SchemeTagFilled] =
                                 {
                                     [ColFg] = col_text,
                                     [ColBg] = col_bg_accent_hover,
                                     [ColDetail] = col_light_blue_hover,
                                 },
                             [SchemeTagFocus] =
                                 {
                                     [ColFg] = col_black,
                                     [ColBg] = col_light_green_hover,
                                     [ColDetail] = col_green_hover,
                                 },
                             [SchemeTagNoFocus] =
                                 {
                                     [ColFg] = col_black,
                                     [ColBg] = col_light_yellow_hover,
                                     [ColDetail] = col_yellow_hover,
                                 },
                             [SchemeTagEmpty] = {
                                 [ColFg] = col_black,
                                 [ColBg] = col_light_red_hover,
                                 [ColDetail] = col_red_hover,
                             }}};

const char *windowcolors[2][7]
                               [3] = {[SchemeNoHover] =
                                          {
                                              [SchemeWinFocus] =
                                                  {
                                                      [ColFg] = col_text,
                                                      [ColBg] = col_bg_accent,
                                                      [ColDetail] =
                                                          col_light_blue,
                                                  },
                                              [SchemeWinNormal] =
                                                  {
                                                      [ColFg] = col_text,
                                                      [ColBg] = col_bg,
                                                      [ColDetail] = col_bg,
                                                  },
                                              [SchemeWinMinimized] =
                                                  {
                                                      [ColFg] = "#928374",
                                                      [ColBg] = col_bg,
                                                      [ColDetail] = col_bg,
                                                  },
                                              [SchemeWinSticky] =
                                                  {
                                                      [ColFg] = col_black,
                                                      [ColBg] =
                                                          col_light_yellow,
                                                      [ColDetail] = col_yellow,
                                                  },
                                              [SchemeWinStickyFocus] =
                                                  {
                                                      [ColFg] = col_black, [ColBg] = col_light_aqua, [ColDetail] = col_aqua},
                                              [SchemeWinOverlay] =
                                                  {
                                                      [ColFg] = col_black,
                                                      [ColBg] = col_light_yellow,
                                                      [ColDetail] = col_yellow,
                                                  },
                                              [SchemeWinOverlayFocus] =
                                                  {
                                                      [ColFg] = col_black,
                                                      [ColBg] = col_light_green,
                                                      [ColDetail] = col_green,
                                                  },
                                          },
                                      // TODO: different hover colors
                                      [SchemeHover] =
                                          {
                                              [SchemeWinFocus] =
                                                  {
                                                      [ColFg] = col_text,
                                                      [ColBg] =
                                                          col_bg_accent_hover,
                                                      [ColDetail] =
                                                          col_light_blue_hover,
                                                  },
                                              [SchemeWinNormal] =
                                                  {
                                                      [ColFg] = col_text,
                                                      [ColBg] = col_bg_hover,
                                                      [ColDetail] =
                                                          col_bg_hover,
                                                  },
                                              [SchemeWinMinimized] =
                                                  {
                                                      [ColFg] = col_text,
                                                      [ColBg] = col_bg,
                                                      [ColDetail] = col_bg,
                                                  },
                                              [SchemeWinSticky] =
                                                  {
                                                      [ColFg] = col_black,
                                                      [ColBg] =
                                                          col_light_yellow_hover,
                                                      [ColDetail] =
                                                          col_yellow_hover,
                                                  },
                                              [SchemeWinStickyFocus] =
                                                  {[ColFg] = col_black,
                                                   [ColBg] =
                                                       col_light_aqua_hover,
                                                   [ColDetail] =
                                                       col_aqua_hover},
                                              [SchemeWinOverlay] =
                                                  {
                                                      [ColFg] = col_black,
                                                      [ColBg] =
                                                          col_light_yellow_hover,
                                                      [ColDetail] =
                                                          col_yellow_hover,
                                                  },
                                              [SchemeWinOverlayFocus] =
                                                  {
                                                      [ColFg] = col_black,
                                                      [ColBg] =
                                                          col_light_green_hover,
                                                      [ColDetail] =
                                                          col_green_hover,
                                                  },
                                          }};

const char
    *closebuttoncolors[2][3][3] =
        {[SchemeNoHover] =
             {
                 [SchemeCloseNormal] =
                     {
                         [ColFg] = col_bg,
                         [ColBg] = col_light_red,
                         [ColDetail] = col_red,
                     },
                 [SchemeCloseLocked] =
                     {
                         [ColFg] = col_bg,
                         [ColBg] = col_light_orange,
                         [ColDetail] = col_orange,
                     },
                 [SchemeCloseFullscreen] =
                     {
                         [ColFg] = col_bg,
                         [ColBg] = col_light_blue,
                         [ColDetail] = col_blue,
                     },
             },
         [SchemeHover] = {
             [SchemeCloseNormal] =
                 {
                     [ColFg] = col_bg,
                     [ColBg] = col_light_red_hover,
                     [ColDetail] = col_red_hover,
                 },
             [SchemeCloseLocked] = {[ColFg] = col_bg,
                                    [ColBg] = col_light_orange_hover,
                                    [ColDetail] = col_orange_hover},
             [SchemeCloseFullscreen] =
                 {
                     [ColFg] = col_bg,
                     [ColBg] = col_light_blue_hover,
                     [ColDetail] = col_blue_hover,
                 },
         }};

const char *bordercolors[] = {[SchemeBorderNormal] = col_bg_accent,
                                     [SchemeBorderTileFocus] = col_light_blue,
                                     [SchemeBorderFloatFocus] = col_light_green,
                                     [SchemeBorderSnap] = col_light_yellow};

const char *statusbarcolors[] = {
    [ColFg] = col_text, [ColBg] = col_bg, [ColDetail] = col_bg};

SchemePref schemehovertypes[] = {{"hover", SchemeHover},
                                 {"nohover", SchemeNoHover}};

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
    {"inactive", SchemeTagInactive}, {"filled", SchemeTagFilled},
    {"focus", SchemeTagFocus},       {"nofocus", SchemeTagNoFocus},
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
