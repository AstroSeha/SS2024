/*
**                                Xgraphics
**                                ---------
**
**  Version 1.00 ( 28/04/96 )
**
**  Copyright (C) 1996  Martin Lueders (lueders@physik.uni-wuerzburg.de)
**
**  This program is free software; you can redistribute it and/or modify
**  it under the terms of the GNU General Public License as published by
**  the Free Software Foundation; either version 2 of the License, or
**  (at your option) any later version.
**
**  This program is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU General Public License for more details.
**
**  You should have received a copy of the GNU General Public License
**  along with this program; if not, write to the Free Software
**  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/


#include "Xgraphics.h"

# if defined(__cplusplus) || defined(c_plusplus)
#   define get_class(pvisual)   pvisual -> c_class
#else
#   define get_class(pvisual)   pvisual -> class
#endif


Display         *meindisplay;
int             meinscreen;
Window          meinwindow;
World           meinworld;
unsigned long   black,white,global_color;
int             global_function;
GC              meingc,cleargc,initgc;
XEvent          meinevent;
XSetWindowAttributes attributes;
int             buttonflag;
ButtonList      buttonlist;
unsigned long   meincolors[MAX_COLORS];
int             NofColors;
Colormap        meincmap;

world_node_t*  make_world_node();
world_node_t*  find_world_node( World world );

win_node_t*  worldlist;
win_node_t*  make_win_node();
win_node_t*  find_win_node( Window window );

/* moved colorlist and graylist from header file to here H. Todt 21.04.2016 */
static char *colorlist[MAX_COLORS] = {
(char*) "white" ,
(char*) "black" ,
(char*) "snow" ,
(char*) "ghost" ,
(char*) "GhostWhite" ,
(char*) "WhiteSmoke" ,
(char*) "gainsboro" ,
(char*) "floral" ,
(char*) "FloralWhite" ,
(char*) "old" ,
(char*) "OldLace" ,
(char*) "linen" ,
(char*) "antique" ,
(char*) "AntiqueWhite" ,
(char*) "papaya" ,
(char*) "PapayaWhip" ,
(char*) "blanched" ,
(char*) "BlanchedAlmond" ,
(char*) "bisque" ,
(char*) "peach" ,
(char*) "PeachPuff" ,
(char*) "navajo" ,
(char*) "NavajoWhite" ,
(char*) "moccasin" ,
(char*) "cornsilk" ,
(char*) "ivory" ,
(char*) "lemon" ,
(char*) "LemonChiffon" ,
(char*) "seashell" ,
(char*) "honeydew" ,
(char*) "mint" ,
(char*) "MintCream" ,
(char*) "azure" ,
(char*) "alice" ,
(char*) "AliceBlue" ,
(char*) "lavender" ,
(char*) "lavender" ,
(char*) "LavenderBlush" ,
(char*) "misty" ,
(char*) "MistyRose" ,
(char*) "white" ,
(char*) "dark" ,
(char*) "DarkSlateGray" ,
(char*) "dark" ,
(char*) "DarkSlateGrey" ,
(char*) "dim" ,
(char*) "DimGray" ,
(char*) "dim" ,
(char*) "DimGrey" ,
(char*) "slate" ,
(char*) "SlateGray" ,
(char*) "slate" ,
(char*) "SlateGrey" ,
(char*) "light" ,
(char*) "LightSlateGray" ,
(char*) "light" ,
(char*) "LightSlateGrey" ,
(char*) "gray" ,
(char*) "grey" ,
(char*) "light" ,
(char*) "LightGrey" ,
(char*) "light" ,
(char*) "LightGray" ,
(char*) "midnight" ,
(char*) "MidnightBlue" ,
(char*) "navy" ,
(char*) "navy" ,
(char*) "NavyBlue" ,
(char*) "cornflower" ,
(char*) "CornflowerBlue" ,
(char*) "dark" ,
(char*) "DarkSlateBlue" ,
(char*) "slate" ,
(char*) "SlateBlue" ,
(char*) "medium" ,
(char*) "MediumSlateBlue" ,
(char*) "light" ,
(char*) "LightSlateBlue" ,
(char*) "medium" ,
(char*) "MediumBlue" ,
(char*) "royal" ,
(char*) "RoyalBlue" ,
(char*) "blue" ,
(char*) "dodger" ,
(char*) "DodgerBlue" ,
(char*) "deep" ,
(char*) "DeepSkyBlue" ,
(char*) "sky" ,
(char*) "SkyBlue" ,
(char*) "light" ,
(char*) "LightSkyBlue" ,
(char*) "steel" ,
(char*) "SteelBlue" ,
(char*) "light" ,
(char*) "LightSteelBlue" ,
(char*) "light" ,
(char*) "LightBlue" ,
(char*) "powder" ,
(char*) "PowderBlue" ,
(char*) "pale" ,
(char*) "PaleTurquoise" ,
(char*) "dark" ,
(char*) "DarkTurquoise" ,
(char*) "medium" ,
(char*) "MediumTurquoise" ,
(char*) "turquoise" ,
(char*) "cyan" ,
(char*) "light" ,
(char*) "LightCyan" ,
(char*) "cadet" ,
(char*) "CadetBlue" ,
(char*) "medium" ,
(char*) "MediumAquamarine" ,
(char*) "aquamarine" ,
(char*) "dark" ,
(char*) "DarkGreen" ,
(char*) "dark" ,
(char*) "DarkOliveGreen" ,
(char*) "dark" ,
(char*) "DarkSeaGreen" ,
(char*) "sea" ,
(char*) "SeaGreen" ,
(char*) "medium" ,
(char*) "MediumSeaGreen" ,
(char*) "light" ,
(char*) "LightSeaGreen" ,
(char*) "pale" ,
(char*) "PaleGreen" ,
(char*) "spring" ,
(char*) "SpringGreen" ,
(char*) "lawn" ,
(char*) "LawnGreen" ,
(char*) "green" ,
(char*) "chartreuse" ,
(char*) "medium" ,
(char*) "MediumSpringGreen" ,
(char*) "green" ,
(char*) "GreenYellow" ,
(char*) "lime" ,
(char*) "LimeGreen" ,
(char*) "yellow" ,
(char*) "YellowGreen" ,
(char*) "forest" ,
(char*) "ForestGreen" ,
(char*) "olive" ,
(char*) "OliveDrab" ,
(char*) "dark" ,
(char*) "DarkKhaki" ,
(char*) "khaki" ,
(char*) "pale" ,
(char*) "PaleGoldenrod" ,
(char*) "light" ,
(char*) "LightGoldenrodYellow" ,
(char*) "light" ,
(char*) "LightYellow" ,
(char*) "yellow" ,
(char*) "gold" ,
(char*) "light" ,
(char*) "LightGoldenrod" ,
(char*) "goldenrod" ,
(char*) "dark" ,
(char*) "DarkGoldenrod" ,
(char*) "rosy" ,
(char*) "RosyBrown" ,
(char*) "indian" ,
(char*) "IndianRed" ,
(char*) "saddle" ,
(char*) "SaddleBrown" ,
(char*) "sienna" ,
(char*) "peru" ,
(char*) "burlywood" ,
(char*) "beige" ,
(char*) "wheat" ,
(char*) "sandy" ,
(char*) "SandyBrown" ,
(char*) "tan" ,
(char*) "chocolate" ,
(char*) "firebrick" ,
(char*) "brown" ,
(char*) "dark" ,
(char*) "DarkSalmon" ,
(char*) "salmon" ,
(char*) "light" ,
(char*) "LightSalmon" ,
(char*) "orange" ,
(char*) "dark" ,
(char*) "DarkOrange" ,
(char*) "coral" ,
(char*) "light" ,
(char*) "LightCoral" ,
(char*) "tomato" ,
(char*) "orange" ,
(char*) "OrangeRed" ,
(char*) "red" ,
(char*) "hot" ,
(char*) "HotPink" ,
(char*) "deep" ,
(char*) "DeepPink" ,
(char*) "pink" ,
(char*) "light" ,
(char*) "LightPink" ,
(char*) "pale" ,
(char*) "PaleVioletRed" ,
(char*) "maroon" ,
(char*) "medium" ,
(char*) "MediumVioletRed" ,
(char*) "violet" ,
(char*) "VioletRed" ,
(char*) "magenta" ,
(char*) "violet" ,
(char*) "plum" ,
(char*) "orchid" ,
(char*) "medium" ,
(char*) "MediumOrchid" ,
(char*) "dark" ,
(char*) "DarkOrchid" ,
(char*) "dark" ,
(char*) "DarkViolet" ,
(char*) "blue" ,
(char*) "BlueViolet" ,
(char*) "purple" ,
(char*) "medium" ,
(char*) "MediumPurple" ,
(char*) "thistle" ,
(char*) "snow1" ,
(char*) "snow2" ,
(char*) "snow3" ,
(char*) "snow4" ,
(char*) "seashell1" ,
(char*) "seashell2" ,
(char*) "seashell3" ,
(char*) "seashell4" ,
(char*) "AntiqueWhite1" ,
(char*) "AntiqueWhite2" ,
(char*) "AntiqueWhite3" ,
(char*) "AntiqueWhite4" ,
(char*) "bisque1" ,
(char*) "bisque2" ,
(char*) "bisque3" ,
(char*) "bisque4" ,
(char*) "PeachPuff1" ,
(char*) "PeachPuff2" ,
(char*) "PeachPuff3" ,
(char*) "PeachPuff4" ,
(char*) "NavajoWhite1" ,
(char*) "NavajoWhite2" ,
(char*) "NavajoWhite3" ,
(char*) "NavajoWhite4" ,
(char*) "LemonChiffon1" ,
(char*) "LemonChiffon2" ,
(char*) "LemonChiffon3" ,
(char*) "LemonChiffon4" ,
(char*) "cornsilk1" ,
(char*) "cornsilk2" ,
(char*) "cornsilk3" ,
(char*) "cornsilk4" ,
(char*) "ivory1" ,
(char*) "ivory2" ,
(char*) "ivory3" ,
(char*) "ivory4" ,
(char*) "honeydew1" ,
(char*) "honeydew2" ,
(char*) "honeydew3" ,
(char*) "honeydew4" ,
(char*) "LavenderBlush1" ,
(char*) "LavenderBlush2" ,
(char*) "LavenderBlush3" ,
(char*) "LavenderBlush4" ,
(char*) "MistyRose1" ,
(char*) "MistyRose2" ,
(char*) "MistyRose3" ,
(char*) "MistyRose4" ,
(char*) "azure1" ,
(char*) "azure2" ,
(char*) "azure3" ,
(char*) "azure4" ,
(char*) "SlateBlue1" ,
(char*) "SlateBlue2" ,
(char*) "SlateBlue3" ,
(char*) "SlateBlue4" ,
(char*) "RoyalBlue1" ,
(char*) "RoyalBlue2" ,
(char*) "RoyalBlue3" ,
(char*) "RoyalBlue4" ,
(char*) "blue1" ,
(char*) "blue2" ,
(char*) "blue3" ,
(char*) "blue4" ,
(char*) "DodgerBlue1" ,
(char*) "DodgerBlue2" ,
(char*) "DodgerBlue3" ,
(char*) "DodgerBlue4" ,
(char*) "SteelBlue1" ,
(char*) "SteelBlue2" ,
(char*) "SteelBlue3" ,
(char*) "SteelBlue4" ,
(char*) "DeepSkyBlue1" ,
(char*) "DeepSkyBlue2" ,
(char*) "DeepSkyBlue3" ,
(char*) "DeepSkyBlue4" ,
(char*) "SkyBlue1" ,
(char*) "SkyBlue2" ,
(char*) "SkyBlue3" ,
(char*) "SkyBlue4" ,
(char*) "LightSkyBlue1" ,
(char*) "LightSkyBlue2" ,
(char*) "LightSkyBlue3" ,
(char*) "LightSkyBlue4" ,
(char*) "SlateGray1" ,
(char*) "SlateGray2" ,
(char*) "SlateGray3" ,
(char*) "SlateGray4" ,
(char*) "LightSteelBlue1" ,
(char*) "LightSteelBlue2" ,
(char*) "LightSteelBlue3" ,
(char*) "LightSteelBlue4" ,
(char*) "LightBlue1" ,
(char*) "LightBlue2" ,
(char*) "LightBlue3" ,
(char*) "LightBlue4" ,
(char*) "LightCyan1" ,
(char*) "LightCyan2" ,
(char*) "LightCyan3" ,
(char*) "LightCyan4" ,
(char*) "PaleTurquoise1" ,
(char*) "PaleTurquoise2" ,
(char*) "PaleTurquoise3" ,
(char*) "PaleTurquoise4" ,
(char*) "CadetBlue1" ,
(char*) "CadetBlue2" ,
(char*) "CadetBlue3" ,
(char*) "CadetBlue4" ,
(char*) "turquoise1" ,
(char*) "turquoise2" ,
(char*) "turquoise3" ,
(char*) "turquoise4" ,
(char*) "cyan1" ,
(char*) "cyan2" ,
(char*) "cyan3" ,
(char*) "cyan4" ,
(char*) "DarkSlateGray1" ,
(char*) "DarkSlateGray2" ,
(char*) "DarkSlateGray3" ,
(char*) "DarkSlateGray4" ,
(char*) "aquamarine1" ,
(char*) "aquamarine2" ,
(char*) "aquamarine3" ,
(char*) "aquamarine4" ,
(char*) "DarkSeaGreen1" ,
(char*) "DarkSeaGreen2" ,
(char*) "DarkSeaGreen3" ,
(char*) "DarkSeaGreen4" ,
(char*) "SeaGreen1" ,
(char*) "SeaGreen2" ,
(char*) "SeaGreen3" ,
(char*) "SeaGreen4" ,
(char*) "PaleGreen1" ,
(char*) "PaleGreen2" ,
(char*) "PaleGreen3" ,
(char*) "PaleGreen4" ,
(char*) "SpringGreen1" ,
(char*) "SpringGreen2" ,
(char*) "SpringGreen3" ,
(char*) "SpringGreen4" ,
(char*) "green1" ,
(char*) "green2" ,
(char*) "green3" ,
(char*) "green4" ,
(char*) "chartreuse1" ,
(char*) "chartreuse2" ,
(char*) "chartreuse3" ,
(char*) "chartreuse4" ,
(char*) "OliveDrab1" ,
(char*) "OliveDrab2" ,
(char*) "OliveDrab3" ,
(char*) "OliveDrab4" ,
(char*) "DarkOliveGreen1" ,
(char*) "DarkOliveGreen2" ,
(char*) "DarkOliveGreen3" ,
(char*) "DarkOliveGreen4" ,
(char*) "khaki1" ,
(char*) "khaki2" ,
(char*) "khaki3" ,
(char*) "khaki4" ,
(char*) "LightGoldenrod1" ,
(char*) "LightGoldenrod2" ,
(char*) "LightGoldenrod3" ,
(char*) "LightGoldenrod4" ,
(char*) "LightYellow1" ,
(char*) "LightYellow2" ,
(char*) "LightYellow3" ,
(char*) "LightYellow4" ,
(char*) "yellow1" ,
(char*) "yellow2" ,
(char*) "yellow3" ,
(char*) "yellow4" ,
(char*) "gold1" ,
(char*) "gold2" ,
(char*) "gold3" ,
(char*) "gold4" ,
(char*) "goldenrod1" ,
(char*) "goldenrod2" ,
(char*) "goldenrod3" ,
(char*) "goldenrod4" ,
(char*) "DarkGoldenrod1" ,
(char*) "DarkGoldenrod2" ,
(char*) "DarkGoldenrod3" ,
(char*) "DarkGoldenrod4" ,
(char*) "RosyBrown1" ,
(char*) "RosyBrown2" ,
(char*) "RosyBrown3" ,
(char*) "RosyBrown4" ,
(char*) "IndianRed1" ,
(char*) "IndianRed2" ,
(char*) "IndianRed3" ,
(char*) "IndianRed4" ,
(char*) "sienna1" ,
(char*) "sienna2" ,
(char*) "sienna3" ,
(char*) "sienna4" ,
(char*) "burlywood1" ,
(char*) "burlywood2" ,
(char*) "burlywood3" ,
(char*) "burlywood4" ,
(char*) "wheat1" ,
(char*) "wheat2" ,
(char*) "wheat3" ,
(char*) "wheat4" ,
(char*) "tan1" ,
(char*) "tan2" ,
(char*) "tan3" ,
(char*) "tan4" ,
(char*) "chocolate1" ,
(char*) "chocolate2" ,
(char*) "chocolate3" ,
(char*) "chocolate4" ,
(char*) "firebrick1" ,
(char*) "firebrick2" ,
(char*) "firebrick3" ,
(char*) "firebrick4" ,
(char*) "brown1" ,
(char*) "brown2" ,
(char*) "brown3" ,
(char*) "brown4" ,
(char*) "salmon1" ,
(char*) "salmon2" ,
(char*) "salmon3" ,
(char*) "salmon4" ,
(char*) "LightSalmon1" ,
(char*) "LightSalmon2" ,
(char*) "LightSalmon3" ,
(char*) "LightSalmon4" ,
(char*) "orange1" ,
(char*) "orange2" ,
(char*) "orange3" ,
(char*) "orange4" ,
(char*) "DarkOrange1" ,
(char*) "DarkOrange2" ,
(char*) "DarkOrange3" ,
(char*) "DarkOrange4" ,
(char*) "coral1" ,
(char*) "coral2" ,
(char*) "coral3" ,
(char*) "coral4" ,
(char*) "tomato1" ,
(char*) "tomato2" ,
(char*) "tomato3" ,
(char*) "tomato4" ,
(char*) "OrangeRed1" ,
(char*) "OrangeRed2" ,
(char*) "OrangeRed3" ,
(char*) "OrangeRed4" ,
(char*) "red1" ,
(char*) "red2" ,
(char*) "red3" ,
(char*) "red4" ,
(char*) "DeepPink1" ,
(char*) "DeepPink2" ,
(char*) "DeepPink3" ,
(char*) "DeepPink4" ,
(char*) "HotPink1" ,
(char*) "HotPink2" ,
(char*) "HotPink3" ,
(char*) "HotPink4" ,
(char*) "pink1" ,
(char*) "pink2" ,
(char*) "pink3" ,
(char*) "pink4" ,
(char*) "LightPink1" ,
(char*) "LightPink2" ,
(char*) "LightPink3" ,
(char*) "LightPink4" ,
(char*) "PaleVioletRed1" ,
(char*) "PaleVioletRed2" ,
(char*) "PaleVioletRed3" ,
(char*) "PaleVioletRed4" ,
(char*) "maroon1" ,
(char*) "maroon2" ,
(char*) "maroon3" ,
(char*) "maroon4" ,
(char*) "VioletRed1" ,
(char*) "VioletRed2" ,
(char*) "VioletRed3" ,
(char*) "VioletRed4" ,
(char*) "magenta1" ,
(char*) "magenta2" ,
(char*) "magenta3" ,
(char*) "magenta4" ,
(char*) "orchid1" ,
(char*) "orchid2" ,
(char*) "orchid3" ,
(char*) "orchid4" ,
(char*) "plum1" ,
(char*) "plum2" ,
(char*) "plum3" ,
(char*) "plum4" ,
(char*) "MediumOrchid1" ,
(char*) "MediumOrchid2" ,
(char*) "MediumOrchid3" ,
(char*) "MediumOrchid4" ,
(char*) "DarkOrchid1" ,
(char*) "DarkOrchid2" ,
(char*) "DarkOrchid3" ,
(char*) "DarkOrchid4" ,
(char*) "purple1" ,
(char*) "purple2" ,
(char*) "purple3" ,
(char*) "purple4" ,
(char*) "MediumPurple1" ,
(char*) "MediumPurple2" ,
(char*) "MediumPurple3" ,
(char*) "MediumPurple4" ,
(char*) "thistle1" ,
(char*) "thistle2" ,
(char*) "thistle3" ,
(char*) "thistle4" ,
(char*) "gray0" ,
(char*) "grey0" ,
(char*) "gray1" ,
(char*) "grey1" ,
(char*) "gray2" ,
(char*) "grey2" ,
(char*) "gray3" ,
(char*) "grey3" ,
(char*) "gray4" ,
(char*) "grey4" ,
(char*) "gray5" ,
(char*) "grey5" ,
(char*) "gray6" ,
(char*) "grey6" ,
(char*) "gray7" ,
(char*) "grey7" ,
(char*) "gray8" ,
(char*) "grey8" ,
(char*) "gray9" ,
(char*) "grey9" ,
(char*) "gray10" ,
(char*) "grey10" ,
(char*) "gray11" ,
(char*) "grey11" ,
(char*) "gray12" ,
(char*) "grey12" ,
(char*) "gray13" ,
(char*) "grey13" ,
(char*) "gray14" ,
(char*) "grey14" ,
(char*) "gray15" ,
(char*) "grey15" ,
(char*) "gray16" ,
(char*) "grey16" ,
(char*) "gray17" ,
(char*) "grey17" ,
(char*) "gray18" ,
(char*) "grey18" ,
(char*) "gray19" ,
(char*) "grey19" ,
(char*) "gray20" ,
(char*) "grey20" ,
(char*) "gray21" ,
(char*) "grey21" ,
(char*) "gray22" ,
(char*) "grey22" ,
(char*) "gray23" ,
(char*) "grey23" ,
(char*) "gray24" ,
(char*) "grey24" ,
(char*) "gray25" ,
(char*) "grey25" ,
(char*) "gray26" ,
(char*) "grey26" ,
(char*) "gray27" ,
(char*) "grey27" ,
(char*) "gray28" ,
(char*) "grey28" ,
(char*) "gray29" ,
(char*) "grey29" ,
(char*) "gray30" ,
(char*) "grey30" ,
(char*) "gray31" ,
(char*) "grey31" ,
(char*) "gray32" ,
(char*) "grey32" ,
(char*) "gray33" ,
(char*) "grey33" ,
(char*) "gray34" ,
(char*) "grey34" ,
(char*) "gray35" ,
(char*) "grey35" ,
(char*) "gray36" ,
(char*) "grey36" ,
(char*) "gray37" ,
(char*) "grey37" ,
(char*) "gray38" ,
(char*) "grey38" ,
(char*) "gray39" ,
(char*) "grey39" ,
(char*) "gray40" ,
(char*) "grey40" ,
(char*) "gray41" ,
(char*) "grey41" ,
(char*) "gray42" ,
(char*) "grey42" ,
(char*) "gray43" ,
(char*) "grey43" ,
(char*) "gray44" ,
(char*) "grey44" ,
(char*) "gray45" ,
(char*) "grey45" ,
(char*) "gray46" ,
(char*) "grey46" ,
(char*) "gray47" ,
(char*) "grey47" ,
(char*) "gray48" ,
(char*) "grey48" ,
(char*) "gray49" ,
(char*) "grey49" ,
(char*) "gray50" ,
(char*) "grey50" ,
(char*) "gray51" ,
(char*) "grey51" ,
(char*) "gray52" ,
(char*) "grey52" ,
(char*) "gray53" ,
(char*) "grey53" ,
(char*) "gray54" ,
(char*) "grey54" ,
(char*) "gray55" ,
(char*) "grey55" ,
(char*) "gray56" ,
(char*) "grey56" ,
(char*) "gray57" ,
(char*) "grey57" ,
(char*) "gray58" ,
(char*) "grey58" ,
(char*) "gray59" ,
(char*) "grey59" ,
(char*) "gray60" ,
(char*) "grey60" ,
(char*) "gray61" ,
(char*) "grey61" ,
(char*) "gray62" ,
(char*) "grey62" ,
(char*) "gray63" ,
(char*) "grey63" ,
(char*) "gray64" ,
(char*) "grey64" ,
(char*) "gray65" ,
(char*) "grey65" ,
(char*) "gray66" ,
(char*) "grey66" ,
(char*) "gray67" ,
(char*) "grey67" ,
(char*) "gray68" ,
(char*) "grey68" ,
(char*) "gray69" ,
(char*) "grey69" ,
(char*) "gray70" ,
(char*) "grey70" ,
(char*) "gray71" ,
(char*) "grey71" ,
(char*) "gray72" ,
(char*) "grey72" ,
(char*) "gray73" ,
(char*) "grey73" ,
(char*) "gray74" ,
(char*) "grey74" ,
(char*) "gray75" ,
(char*) "grey75" ,
(char*) "gray76" ,
(char*) "grey76" ,
(char*) "gray77" ,
(char*) "grey77" ,
(char*) "gray78" ,
(char*) "grey78" ,
(char*) "gray79" ,
(char*) "grey79" ,
(char*) "gray80" ,
(char*) "grey80" ,
(char*) "gray81" ,
(char*) "grey81" ,
(char*) "gray82" ,
(char*) "grey82" ,
(char*) "gray83" ,
(char*) "grey83" ,
(char*) "gray84" ,
(char*) "grey84" ,
(char*) "gray85" ,
(char*) "grey85" ,
(char*) "gray86" ,
(char*) "grey86" ,
(char*) "gray87" ,
(char*) "grey87" ,
(char*) "gray88" ,
(char*) "grey88" ,
(char*) "gray89" ,
(char*) "grey89" ,
(char*) "gray90" ,
(char*) "grey90" ,
(char*) "gray91" ,
(char*) "grey91" ,
(char*) "gray92" ,
(char*) "grey92" ,
(char*) "gray93" ,
(char*) "grey93" ,
(char*) "gray94" ,
(char*) "grey94" ,
(char*) "gray95" ,
(char*) "grey95" ,
(char*) "gray96" ,
(char*) "grey96" ,
(char*) "gray97" ,
(char*) "grey97" ,
(char*) "gray98" ,
(char*) "grey98" ,
(char*) "gray99" ,
(char*) "grey99" ,
(char*) "gray100" ,
(char*) "grey100" ,
(char*) "dark" ,
(char*) "DarkGrey" ,
(char*) "dark" ,
(char*) "DarkGray" ,
(char*) "dark" ,
(char*) "DarkBlue" ,
(char*) "dark" ,
(char*) "DarkCyan" ,
(char*) "dark" ,
(char*) "DarkMagenta" ,
(char*) "dark" ,
(char*) "DarkRed" ,
(char*) "light" ,
(char*) "LightGreen" 
};

/* moved colorlist and graylist from header file to here H. Todt 21.04.2016 */
static char *graylist[MAX_GRAYS] = {
  (char*)"white",
  (char*)"black",
  (char*)"gray90",
  (char*)"gray85",
  (char*)"gray80",
  (char*)"gray75",
  (char*)"gray70",
  (char*)"gray65",
  (char*)"gray60",
  (char*)"gray55",
  (char*)"gray50",
  (char*)"gray45",
  (char*)"gray40",
  (char*)"gray35",
  (char*)"gray30",
  (char*)"gray25",
  (char*)"gray20"
};

 
void InitX()
{
  char **fontlist;
  int  i,count;
  Font meinfont;
  char meinfontpattern[40];
  XColor col, colexact;

  /* set display to value of environment DISPLAY */
  
  meindisplay=XOpenDisplay("");
  if (meindisplay==NULL) {
    printf("Cannot connect to X Server\n");
    exit(0);
  }
  meinscreen=DefaultScreen(meindisplay);
  
  /* set colors */

  meincmap = DefaultColormap(meindisplay,meinscreen);
  
  black=BlackPixel(meindisplay,meinscreen);
  white=WhitePixel(meindisplay,meinscreen);
  global_color = black;
  global_function = GXcopy;

  meingc    = XCreateGC(meindisplay,DefaultRootWindow(meindisplay),0,0);
  cleargc = XCreateGC(meindisplay,DefaultRootWindow(meindisplay),0,0);
  initgc  = XCreateGC(meindisplay,DefaultRootWindow(meindisplay),0,0);
  
  XSetForeground(meindisplay,meingc,black);
  XSetBackground(meindisplay,meingc,white);
  
  XSetForeground(meindisplay,cleargc,white);
  XSetBackground(meindisplay,cleargc,black);
  
  XFlush(meindisplay);
  
  if( DefaultDepth(meindisplay,meinscreen) == 1 ) {

    meincolors[0] = white;
    meincolors[1] = black;
    NofColors = 2;

  } else {
    if ( get_class(DefaultVisual(meindisplay,meinscreen)) < 2 ) {
      for(i=NofColors=0;i<MAX_GRAYS;++i) {
	if (XAllocNamedColor(meindisplay,meincmap,graylist[i],&col,&colexact) )
	  meincolors[NofColors++] = col.pixel; 
      }
    } else {
      for(i=NofColors=0;i<MAX_COLORS;++i) {
	if (XAllocNamedColor(meindisplay,meincmap,colorlist[i],&col,&colexact) )
	  meincolors[NofColors++] = col.pixel;
      }
    }
  }

  /* set default font */

  strcpy(meinfontpattern,"-*-helvetica-bold-r-normal--14*");

  fontlist = XListFonts(meindisplay,meinfontpattern,20,&count);
  if(count) {
    meinfont=XLoadFont(meindisplay,meinfontpattern);
    XSetFont(meindisplay,meingc,meinfont);
  } /* if */
  XFreeFontNames(fontlist);

  XCopyGC(meindisplay,meingc,-1,initgc);
  
  /* reset internal lists */

  worldlist = (struct win_node *) NULL;
  buttonflag = 0;
  buttonlist.buttons = (ButtonType *) NULL;
  buttonlist.NofButtons = 0;
}


/*****************************************************************************/

void ExitX()
{
  /* destroy remaining windows */

  while(worldlist) DestroyWindow(worldlist->win);

  /* free memory */

  if ( buttonlist.buttons ) free ( buttonlist.buttons );

  XFreeGC(meindisplay,meingc);
  XFreeGC(meindisplay,cleargc);
  
  XCloseDisplay(meindisplay);
}

/*****************************************************************************/

/* internal world- and win- handling */

struct world_node *make_world_node()
{
  return( (struct world_node *) calloc(1,sizeof(struct world_node)) );
}

struct win_node *make_win_node()
{
  return( (struct win_node *) calloc(1,sizeof(struct win_node)) );
}

struct win_node *find_win_node(Window window)
{
  struct win_node *winptr;
  int notfound=1;

  winptr = worldlist;

  while(winptr && notfound) {
    if( winptr->win == window ) notfound = 0;
    else winptr = winptr->nextwin;
  }
  return winptr;
}

struct world_node *find_world_node(World world)
{
  struct world_node *worldptr;
  int notfound=1;

  worldptr = find_win_node(world->win)->nextworld;

  while(worldptr && notfound) {
    if( worldptr->world == world ) notfound = 0;
    else worldptr = worldptr->nextworld;
  }
  return worldptr;
}


/*****************************************************************************/

Window CreateWindow(int width, int height, const char *sname)
{
  Window tmp;
  struct win_node *winptr;

  /* changed char *name to const char *sname, H.Todt 28.4.2016 therefore: */
  char *name = (char*) sname ;
  XSizeHints *sizehints;
  XWMHints   *wmhints;
  XClassHint *classhints;
  XTextProperty windowname, iconname;


  /* define window attributes */

  if(!(sizehints=XAllocSizeHints())){
    fprintf(stderr,"Xgraphics: failure allocating memory\n");
    exit(-1);
  }

  if(!(wmhints=XAllocWMHints())){
    fprintf(stderr,"Xgraphics: failure allocating memory\n");
    exit(-1);
  }

  if(!(classhints=XAllocClassHint())){
    fprintf(stderr,"Xgraphics: failure allocating memory\n");
    exit(-1);
  }

  if(XStringListToTextProperty(&name,1,&windowname) ==0) {
    fprintf(stderr,"Xgraphics: failure allocating structure\n");
    exit(-1);
  }

  if(XStringListToTextProperty(&name,1,&iconname) ==0) {
    fprintf(stderr,"Xgraphics: failure allocating structure\n");
    exit(-1);
  }

  wmhints->initial_state = NormalState;
  wmhints->input = True;
  wmhints->flags = StateHint | InputHint;

/*
  sizehints->base_width = width;
  sizehints->base_height = height;
  sizehints->flags = PBaseSize;
*/

  attributes.backing_store    = Always;
  attributes.background_pixel = white;

  /* create a window */

  tmp =  XCreateWindow(meindisplay,DefaultRootWindow(meindisplay),
             200,200,width,height,                      /* coords */
             17,CopyFromParent,            /* border width, depth */
             InputOutput,                                /* class */
             CopyFromParent,                       /* visual type */
             CWBackingStore|
	     CWBackPixel,                            /* valuemask */
             &attributes);                          /* attributes */
  
  XSelectInput(meindisplay,tmp,
	    OwnerGrabButtonMask |   
            ButtonPressMask | ButtonReleaseMask |         /* Mouse */
            EnterWindowMask |               /* Mouse enters Window */
	    StructureNotifyMask |              /* Geometry changes */
            KeyPressMask    |                          /* Keyboard */
            ExposureMask);                    /* Window - Exposure */

  XSetWMProperties(meindisplay,tmp,&windowname,&iconname,NULL,0,sizehints,
		   wmhints,classhints);


  /* update window/world - database */

  winptr    = worldlist;
  worldlist = make_win_node();

  worldlist->nextwin   = winptr;
  worldlist->prevwin   = (struct win_node *) NULL;
  worldlist->nextworld = (struct world_node *) NULL;
  worldlist->win       = tmp;

  if(winptr) winptr->prevwin = worldlist;

  return tmp;
}
  
/*****************************************************************************/

void ShowWindow(Window win)
{
  XMapRaised(meindisplay,win);
}

void HideWindow(Window win)
{
  XUnmapWindow(meindisplay,win);
  XSync(meindisplay,True);
}

/*****************************************************************************/

void DestroyWindow(Window win)
{
  struct win_node   *winptr;
  /* not used in this function H. Todt 21.04.2016 */
  /* struct world_node *worldptr; */

  /* find entry in database */
  winptr = find_win_node(win);
  /* not used in this function H. Todt 21.04.2016 */
  /* worldptr = winptr->nextworld; */

  /* destroy worlds within this window */
  while(winptr->nextworld) DestroyWorld(winptr->nextworld->world);

  /* delete database-entry */
  if(winptr->nextwin) winptr->nextwin->prevwin = winptr->prevwin;
  if(winptr->prevwin) winptr->prevwin->nextwin = winptr->nextwin;
  else worldlist = winptr->nextwin;

  /* destroy window */
  XDestroyWindow(meindisplay,win);
  free(winptr);
}

void DestroyWorld(World world) 
{
  struct world_node *worldptr;
  
  /* find database-entry */
  worldptr = find_world_node(world);

  /* free GC's */
  if(world->clipping) XFreeGC(meindisplay,world->gcw);
  if(world->gcp != meingc) XFreeGC(meindisplay,world->gcp);

  /* delete database-entry */
  if(worldptr->nextworld) worldptr->nextworld->prevworld = worldptr->prevworld;
  if(worldptr->prevworld) worldptr->prevworld->nextworld = worldptr->nextworld;
  else find_win_node(world->win)->nextworld = worldptr->nextworld;

  /* destroy world */
  free(world);
  free(worldptr);
}


/*****************************************************************************/

void ClearWindow(Window win)
{
  XClearWindow(meindisplay,win);
}

/*****************************************************************************/

World CreateWorld(Window window, int px, int py, int pwidth, int pheight,
		  double wx1, double wy1, double wx2, double wy2,
		  int scalable, int gravity)
{
 
  World  tmpworld;
  struct win_node   *winptr;
  struct world_node *worldptr;
  Window tmp;
  int    gx,gy;
  unsigned int gb,gd;
  XRectangle rect;

  /* create world (memory) */
  tmpworld = (World) calloc(1,sizeof(Worldstruct));

  /* if neccessary create window */
  if(window == 0) { tmpworld->win = CreateWindow(px+pwidth,py+pheight,(char*)"");
		    ShowWindow(tmpworld->win); }
  else            tmpworld->win = window;

  /* create Backing-storage Pixmap */
  if( !scalable ) {
    tmpworld->pixmap = XCreatePixmap(meindisplay,tmpworld->win,pwidth,pheight,
				    DefaultDepth(meindisplay,meinscreen));
    XFillRectangle(meindisplay,tmpworld->pixmap,cleargc,0,0,pwidth,pheight);
  }
  else
    tmpworld->pixmap = 0;

  /* set coords */
  tmpworld->px = px;
  tmpworld->py = py;
  tmpworld->pwidth  = pwidth;
  tmpworld->pheight = pheight;
  
  tmpworld->bbx = px;
  tmpworld->bby = py;
  tmpworld->bbwidth = pwidth;
  tmpworld->bbheight = pheight;

  tmpworld->x1 = wx1;
  tmpworld->y1 = wy1;
  tmpworld->x2 = wx2;
  tmpworld->y2 = wy2;

  tmpworld->fx = (double)(pwidth-1)/(wx2-wx1);
  tmpworld->fy = (double)(pheight-1)/(wy2-wy1);

  tmpworld->aspect = (double)pheight/(double)pwidth;

  /* get coords of window */
  XGetGeometry(meindisplay,tmpworld->win,&tmp,&gx,&gy,
	       &(tmpworld->winwidth),&(tmpworld->winheight),&gb,&gd);

  /* set params */
  tmpworld->scalable = scalable;
  tmpworld->gravity  = gravity;
  tmpworld->clipping = CLIPPING;

  /* create CG for Pixmap */
  tmpworld->gcp = XCreateGC(meindisplay,DefaultRootWindow(meindisplay),0,0);
  XCopyGC(meindisplay,initgc,-1,tmpworld->gcp);

  /* create CG for world */
  if (CLIPPING) {
    tmpworld->gcw = XCreateGC(meindisplay,DefaultRootWindow(meindisplay),0,0);
    XCopyGC(meindisplay,initgc,-1,tmpworld->gcw);
    rect.x = px;
    rect.y = py;
    rect.width  = pwidth;
    rect.height = pheight;
    XSetClipRectangles(meindisplay,tmpworld->gcw,0,0,&rect,1,Unsorted);
  } else 
    tmpworld->gcw = tmpworld->gcp;

  /* set default color */
  tmpworld->color = black;
  tmpworld->function = GXcopy;

  /* create database-entry */
  winptr = find_win_node(tmpworld->win);
  if(winptr){
    worldptr = winptr->nextworld;
    winptr->nextworld = make_world_node();
    winptr->nextworld->world = tmpworld;
    winptr->nextworld->nextworld = worldptr;
    winptr->nextworld->prevworld = (struct world_node *) NULL;

    if(worldptr) worldptr->prevworld = winptr->nextworld;
  }
  else { fprintf(stderr,"Problems with alloc !\n"); exit(0); }

  return tmpworld;
}  

/*****************************************************************************/

void ClearWorld(World world)
{
  ClearArea(world->win,world->px,world->py,world->pwidth,world->pheight);

  if(world->pixmap) XFillRectangle(meindisplay,world->pixmap,cleargc,
				  0,0,
				  world->pwidth,world->pheight);
  XFlush(meindisplay);
}

/*****************************************************************************/

void ExposeWorld(World world)
{
  if(world->pixmap) {
    XCopyArea(meindisplay,world->pixmap,world->win,meingc,0,0,
	      world->pwidth,world->pheight,
	      world->px,world->py);
    XFlush(meindisplay);
  }
}

/*****************************************************************************/

void ResizeWorld(World world, int newwidth, int newheight)
{
  int delta_width, delta_height, bbx_a, bby_a;
  XRectangle rect;

  /* differences in size */
  delta_width  = (newwidth-world->winwidth);
  delta_height = (newheight-world->winheight);

  /* bounding-box */
  bbx_a = world->bbx;
  bby_a = world->bby;

  /* new coords for non-scalable worlds */
  if( !(world->scalable) )
    switch(world->gravity) {
    case NorthGravity:
      world->px += delta_width/2;
      break;
      
    case EastGravity:
      world->px += delta_width;
      world->py += delta_height/2;
      break;
      
    case SouthGravity:
      world->px += delta_width/2;
      world->py += delta_height;
      break;
      
    case WestGravity:
      world->py += delta_height/2;
      break;
      
    case NorthEastGravity:
      world->px += delta_width;
      break;
      
    case SouthEastGravity:
      world->px += delta_width;
      world->py += delta_height;
      break;
      
    case SouthWestGravity:
      world->py += delta_height;
      break;
      
    case NorthWestGravity:
    default:
      break;

  } else {

  /* scalable worlds */
    if( world->scalable & FIXED_WIDTH ) {
      switch(world->gravity) {
      case NorthWestGravity:
      case WestGravity:
      case SouthWestGravity:
	break;
      case NorthEastGravity:
      case EastGravity:
      case SouthEastGravity:
	world->bbx += delta_width;
	break;
      default:
	world->bbx += delta_width/2;
	break;
      }
    } else {
      world->bbx += (world->scalable & FLOAT_WEST)  ? 
	world->bbx*(delta_width/(double)(world->winwidth)) : 0;
      
      world->bbwidth = (world->scalable & FLOAT_EAST) ? 
	(bbx_a + world->bbwidth)*
	  (newwidth/(double)(world->winwidth)) - world->bbx:
	  (world->bbwidth + delta_width) + (bbx_a - world->bbx);
    }
    
    if( world->scalable & FIXED_HEIGHT ) {
      switch(world->gravity) {
      case NorthEastGravity:
      case NorthGravity:
      case NorthWestGravity:
	break;
      case SouthEastGravity:
      case SouthGravity:
      case SouthWestGravity:
	world->bby += delta_height;
	break;
      default:
	world->bby += delta_height/2;
	break;
      }
    } else {
      
      world->bby += (world->scalable & FLOAT_NORTH) ? 
	world->bby*(delta_height/(double)(world->winheight)) : 0;
      
      world->bbheight = (world->scalable & FLOAT_SOUTH) ? 
	(bby_a + world->bbheight)*
	  (newheight/(double)(world->winheight)) - world->bby:
	  (world->bbheight + delta_height) + (bby_a - world->bby);
    }
    
    if ( world->scalable & FREE_ASPECT ) {
      world->px = world->bbx; world->py = world->bby;
      world->pwidth = world->bbwidth; world->pheight = world->bbheight;
    } else {
      if ( world->bbwidth * world->aspect > world->bbheight ) {
	world->pheight = world->bbheight;
	world->pwidth = world->pheight/world->aspect;
	world->py = world->bby;
	world->px = world->bbx + (world->bbwidth - world->pwidth)/2;
      } else {
	world->pwidth = world->bbwidth;
	world->pheight = world->pwidth*world->aspect;
	world->px = world->bbx;
	world->py = world->bby + (world->bbheight - world->pheight)/2;
      }
    }
 
    world->fx = (double)(world->pwidth-1)/(world->x2 - world->x1);
    world->fy = (double)(world->pheight-1)/(world->y2 - world->y1);
  }
  world->winwidth  = newwidth;
  world->winheight = newheight;

  if ( world->pwidth  < 1 ) world->pwidth  = 1;
  if ( world->pheight < 1 ) world->pheight = 1;
  
  world->aspect = (double)world->pheight/(double)world->pwidth;
  if (world->clipping) {
    rect.x = world->px;
    rect.y = world->py;
    rect.width  = world->pwidth;
    rect.height = world->pheight;
    XSetClipRectangles(meindisplay,world->gcw,0,0,&rect,1,Unsorted);
  }
}

/*****************************************************************************/

void    RescaleWorld(World world, double nx1, double ny1, double nx2, double ny2)
{
  world->x1 = nx1;
  world->y1 = ny1;
  world->x2 = nx2;
  world->y2 = ny2;

  world->fx = (double)(world->pwidth-1)/(nx2-nx1);
  world->fy = (double)(world->pheight-1)/(ny2-ny1);
}

/*****************************************************************************/

void InitButtons(Window win, const char* buttonstring, 
		 int width)
{
  struct blist { char type; char text[20]; char key; } *list; 

  XSetWindowAttributes b_attributes;
  const char *ptr;
  char  *ptr2;
  int i, j, count = 1,bcount = 0, x, height, gx, gy;
  unsigned int gwidth, gheight, gb, gd;
  Window tmp;

  ptr = buttonstring;
  while(*ptr) if(*ptr++ == ',') (count)++;
  count /= 3;

  /* parse buttonstring */

  list = (struct blist *) calloc(count,sizeof(struct blist));

  ptr = buttonstring; i=0;
  while(*ptr && i<count) {
    list[i].type = *ptr++;
    while ( (*ptr++ != ',') && *ptr); 
    ptr2 = list[i].text;
    for(j=0; (*ptr!=',') && (*ptr) && j<30 ; *ptr2++ = *ptr++,j++ );
    if(*ptr++ !=',') { printf("Fehler 2 ! %d \n",i); exit(0); };
    if (list[i].type == 'b' ) list[i].key = *ptr++; else list[i].key = ' ';
    while (*ptr++ !=',' && i<count-1);   
    i++;
  }

  /* count buttons */
  for(i=0,bcount=0;i<count;++i) if (list[i].type == 'b') ++bcount;

  /* calculate geometry */
  height = (count + 1) * BUTTONHEIGHT;
  XGetGeometry(meindisplay, win, &tmp, &gx, &gy, &gwidth, &gheight, &gb, &gd );
  x = gwidth - width;

  /* remove existing buttons */
  if ( buttonlist.buttons ) {
    free( buttonlist.buttons );
    ClearWorld( buttonlist.world );
    DestroyWorld( buttonlist.world );
  }

  /* create button-world */
  buttonlist.buttons = (ButtonType *) calloc(bcount,sizeof(ButtonType));
  buttonlist.world = CreateWorld(win,x,0,width,height,0,0,
				 width-1,height-1,0,NorthEastGravity);
  buttonlist.NofButtons = bcount;

  b_attributes.win_gravity = NorthEastGravity;

  /* create buttons */
  for(i=0,j=0;i<count;++i) {
    if ( list[i].type == 'b' ) {
/*
      WFillRectangle(buttonlist.world,5,i*BUTTONHEIGHT+2,
		     width-10,(i+1)*BUTTONHEIGHT-4,0);
*/
      WDrawRectangle(buttonlist.world,5,i*BUTTONHEIGHT+2,
		     width-10,(i+1)*BUTTONHEIGHT-4,1);
      WDrawString(buttonlist.world,10,(i+1)*BUTTONHEIGHT-13,list[i].text,1);

      buttonlist.buttons[j].win = 
	XCreateWindow(meindisplay,win,x+5,i*BUTTONHEIGHT+2,
		      width-12,BUTTONHEIGHT-4,0,CopyFromParent,
		      InputOnly,CopyFromParent,
		      CWWinGravity,&b_attributes);

      XSelectInput(meindisplay,buttonlist.buttons[j].win,ButtonPressMask);
      ShowWindow(buttonlist.buttons[j].win);

      buttonlist.buttons[j].keycode = XKeysymToKeycode(meindisplay,list[i].key);

      /* workaround from 
       http://stackoverflow.com/questions/9838385/replace-of-xkeycodetokeysym
      */
      int keysyms_per_keycode_return ;
      KeySym *keysym = XGetKeyboardMapping(
                                           meindisplay,
                                           buttonlist.buttons[j].keycode,
                                           1,
                                           &keysyms_per_keycode_return) ; 
      /* casting to signed int H. Todt 21.04.2016 */
      if ((int)keysym[0] == list[i].key)
         buttonlist.buttons[j++].state = 0;
      else
       buttonlist.buttons[j++].state = 1;
      XFree(keysym) ;


    } else {

      WDrawString(buttonlist.world,5,(i+1)*BUTTONHEIGHT-13,list[i].text,1);
    }
  }
  buttonflag = 1;
  free(list);
}

/*****************************************************************************/

int GetEvent(XEvent* event, int wait_flag)
{
  int i, ret;
  int newwidth, newheight;
  struct win_node   *winptr;
  struct world_node *worldptr;
  static int configure_flag=0;
  char buffer[2];

  if(wait_flag) 
  {
    /* wait for next event */
    XNextEvent(meindisplay,event);
    ret = 1;
  }
  else
  {
    /* check whether an event is queued */
    if(XEventsQueued(meindisplay,QueuedAfterFlush)) 
    {
      /* read event */
      XNextEvent(meindisplay,event);
      ret = 1;
    }
    else
    {
      /* if no event queued, return 0 */
      event->type = 0;
      ret = 0;
    }
  };
  
  /* serve standard-events */
  if(ret)
    {
      switch(event->type) {
	
      case EnterNotify:
	/* mouse entered window */
/*	XSetInputFocus(meindisplay,event->xcrossing.window,
		       RevertToParent,CurrentTime);
*/
	break;
	
      case MappingNotify:
	/* someone changed keyboard-layout */
	XRefreshKeyboardMapping(&(event->xmapping));
	break;
	
      case Expose:
	/* window gets visible again */
	if(configure_flag) {
	  XClearWindow(meindisplay,event->xexpose.window);
	  
	  winptr = find_win_node(event->xexpose.window);
	  worldptr = winptr->nextworld;
	  
	  while(worldptr) {
	    ExposeWorld(worldptr->world);
	    worldptr = worldptr->nextworld;
	  }
	} else {
	  event->type = 0;
	  ret = 0;	
	}
	configure_flag = 0;
	break;
	
      case ConfigureNotify:
	/* window geometry changed */
	newwidth  = event->xconfigure.width;
	newheight = event->xconfigure.height;
	
	winptr = find_win_node(event->xconfigure.window);
	worldptr = winptr->nextworld;
	
	while(worldptr) {
	  
	  ResizeWorld(worldptr->world,newwidth,newheight);
	  worldptr = worldptr->nextworld;
	}
	configure_flag = 1;
	break;
	
      case ButtonPress:
	/* someone pressed a mouse button */
	if (buttonflag) {
	  /* check whether it was in a 'button' and return key-event */
	  for(i=0; i<buttonlist.NofButtons; i++) {
	    if (event->xbutton.window == buttonlist.buttons[i].win) {
	      event->type = KeyPress;
	      event->xkey.keycode = buttonlist.buttons[i].keycode;
	      event->xkey.state = buttonlist.buttons[i].state;
	      
	    }
	  }
	}
	break;
	
      case KeyPress:
	/* someone pressed a key */
	if (XLookupString(&(event->xkey),buffer,2,0,0) != 1) {
	  event->type = 0;
	  ret = 0;
	}
	break;
	
      default:
	break;
      }
    };
  return ret;
}

/*****************************************************************************/

char ExtractChar(XEvent event)
{
  char buffer[2];

  if(event.type != KeyPress) return 0;
  if(XLookupString(&event.xkey,buffer,2,0,0)==1) return buffer[0];
  else return 0;
}

/*****************************************************************************/

int WGetMousePos(World world, XEvent event, double *x, double *y)
{
  int ret = 0;

  if(event.type != ButtonPress) return 0;

  /* get coords and convert to world-coords */
  *x = (event.xbutton.x - world->px)/world->fx + world->x1;
  *y = (event.xbutton.y - world->py)/world->fy + world->y1;

  /* in world ? */
  if ( (*x >= world->x1) && (*x <= world->x2) && 
       (*y >= world->y1) && (*y <= world->y2) ) ret = event.xbutton.button;

  return ret;
}
  
/*****************************************************************************/


int GetNumber( Window win, int x, int y, double *value )
{
  char   str[30],  zeichen = ' ';
  int    i=1;
  XEvent meinevent;
  
  str[0] = ' ';str[1] = '\0';
  
  while ( zeichen != '\15' )           /* repeat until RETURN pressed */
    {  
      GetEvent(&meinevent,1);
      
      switch (meinevent.type){
	
      case KeyPress: 
	zeichen = ExtractChar(meinevent);
	switch(zeichen){
	  
          /**********   BACK SPACE  ***************************************/
	  
	case '\10':
	  {     
	    if(i>0)
	      {
		
		DrawString (win, x,y,str,1);
		
		str[i+1] = '\0'; str[i] = ' '; str[--i] = ' '; 
		DrawString (win, x,y,str,1);
		break;
	      }
	    else XBell(meindisplay,0);
	  }
	  
          /**********   RETURN   ******************************************/
	  
	case '\15':
	  {     str[i] = '\0';
		break; }
	  
	  
          /**********   MINUS SIGN  ***************************************/
	  
	case '-'  :
	  {     if (i>0) i--; }

	  
          /**********   NUMBER   ******************************************/
	  
	case '0'  :
	case '1'  :
	case '2'  :
	case '3'  :
	case '4'  :
	case '5'  :
	case '6'  :
	case '7'  :
	case '8'  :
	case '9'  :
	case '.'  :
	  
	  
	  {        str[i++] = zeichen;
		   str[i] = ' ';
		   str[i+1] = ' ';
		   str[i+2] = '\0';
		   DrawString (win, x,y,str,1);
		   break;}
	} /* switch zeichen */
	break;
	
      default: break;
      } /* switch */
    } /* while */
  
  
  /**************   Conversion to double *******************************/
  
  if ( !( str[0] == '\0' || str[1] == '\0') ) {
    *value = atof(str);
    return 1;
  } else return 0;
}



/*****************************************************************************/

int WGetNumber( World world, double x, double y, double *value )
{
  char   str[30],  zeichen = ' ';
  int    i=1;
  XEvent meinevent;
  
  str[0] = ' ';str[1] = '\0';
  
  while ( zeichen != '\15' )           /* repeat until RETURN pressed */
    {  
      GetEvent(&meinevent,1);
      
      switch (meinevent.type){
	
      case KeyPress: 
	zeichen = ExtractChar(meinevent);
	switch(zeichen){
	  
          /**********   BACK SPACE  ***************************************/
	  
	case '\10':
	  {     if(i>0)
		  {
		    
		    WDrawString (world, x,y,str,1);
		    
		    str[i+1] = '\0'; str[i] = ' '; str[--i] = ' '; 
		    WDrawString (world, x,y,str,1);
		    break;
		  }
	  else XBell(meindisplay,0);
	      }
	  
          /**********   RETURN   ******************************************/
	  
	case '\15':
	  {     str[i] = '\0';
		break; }
	  
	  
          /**********   MINUS SIGN  ***************************************/
	  
	case '-'  :
	  {     if (i>0) i--; }
	  
	  
          /**********   NUMBER   ******************************************/
	  
	case '0'  :
	case '1'  :
	case '2'  :
	case '3'  :
	case '4'  :
	case '5'  :
	case '6'  :
	case '7'  :
	case '8'  :
	case '9'  :
	case '.'  :
	  
	  
	  {        str[i++] = zeichen;
		   str[i] = ' ';
		   str[i+1] = ' ';
		   str[i+2] = '\0';
		   WDrawString (world, x,y,str,1);
		   break;}
	} /* switch zeichen */
	break;
	
      default: break;
      } /* switch */
    } /* while */
  
  
  /**************   Conversion to double *******************************/
  
  if ( !( str[0] == '\0' || str[1] == '\0') ) {
    *value = atof(str);
    return 1;
  }
  else return 0;
}

/*****************************************************************************/

int GetString( Window win, int x, int y, int length, char *str )
{
  char   zeichen = ' ';
  int    i=0;
  XEvent meinevent;
  
  str[0] = ' ';str[1] = '\0';
  
  while ( zeichen != '\15' )           /* repeat until RETURN pressed */
    {  
      GetEvent(&meinevent,1);
      
      switch (meinevent.type){
	
      case KeyPress: 
	zeichen = ExtractChar(meinevent);
	switch(zeichen){
	  
          /**********   BACK SPACE  ***************************************/
	  
	case '\10':
	  {     
	    if(i>0)
	      {
		
		DrawString (win, x,y,str,1);
		
		XBell(meindisplay,0);

		str[i+1] = '\0'; str[i] = ' '; str[--i] = ' '; 
		DrawString (win, x,y,str,1);
		break;
	      }
	    else XBell(meindisplay,0);
	  }
	  
          /**********   RETURN   ******************************************/
	  
	case '\15':
	  {     str[i] = '\0';
		break; }
	  
	  
          /**********  CHARACTER   ****************************************/
	  
	default  :
	  
	  
	  {        str[i++] = zeichen;
		   str[i] = ' ';
		   str[i+1] = ' ';
		   str[i+2] = '\0';
		   DrawString (win, x,y,str,1);
		   break;}
	} /* switch zeichen */
	break;
	
      } /* switch */
    } /* while */
  
  
  /******************************************************************/
  
  if ( !( str[0] == '\0' || str[1] == '\0') ) {
    str[i] = '\0';
    return 1;
  } else return 0;
}



/*****************************************************************************/

int WGetString( World world, double x, double y, int length, char *string )
{
  char   str[30],  zeichen = ' ';
  int    i=0;
  XEvent meinevent;
  
  str[0] = ' ';str[1] = '\0';
  
  while ( zeichen != '\15' )           /* repeat until RETURN pressed */
    {  
      GetEvent(&meinevent,1);
      
      switch (meinevent.type){
	
      case KeyPress: 
	zeichen = ExtractChar(meinevent);
	switch(zeichen){
	  
          /**********   BACK SPACE  ***************************************/
	  
	case '\10':
	  {     if(i>0)
		  {
		    
		    WDrawString (world, x,y,str,1);
		    
		    str[i+1] = '\0'; str[i] = ' '; str[--i] = ' '; 
		    WDrawString (world, x,y,str,1);
		    break;
		  }
	  else XBell(meindisplay,0);
	      }
	  
          /**********   RETURN   ******************************************/
	  
	case '\15':
	  {     str[i] = '\0';
		break; }
	  
	  
          /**********   CHARACTER   ***************************************/
	  
	default  :
	  
	  
	  {        str[i++] = zeichen;
		   str[i] = ' ';
		   str[i+1] = ' ';
		   str[i+2] = '\0';
		   WDrawString (world, x,y,str,1);
		   break;}
	} /* switch zeichen */
	break;
	
      } /* switch */
    } /* while */
  
  
  /***************************************************************/
  
  if ( !( str[0] == '\0' || str[1] == '\0') ) {
    str[i] = '\0';
    strcpy(string,str);
    return 1;
  }
  else return 0;
}



/*****************************************************************************/

void WSetColor(World world, unsigned long color_func)
{
  unsigned long color;
  unsigned function;

  /* extract color and drawing-function */
  
  function  = (color_func&4096)?(color_func/752)%16:3;
  color     = (function==GXxor)?                  /* colors should appear */
    meincolors[(color_func%752)%NofColors]^white:   /* normal on white      */ 
      meincolors[(color_func%752)%NofColors];       /* background           */
  
  if(color != world->color) {
    XSetForeground(meindisplay,world->gcw,color);
    if(world->pixmap) XSetForeground(meindisplay,world->gcp,color);
    world->color = color;
  }

  /* casting to signed int H. Todt 21.04.2015 */
  if((int)function != world->function) {
    XSetFunction(meindisplay,world->gcw,function);
    if(world->pixmap) XSetFunction(meindisplay,world->gcp,function);
    world->function = function;
  }
}  


void SetColor(unsigned long color_func)
{
  unsigned long color;
  unsigned function;

  function  = (color_func&4096)?(color_func/752)%16:3;
  color     = (function==GXxor)?
    meincolors[(color_func%752)%NofColors]^white:
      meincolors[(color_func%752)%NofColors];
  
  if(color != global_color) {
    XSetForeground(meindisplay,meingc,color);
    global_color = color;
  }

  /* casting to signed int H. Todt 21.04.2015 */
  if((int)function != global_function) {
    XSetFunction(meindisplay,meingc,function);
    global_function = function;
  }
  
}  


/*****************************************************************************/

void ClearArea(Window win, int x, int y, int width, int height)
{
  XClearArea(meindisplay,win,x,y,width,height,False);
}

/*****************************************************************************/

void DrawPoint(Window win, int x, int y, int c)
{
  SetColor(c);

  XDrawPoint(meindisplay,win,meingc,x,y);
}

/*****************************************************************************/

void DrawPoints(Window win, XPoint *points, int NofPoints, int c)
{
  SetColor(c);

  XDrawPoints(meindisplay, win, meingc, points, NofPoints, CoordModeOrigin);
}

/*****************************************************************************/

void DrawLine(Window win, int x1,int y1, int x2, int y2, int c)
{
  SetColor(c);

  XDrawLine(meindisplay,win,meingc,x1,y1,x2,y2);
}

/*****************************************************************************/

void DrawLines(Window win, XPoint *points, int NofPoints, int c)
{
  SetColor(c);

  XDrawLines(meindisplay, win, meingc, points, NofPoints, CoordModeOrigin);
}


/*****************************************************************************/

void DrawCircle(Window win, int x, int y, int r, int c)
{
  int rr;
  
  rr = abs(r);
  SetColor(c);

  XDrawArc(meindisplay,win,meingc,x-rr,y-rr,2*rr,2*rr,0,23040);
}

void FillCircle(Window win, int x, int y, int r, int c)
{
  int rr;
  
  rr = abs(r);
  SetColor(c);

  XFillArc(meindisplay,win,meingc,x-rr,y-rr,2*rr,2*rr,0,23040);
}


/*****************************************************************************/

void DrawString(Window win, int x, int y, const char* text, int c)
{
  SetColor(c);

  XDrawImageString(meindisplay,win,meingc,x,y,text,strlen(text));
  XFlush(meindisplay);
}

/*****************************************************************************/

void DrawRectangle(Window win, int x1, int y1, int x2, int y2, int c)
{
  int temp;
  SetColor(c);

  if (x1 > x2) { temp=x1; x1=x2; x2=temp; };
  if (y1 > y2) { temp=y1; y1=y2; y2=temp; };

  XDrawRectangle(meindisplay, win, meingc, x1, y1, x2-x1, y2-y1);
  XFlush(meindisplay);
}

void FillRectangle(Window win, int x1, int y1, int x2, int y2, int c)
{
  int temp;
  SetColor(c);

  if (x1 > x2) { temp=x1; x1=x2; x2=temp; };
  if (y1 > y2) { temp=y1; y1=y2; y2=temp; };

  XFillRectangle(meindisplay, win, meingc, x1, y1, x2-x1, y2-y1);
  XFlush(meindisplay);
}

/*****************************************************************************/

void DrawPoly(Window win, XPoint *points, int NofPoints, int c)
{
  int i;
  XPoint *xpoints;

  if( !(xpoints = (XPoint*) calloc(NofPoints+1,sizeof(XPoint)) ) ) {
    fprintf(stderr,"Calloc error XLines !!!\n");
    exit(-1);
  }


  for(i=0; i<NofPoints; ++i) {
    xpoints[i].x = points[i].x;
    xpoints[i].y = points[i].y;
  }

  if ((xpoints[0].x != xpoints[NofPoints-1].x)
    ||(xpoints[0].y != xpoints[NofPoints-1].y)) {
      xpoints[NofPoints].x = xpoints[0].x;
      xpoints[NofPoints].y = xpoints[0].y;
      NofPoints ++; 
    }
  

  SetColor(c);

  XDrawLines(meindisplay,win,meingc,
	      xpoints,NofPoints,CoordModeOrigin);

  free(xpoints);

  XFlush(meindisplay);
}

/*****************************************************************************/

void FillPoly(Window win, XPoint *points, int NofPoints, int c, int cfill)
{
  int i;
  XPoint *xpoints;

  if( !(xpoints = (XPoint*) calloc(NofPoints+1,sizeof(XPoint)) ) ) {
    fprintf(stderr,"Calloc error XLines !!!\n");
    exit(-1);
  }


  for(i=0; i<NofPoints; ++i) {
    xpoints[i].x = points[i].x;
    xpoints[i].y = points[i].y;
  }

  if ((xpoints[0].x != xpoints[NofPoints-1].x)
    ||(xpoints[0].y != xpoints[NofPoints-1].y)) {
      xpoints[NofPoints].x = xpoints[0].x;
      xpoints[NofPoints].y = xpoints[0].y;
      NofPoints ++; 
    }
  
  SetColor(cfill);

  XFillPolygon(meindisplay, win, meingc, points, NofPoints, Complex,
	       CoordModeOrigin);


  SetColor(c);

  XDrawLines(meindisplay,win,meingc,
	      xpoints,NofPoints,CoordModeOrigin);

  free(xpoints);

  XFlush(meindisplay);
}

/*****************************************************************************/


void WDrawPoint(World world, double x, double y, int c)
{
  int px, py;

  px = (x-world->x1)*world->fx;
  py = (y-world->y1)*world->fy;

  WSetColor(world,c);

  XDrawPoint(meindisplay,world->win,world->gcw,world->px+px,world->py+py);
  if(world->pixmap) XDrawPoint(meindisplay,world->pixmap,world->gcp,px,py);
  XFlush(meindisplay);
}

/*****************************************************************************/

void WDrawPoints(World world, WPoint *points, int NofPoints, int c)
{
  int i;
  XPoint *xpoints;

  if( !(xpoints = (XPoint*) calloc(NofPoints,sizeof(XPoint)) ) ) {
    fprintf(stderr,"Calloc error XPoints !!!\n");
    exit(-1);
  }


  for(i=0; i<NofPoints; ++i) {
    xpoints[i].x = world->px + (points[i].x-world->x1)*world->fx;
    xpoints[i].y = world->py + (points[i].y-world->y1)*world->fy;
  }

  WSetColor(world,c);

  XDrawPoints(meindisplay,world->win,world->gcw,
	      xpoints,NofPoints,CoordModeOrigin);

  if(world->pixmap){
    for(i=0; i<NofPoints; ++i) {
      xpoints[i].x -= world->px;
      xpoints[i].y -= world->py;
    }

    XDrawPoints(meindisplay,world->pixmap,world->gcp,
		xpoints,NofPoints,CoordModeOrigin);
  }
  free(xpoints);
}

/*****************************************************************************/

void WDrawLine(World world, double x1, double y1, double x2, double y2, int c)
{
  int px1, px2, py1, py2;

  px1 = (x1-world->x1)*world->fx;
  py1 = (y1-world->y1)*world->fy;
  px2 = (x2-world->x1)*world->fx;
  py2 = (y2-world->y1)*world->fy;

  WSetColor(world,c);

  XDrawLine(meindisplay,world->win,world->gcw,
	    world->px+px1,world->py+py1,world->px+px2,world->py+py2);
  
  if(world->pixmap) XDrawLine(meindisplay,world->pixmap,world->gcp,
			      px1,py1,px2,py2);
  
  XFlush(meindisplay);
}

/*****************************************************************************/

void WDrawLines(World world, WPoint *points, int NofPoints, int c)
{
  int i;
  XPoint *xpoints;

  if( !(xpoints = (XPoint*) calloc(NofPoints,sizeof(XPoint)) ) ) {
    fprintf(stderr,"Calloc error XLines !!!\n");
    exit(-1);
  }


  for(i=0; i<NofPoints; ++i) {
    xpoints[i].x = world->px + (points[i].x-world->x1)*world->fx;
    xpoints[i].y = world->py + (points[i].y-world->y1)*world->fy;
  }

  WSetColor(world,c);

  XDrawLines(meindisplay,world->win,world->gcw,
	      xpoints,NofPoints,CoordModeOrigin);

  if(world->pixmap){
    for(i=0; i<NofPoints; ++i) {
      xpoints[i].x -= world->px;
      xpoints[i].y -= world->py;
    }

    XDrawLines(meindisplay,world->pixmap,world->gcp,
		xpoints,NofPoints,CoordModeOrigin);
  }
  free(xpoints);

  XFlush(meindisplay);
}

/*****************************************************************************/

void WDrawCircle(World world, double x, double y, double r, int c)
{
  int px, py, prx, pry;

  px = (x-world->x1)*world->fx;
  py = (y-world->y1)*world->fy;
  prx = abs((int) (r*world->fx));
  pry = abs((int) (r*world->fy));

  if(prx==0) prx=1;
  if(pry==0) pry=1;

  WSetColor(world,c);

  XDrawArc(meindisplay,world->win,world->gcw,world->px+px-prx,
	   world->py+py-pry,2*prx,2*pry,0,23040);

  if(world->pixmap) XDrawArc(meindisplay,world->pixmap,world->gcp,px-prx,
			    py-pry,2*prx,2*pry,0,23040);
}

void WFillCircle(World world, double x, double y, double r, int c)
{
  int px, py, prx, pry;

  px = (x-world->x1)*world->fx;
  py = (y-world->y1)*world->fy;
  prx = abs((int) (r*world->fx));
  pry = abs((int) (r*world->fy));

  if(prx==0) prx=1;
  if(pry==0) pry=1;

  WSetColor(world,c);

  XFillArc(meindisplay,world->win,world->gcw,world->px+px-prx,
	   world->py+py-pry,2*prx,2*pry,0,23040);

  if(world->pixmap) XFillArc(meindisplay,world->pixmap,world->gcp,px-prx,
			    py-pry,2*prx,2*pry,0,23040);
}


/*****************************************************************************/

void WDrawString(World world, double x, double y, const char* text, int c)
{
  int px,py;

  px = (x-world->x1)*world->fx;
  py = (y-world->y1)*world->fy;
  
  WSetColor(world,c);

  XDrawImageString(meindisplay,world->win,world->gcw,
		   world->px+px,world->py+py,text,strlen(text));

  if(world->pixmap)   XDrawImageString(meindisplay,world->pixmap,world->gcp,
				      px,py,text,strlen(text));
  XFlush(meindisplay);
}

/*****************************************************************************/

void WDrawRectangle(World world, double x1, double y1, double x2, double y2, int c)
{
  int px1,px2,py1,py2, temp;

  px1 = (x1-world->x1)*world->fx;
  py1 = (y1-world->y1)*world->fy;
  px2 = (x2-world->x1)*world->fx;
  py2 = (y2-world->y1)*world->fy;

  if (px1>px2) { temp=px1; px1=px2; px2=temp; };
  if (py1>py2) { temp=py1; py1=py2; py2=temp; };

  WSetColor(world,c);

  XDrawRectangle(meindisplay, world->win, world->gcw, 
		 world->px+px1, world->py+py1, px2-px1, py2-py1);
  if(world->pixmap) XDrawRectangle(meindisplay, world->pixmap, world->gcp, 
				  px1, py1, px2-px1, py2-py1);
  XFlush(meindisplay);
}


void WFillRectangle(World world, double x1, double y1, double x2, double y2, int c)
{
  int px1,px2,py1,py2, temp;

  px1 = (x1-world->x1)*world->fx;
  py1 = (y1-world->y1)*world->fy;
  px2 = (x2-world->x1)*world->fx;
  py2 = (y2-world->y1)*world->fy;

  if (px1>px2) { temp=px1; px1=px2; px2=temp; };
  if (py1>py2) { temp=py1; py1=py2; py2=temp; };

  WSetColor(world,c);

  XFillRectangle(meindisplay, world->win, world->gcw, 
		 world->px+px1, world->py+py1, px2-px1, py2-py1);
  if(world->pixmap) XFillRectangle(meindisplay, world->pixmap, world->gcp, 
				  px1, py1, px2-px1, py2-py1);
  XFlush(meindisplay);
}

/*****************************************************************************/

void WDrawPoly(World world, WPoint *points, int NofPoints, int c)
{
  int i;
  XPoint *xpoints;

  if( !(xpoints = (XPoint*) calloc(NofPoints+1,sizeof(XPoint)) ) ) {
    fprintf(stderr,"Calloc error XLines !!!\n");
    exit(-1);
  }


  for(i=0; i<NofPoints; ++i) {
    xpoints[i].x = world->px + (points[i].x-world->x1)*world->fx;
    xpoints[i].y = world->py + (points[i].y-world->y1)*world->fy;
  }

  if ((xpoints[0].x != xpoints[NofPoints-1].x)
    ||(xpoints[0].y != xpoints[NofPoints-1].y)) {
      xpoints[NofPoints].x = xpoints[0].x;
      xpoints[NofPoints].y = xpoints[0].y;
      NofPoints ++; 
    }
  

  WSetColor(world,c);

  XDrawLines(meindisplay,world->win,world->gcw,
	      xpoints,NofPoints,CoordModeOrigin);

  if(world->pixmap){
    for(i=0; i<NofPoints; ++i) {
      xpoints[i].x -= world->px;
      xpoints[i].y -= world->py;
    }

    XDrawLines(meindisplay,world->pixmap,world->gcp,
		xpoints,NofPoints,CoordModeOrigin);
  }
  free(xpoints);

  XFlush(meindisplay);
}

/*****************************************************************************/

void WFillPoly(World world, WPoint *points, int NofPoints, int c, int cfill)
{
  int i;
  XPoint *xpoints;

  if( !(xpoints = (XPoint*) calloc(NofPoints+1,sizeof(XPoint)) ) ) {
    fprintf(stderr,"Calloc error XLines !!!\n");
    exit(-1);
  }


  for(i=0; i<NofPoints; ++i) {
    xpoints[i].x = world->px + (points[i].x-world->x1)*world->fx;
    xpoints[i].y = world->py + (points[i].y-world->y1)*world->fy;
  }

  WSetColor(world,cfill);

  XFillPolygon(meindisplay, world->win, world->gcw, xpoints, NofPoints,
	       Complex, CoordModeOrigin);

  if ((xpoints[0].x != xpoints[NofPoints-1].x)
    ||(xpoints[0].y != xpoints[NofPoints-1].y)) {
      xpoints[NofPoints].x = xpoints[0].x;
      xpoints[NofPoints].y = xpoints[0].y;
      NofPoints ++; 
    }
  

  WSetColor(world,c);

  XDrawLines(meindisplay,world->win,world->gcw,
	      xpoints,NofPoints,CoordModeOrigin);

  if(world->pixmap){
    for(i=0; i<NofPoints; ++i) {
      xpoints[i].x -= world->px;
      xpoints[i].y -= world->py;
    }
    
    WSetColor(world,cfill);

    XFillPolygon(meindisplay, world->pixmap, world->gcp, xpoints, NofPoints,
		 Complex, CoordModeOrigin);

    WSetColor(world,c);

    XDrawLines(meindisplay,world->pixmap,world->gcp,
		xpoints,NofPoints,CoordModeOrigin);
  }
  free(xpoints);

  XFlush(meindisplay);
}

/*****************************************************************************/

  





