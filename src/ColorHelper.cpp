//----------------------------------------------------------------------------//
//               █      █                                                     //
//               ████████                                                     //
//             ██        ██                                                   //
//            ███  █  █  ███        Color.cpp                                 //
//            █ █        █ █        ColorHelper_cpp                           //
//             ████████████                                                   //
//           █              █       Copyright (c) 2015, 2016                  //
//          █     █    █     █      AmazingCow - www.AmazingCow.com           //
//          █     █    █     █                                                //
//           █              █       N2OMatt - n2omatt@amazingcow.com          //
//             ████████████         www.amazingcow.com/n2omatt                //
//                                                                            //
//                  This software is licensed as GPLv3                        //
//                 CHECK THE COPYING FILE TO MORE DETAILS                     //
//                                                                            //
//    Permission is granted to anyone to use this software for any purpose,   //
//   including commercial applications, and to alter it and redistribute it   //
//               freely, subject to the following restrictions:               //
//                                                                            //
//     0. You **CANNOT** change the type of the license.                      //
//     1. The origin of this software must not be misrepresented;             //
//        you must not claim that you wrote the original software.            //
//     2. If you use this software in a product, an acknowledgment in the     //
//        product IS HIGHLY APPRECIATED, both in source and binary forms.     //
//        (See opensource.AmazingCow.com/acknowledgment.html for details).    //
//        If you will not acknowledge, just send us a email. We'll be         //
//        *VERY* happy to see our work being used by other people. :)         //
//        The email is: acknowledgment_opensource@AmazingCow.com              //
//     3. Altered source versions must be plainly marked as such,             //
//        and must not be misrepresented as being the original software.      //
//     4. This notice may not be removed or altered from any source           //
//        distribution.                                                       //
//     5. Most important, you must have fun. ;)                               //
//                                                                            //
//      Visit opensource.amazingcow.com for more open-source projects.        //
//                                                                            //
//                                  Enjoy :)                                  //
//----------------------------------------------------------------------------//

//Header
#include "../include/ColorHelper.h"
//std
#include <cmath>
#include <cstring>
#include <algorithm>
#include <iomanip>
#include <sstream>
#include <iostream>

//Usings
using namespace ColorHelper;


////////////////////////////////////////////////////////////////////////////////
// Macros                                                                     //
////////////////////////////////////////////////////////////////////////////////
#define _CH_MAX(_a_, _b_, _c_)  std::max({(_a_), (_b_), (_c_)})
#define _CH_MIN(_a_, _b_, _c_)  std::min({(_a_), (_b_), (_c_)})


#define _CH_NORM_RANGE_RGB(_v_) (_v_) / 255.0f
#define _CH_FULL_RANGE_RGB(_v_) static_cast<int>(ceil((_v_)) * 255.0f)


#define _CH_CALC_HSX_DELTA(_nr_) \
    (((max_value - (_nr_)) / 6.0f) + (delta_value / 2.0f)) / delta_value;


#define _ANGLE_TO_HUE(_angle_) \
    static_cast<float>(fabs(fmodf(_angle_, 360.0f) / 360.0f))

#define _HSL_PLUS_ANGLE(_hsl_, _angle_)     \
    HSL { _hsl_.h + _ANGLE_TO_HUE(_angle_), \
          _hsl_.s,                          \
          _hsl_.l }

#define _HSV_PLUS_ANGLE(_hsv_, _angle_)           \
          HSV { _hsv_.h + _ANGLE_TO_HUE(_angle_), \
                _hsv_.s,                          \
                _hsv_.v }



////////////////////////////////////////////////////////////////////////////////
// Constants                                                                  //
////////////////////////////////////////////////////////////////////////////////
constexpr float kOneThird = 1.0f / 3.0f;
constexpr float kTwoThird = 2.0f / 3.0f;


/* TAKEN DIRECTLY FROM ALLEGRO 5 SOURCE */

typedef struct {
   char const *name;
   int r, g, b;
} ColorName;

/* Taken from http://www.w3.org/TR/2010/PR-css3-color-20101028/#svg-color
 * This must be sorted correctly for binary search.
 */
static ColorName _al_color_names[] = {
   { "aliceblue"            , 0xf0, 0xf8, 0xff },
   { "antiquewhite"         , 0xfa, 0xeb, 0xd7 },
   { "aqua"                 , 0x00, 0xff, 0xff },
   { "aquamarine"           , 0x7f, 0xff, 0xd4 },
   { "azure"                , 0xf0, 0xff, 0xff },
   { "beige"                , 0xf5, 0xf5, 0xdc },
   { "bisque"               , 0xff, 0xe4, 0xc4 },
   { "black"                , 0x00, 0x00, 0x00 },
   { "blanchedalmond"       , 0xff, 0xeb, 0xcd },
   { "blue"                 , 0x00, 0x00, 0xff },
   { "blueviolet"           , 0x8a, 0x2b, 0xe2 },
   { "brown"                , 0xa5, 0x2a, 0x2a },
   { "burlywood"            , 0xde, 0xb8, 0x87 },
   { "cadetblue"            , 0x5f, 0x9e, 0xa0 },
   { "chartreuse"           , 0x7f, 0xff, 0x00 },
   { "chocolate"            , 0xd2, 0x69, 0x1e },
   { "coral"                , 0xff, 0x7f, 0x50 },
   { "cornflowerblue"       , 0x64, 0x95, 0xed },
   { "cornsilk"             , 0xff, 0xf8, 0xdc },
   { "crimson"              , 0xdc, 0x14, 0x3c },
   { "cyan"                 , 0x00, 0xff, 0xff },
   { "darkblue"             , 0x00, 0x00, 0x8b },
   { "darkcyan"             , 0x00, 0x8b, 0x8b },
   { "darkgoldenrod"        , 0xb8, 0x86, 0x0b },
   { "darkgray"             , 0xa9, 0xa9, 0xa9 },
   { "darkgreen"            , 0x00, 0x64, 0x00 },
   { "darkgrey"             , 0xa9, 0xa9, 0xa9 },
   { "darkkhaki"            , 0xbd, 0xb7, 0x6b },
   { "darkmagenta"          , 0x8b, 0x00, 0x8b },
   { "darkolivegreen"       , 0x55, 0x6b, 0x2f },
   { "darkorange"           , 0xff, 0x8c, 0x00 },
   { "darkorchid"           , 0x99, 0x32, 0xcc },
   { "darkred"              , 0x8b, 0x00, 0x00 },
   { "darksalmon"           , 0xe9, 0x96, 0x7a },
   { "darkseagreen"         , 0x8f, 0xbc, 0x8f },
   { "darkslateblue"        , 0x48, 0x3d, 0x8b },
   { "darkslategray"        , 0x2f, 0x4f, 0x4f },
   { "darkslategrey"        , 0x2f, 0x4f, 0x4f },
   { "darkturquoise"        , 0x00, 0xce, 0xd1 },
   { "darkviolet"           , 0x94, 0x00, 0xd3 },
   { "deeppink"             , 0xff, 0x14, 0x93 },
   { "deepskyblue"          , 0x00, 0xbf, 0xff },
   { "dimgray"              , 0x69, 0x69, 0x69 },
   { "dimgrey"              , 0x69, 0x69, 0x69 },
   { "dodgerblue"           , 0x1e, 0x90, 0xff },
   { "firebrick"            , 0xb2, 0x22, 0x22 },
   { "floralwhite"          , 0xff, 0xfa, 0xf0 },
   { "forestgreen"          , 0x22, 0x8b, 0x22 },
   { "fuchsia"              , 0xff, 0x00, 0xff },
   { "gainsboro"            , 0xdc, 0xdc, 0xdc },
   { "ghostwhite"           , 0xf8, 0xf8, 0xff },
   { "gold"                 , 0xff, 0xd7, 0x00 },
   { "goldenrod"            , 0xda, 0xa5, 0x20 },
   { "gray"                 , 0x80, 0x80, 0x80 },
   { "green"                , 0x00, 0x80, 0x00 },
   { "greenyellow"          , 0xad, 0xff, 0x2f },
   { "grey"                 , 0x80, 0x80, 0x80 },
   { "honeydew"             , 0xf0, 0xff, 0xf0 },
   { "hotpink"              , 0xff, 0x69, 0xb4 },
   { "indianred"            , 0xcd, 0x5c, 0x5c },
   { "indigo"               , 0x4b, 0x00, 0x82 },
   { "ivory"                , 0xff, 0xff, 0xf0 },
   { "khaki"                , 0xf0, 0xe6, 0x8c },
   { "lavender"             , 0xe6, 0xe6, 0xfa },
   { "lavenderblush"        , 0xff, 0xf0, 0xf5 },
   { "lawngreen"            , 0x7c, 0xfc, 0x00 },
   { "lemonchiffon"         , 0xff, 0xfa, 0xcd },
   { "lightblue"            , 0xad, 0xd8, 0xe6 },
   { "lightcoral"           , 0xf0, 0x80, 0x80 },
   { "lightcyan"            , 0xe0, 0xff, 0xff },
   { "lightgoldenrodyellow" , 0xfa, 0xfa, 0xd2 },
   { "lightgray"            , 0xd3, 0xd3, 0xd3 },
   { "lightgreen"           , 0x90, 0xee, 0x90 },
   { "lightgrey"            , 0xd3, 0xd3, 0xd3 },
   { "lightpink"            , 0xff, 0xb6, 0xc1 },
   { "lightsalmon"          , 0xff, 0xa0, 0x7a },
   { "lightseagreen"        , 0x20, 0xb2, 0xaa },
   { "lightskyblue"         , 0x87, 0xce, 0xfa },
   { "lightslategray"       , 0x77, 0x88, 0x99 },
   { "lightslategrey"       , 0x77, 0x88, 0x99 },
   { "lightsteelblue"       , 0xb0, 0xc4, 0xde },
   { "lightyellow"          , 0xff, 0xff, 0xe0 },
   { "lime"                 , 0x00, 0xff, 0x00 },
   { "limegreen"            , 0x32, 0xcd, 0x32 },
   { "linen"                , 0xfa, 0xf0, 0xe6 },
   { "magenta"              , 0xff, 0x00, 0xff },
   { "maroon"               , 0x80, 0x00, 0x00 },
   { "mediumaquamarine"     , 0x66, 0xcd, 0xaa },
   { "mediumblue"           , 0x00, 0x00, 0xcd },
   { "mediumorchid"         , 0xba, 0x55, 0xd3 },
   { "mediumpurple"         , 0x93, 0x70, 0xdb },
   { "mediumseagreen"       , 0x3c, 0xb3, 0x71 },
   { "mediumslateblue"      , 0x7b, 0x68, 0xee },
   { "mediumspringgreen"    , 0x00, 0xfa, 0x9a },
   { "mediumturquoise"      , 0x48, 0xd1, 0xcc },
   { "mediumvioletred"      , 0xc7, 0x15, 0x85 },
   { "midnightblue"         , 0x19, 0x19, 0x70 },
   { "mintcream"            , 0xf5, 0xff, 0xfa },
   { "mistyrose"            , 0xff, 0xe4, 0xe1 },
   { "moccasin"             , 0xff, 0xe4, 0xb5 },
   { "navajowhite"          , 0xff, 0xde, 0xad },
   { "navy"                 , 0x00, 0x00, 0x80 },
   { "oldlace"              , 0xfd, 0xf5, 0xe6 },
   { "olive"                , 0x80, 0x80, 0x00 },
   { "olivedrab"            , 0x6b, 0x8e, 0x23 },
   { "orange"               , 0xff, 0xa5, 0x00 },
   { "orangered"            , 0xff, 0x45, 0x00 },
   { "orchid"               , 0xda, 0x70, 0xd6 },
   { "palegoldenrod"        , 0xee, 0xe8, 0xaa },
   { "palegreen"            , 0x98, 0xfb, 0x98 },
   { "paleturquoise"        , 0xaf, 0xee, 0xee },
   { "palevioletred"        , 0xdb, 0x70, 0x93 },
   { "papayawhip"           , 0xff, 0xef, 0xd5 },
   { "peachpuff"            , 0xff, 0xda, 0xb9 },
   { "peru"                 , 0xcd, 0x85, 0x3f },
   { "pink"                 , 0xff, 0xc0, 0xcb },
   { "plum"                 , 0xdd, 0xa0, 0xdd },
   { "powderblue"           , 0xb0, 0xe0, 0xe6 },
   { "purple"               , 0x80, 0x00, 0x80 },
   { "purwablue"            , 0x9b, 0xe1, 0xff },
   { "red"                  , 0xff, 0x00, 0x00 },
   { "rosybrown"            , 0xbc, 0x8f, 0x8f },
   { "royalblue"            , 0x41, 0x69, 0xe1 },
   { "saddlebrown"          , 0x8b, 0x45, 0x13 },
   { "salmon"               , 0xfa, 0x80, 0x72 },
   { "sandybrown"           , 0xf4, 0xa4, 0x60 },
   { "seagreen"             , 0x2e, 0x8b, 0x57 },
   { "seashell"             , 0xff, 0xf5, 0xee },
   { "sienna"               , 0xa0, 0x52, 0x2d },
   { "silver"               , 0xc0, 0xc0, 0xc0 },
   { "skyblue"              , 0x87, 0xce, 0xeb },
   { "slateblue"            , 0x6a, 0x5a, 0xcd },
   { "slategray"            , 0x70, 0x80, 0x90 },
   { "slategrey"            , 0x70, 0x80, 0x90 },
   { "snow"                 , 0xff, 0xfa, 0xfa },
   { "springgreen"          , 0x00, 0xff, 0x7f },
   { "steelblue"            , 0x46, 0x82, 0xb4 },
   { "tan"                  , 0xd2, 0xb4, 0x8c },
   { "teal"                 , 0x00, 0x80, 0x80 },
   { "thistle"              , 0xd8, 0xbf, 0xd8 },
   { "tomato"               , 0xff, 0x63, 0x47 },
   { "turquoise"            , 0x40, 0xe0, 0xd0 },
   { "violet"               , 0xee, 0x82, 0xee },
   { "wheat"                , 0xf5, 0xde, 0xb3 },
   { "white"                , 0xff, 0xff, 0xff },
   { "whitesmoke"           , 0xf5, 0xf5, 0xf5 },
   { "yellow"               , 0xff, 0xff, 0x00 },
   { "yellowgreen"          , 0x9a, 0xcd, 0x32 },
};


////////////////////////////////////////////////////////////////////////////////
// Helper Prototypes                                                          //
////////////////////////////////////////////////////////////////////////////////
float HSL_hue_to_RGB_comp(float, float, float);


////////////////////////////////////////////////////////////////////////////////
// Conversions                                                                //
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// RGB - HEX                                                                  //
////////////////////////////////////////////////////////////////////////////////
HEX ColorHelper::RGB_to_HEX(const RGB &rgb)
{
    std::stringstream ss;

    ss << "#"
       << std::hex
       << std::setw(2) << std::setfill('0') << rgb.r
       << std::setw(2) << std::setfill('0') << rgb.g
       << std::setw(2) << std::setfill('0') << rgb.b;

    return ss.str();
}

RGB ColorHelper::HEX_to_RGB(const HEX &hex)
{
    std::stringstream ss(hex);
    RGB rgb { 0, 0, 0 };

    std::string dummy, s1, s2, s3;

    ss >> std::setw(1) >> dummy
       >> std::setw(2) >> s1
       >> std::setw(2) >> s2
       >> std::setw(2) >> s3;

    rgb.r = strtol(s1.c_str(), nullptr, 16);
    rgb.g = strtol(s2.c_str(), nullptr, 16);
    rgb.b = strtol(s3.c_str(), nullptr, 16);

    return rgb;
}


////////////////////////////////////////////////////////////////////////////////
// RGB - HSV                                                                  //
////////////////////////////////////////////////////////////////////////////////
HSV ColorHelper::RGB_to_HSV(const RGB &rgb)
{
    //Formula taken from:
    //http://www.easyrgb.com/index.php?X=MATH&H=20#text20
    HSV hsv {0, 0, 0};

    //Make the values from range of (0,255) to (0,1);
    float normalized_r = _CH_NORM_RANGE_RGB(rgb.r);
    float normalized_g = _CH_NORM_RANGE_RGB(rgb.g);
    float normalized_b = _CH_NORM_RANGE_RGB(rgb.b);

    //Min, Max and Delta from RGB.
    float min_value   = _CH_MIN(normalized_r, normalized_g, normalized_b);
    float max_value   = _CH_MAX(normalized_r, normalized_g, normalized_b);
    float delta_value = max_value - min_value;

    hsv.v = max_value;
    if(delta_value == 0)
        return hsv;

    //Color isn't gray - i.e. it has chroma.
    hsv.s = (delta_value / max_value);

    float delta_r = _CH_CALC_HSX_DELTA(normalized_r);
    float delta_g = _CH_CALC_HSX_DELTA(normalized_g);
    float delta_b = _CH_CALC_HSX_DELTA(normalized_b);

    if(normalized_r == max_value)
        hsv.h = (delta_b - delta_g);
    else if(normalized_g == max_value)
        hsv.h = kOneThird + (delta_r - delta_b);
    else if(normalized_b == max_value)
        hsv.h = kTwoThird + (delta_g - delta_r);

    if(hsv.h < 0) hsv.h += 1;
    if(hsv.h > 1) hsv.h -= 1;

    return hsv;
}

RGB ColorHelper::HSV_to_RGB(const HSV &hsv)
{
    //Formula taken from:
    //http://www.easyrgb.com/index.php?X=MATH&H=21#text21
    RGB rgb;

    if(hsv.s == 0)
    {
        rgb.r = _CH_FULL_RANGE_RGB(hsv.v);
        rgb.g = _CH_FULL_RANGE_RGB(hsv.v);
        rgb.b = _CH_FULL_RANGE_RGB(hsv.v);

        return rgb;
    }

    float value_h = hsv.h * 6.0f;
    if(value_h == 6)
        value_h = 0;

    float value_i = floorf(value_h);
    float value_1 = hsv.v * (1.0f - hsv.s);
    float value_2 = hsv.v * (1.0f - hsv.s * (value_h - value_i));
    float value_3 = hsv.v * (1.0f - hsv.s * (1.0f - (value_h - value_i)));

    float value_r, value_g, value_b;

    #define _ASSIGN(_tr_, _tg_, _tb_) \
        { value_r = (_tr_); value_g = (_tg_); value_b = (_tb_); }

    switch(static_cast<int>(value_i))
    {
        case 0 : _ASSIGN(hsv.v,   value_3, value_1); break;
        case 1 : _ASSIGN(value_2, hsv.v,   value_1); break;
        case 2 : _ASSIGN(value_1, hsv.v,   value_3); break;
        case 3 : _ASSIGN(value_1, value_2, hsv.v  ); break;
        case 4 : _ASSIGN(value_3, value_1, hsv.v  ); break;
        default: _ASSIGN(hsv.v,   value_1, value_2); break;
    }

    #undef _ASSIGN

    rgb.r = _CH_FULL_RANGE_RGB(value_r);
    rgb.g = _CH_FULL_RANGE_RGB(value_g);
    rgb.b = _CH_FULL_RANGE_RGB(value_b);

    return rgb;
}


////////////////////////////////////////////////////////////////////////////////
// RGB - HSL                                                                  //
////////////////////////////////////////////////////////////////////////////////
HSL ColorHelper::RGB_to_HSL(const RGB &rgb)
{
    //Formula taken from:
    //http://www.easyrgb.com/index.php?X=MATH&H=18#text18
    HSL hsl { 0, 0, 0 };

    //Make the values from range of (0,255) to (0,1);
    float normalized_r = _CH_NORM_RANGE_RGB(rgb.r);
    float normalized_g = _CH_NORM_RANGE_RGB(rgb.g);
    float normalized_b = _CH_NORM_RANGE_RGB(rgb.b);

    //Make the values from range of (0,255) to (0,1);
    float min_value   = _CH_MIN(normalized_r, normalized_g, normalized_b);
    float max_value   = _CH_MAX(normalized_r, normalized_g, normalized_b);
    float delta_value = (max_value - min_value);


    hsl.l = (max_value + min_value) / 2.0f;

    if(delta_value == 0)
        return hsl;

    //Color isn't gray - i.e. it has chroma.
    hsl.s = (hsl.l < 0.5f)
            ? (delta_value / (max_value + min_value))
            : (delta_value / (2 - max_value - min_value));

    float delta_r = _CH_CALC_HSX_DELTA(normalized_r);
    float delta_g = _CH_CALC_HSX_DELTA(normalized_g);
    float delta_b = _CH_CALC_HSX_DELTA(normalized_b);

    if(normalized_r == max_value)
        hsl.h = (delta_b - delta_g);
    else if(normalized_g == max_value)
        hsl.h = kOneThird + (delta_r - delta_b);
    else if(normalized_b == max_value)
        hsl.h = kTwoThird + (delta_g - delta_r);

    if(hsl.h < 0) hsl.h += 1;
    if(hsl.h > 1) hsl.h -= 1;

    return hsl;
}

RGB ColorHelper::HSL_to_RGB(const HSL &hsl)
{
    //Formula taken:
    //http://www.easyrgb.com/index.php?X=MATH&H=19#text19
    RGB rgb;

    if(hsl.s == 0)
    {
        rgb.r = _CH_FULL_RANGE_RGB(hsl.l);
        rgb.g = _CH_FULL_RANGE_RGB(hsl.l);
        rgb.b = _CH_FULL_RANGE_RGB(hsl.l);

        return rgb;
    }

    float value_2 = (hsl.l < 0.5 )
                  ? (hsl.l * (1.0f + hsl.s))
                  : (hsl.l + hsl.s) - (hsl.s * hsl.l);

    float value_1 = (2.0f * hsl.l) - value_2;

    float value_r = HSL_hue_to_RGB_comp(value_1, value_2, hsl.h + kOneThird);
    float value_g = HSL_hue_to_RGB_comp(value_1, value_2, hsl.h);
    float value_b = HSL_hue_to_RGB_comp(value_1, value_2, hsl.h - kOneThird);

    rgb.r = _CH_FULL_RANGE_RGB(value_r);
    rgb.g = _CH_FULL_RANGE_RGB(value_g);
    rgb.b = _CH_FULL_RANGE_RGB(value_b);

    return rgb;
}


////////////////////////////////////////////////////////////////////////////////
// RGB - CMY                                                                  //
////////////////////////////////////////////////////////////////////////////////
CMY ColorHelper::RGB_to_CMY(const RGB &rgb)
{
    //Formula taken from:
    //http://www.easyrgb.com/index.php?X=MATH&H=11#text11
    CMY cmy;

    cmy.c = 1.0f - _CH_NORM_RANGE_RGB(rgb.r);
    cmy.m = 1.0f - _CH_NORM_RANGE_RGB(rgb.g);
    cmy.y = 1.0f - _CH_NORM_RANGE_RGB(rgb.b);

    return cmy;
}

RGB ColorHelper::CMY_to_RGB(const CMY &cmy)
{
    //Formula taken from:
    //http://www.easyrgb.com/index.php?X=MATH&H=12#text12
    RGB rgb;

    rgb.r =  _CH_FULL_RANGE_RGB(1.0f - cmy.c);
    rgb.g =  _CH_FULL_RANGE_RGB(1.0f - cmy.m);
    rgb.b =  _CH_FULL_RANGE_RGB(1.0f - cmy.y);

    return rgb;
}


////////////////////////////////////////////////////////////////////////////////
// RGB - CMYK                                                                 //
////////////////////////////////////////////////////////////////////////////////
RGB ColorHelper::CMYK_to_RGB(const CMYK &cmyk)
{

}

CMYK ColorHelper::RGB_to_CMYK(const RGB &rgb)
{

}

////////////////////////////////////////////////////////////////////////////////
// RGB - Name                                                                 //
////////////////////////////////////////////////////////////////////////////////
std::string ColorHelper::RGB_to_Name(const RGB &rgb, bool *found)
{
    //COWTODO: Binary search can be used?
    auto it = std::find_if (
        std::begin(_al_color_names),
        std::end  (_al_color_names),
        [=](const ColorName &c1) {
            return (rgb.r == c1.r &&
                    rgb.g == c1.g &&
                    rgb.b == c1.b);
    });

    std::string name;
    if(it != std::end(_al_color_names))
    {
        if(found) *found = true;
        name = it->name;
    }
    else
    {
        if(found) *found = false;
        name = "";
    }

    return name;
}

RGB ColorHelper::Name_To_RGB(const std::string &name, bool *found)
{
    //COWTODO: Binary search can be used?
    auto it = std::find_if (
        std::begin(_al_color_names),
        std::end  (_al_color_names),
        [=](const ColorName &c1) {
            return name == c1.name;
    });

    RGB rgb { 0, 0, 0 };
    if(it != std::end(_al_color_names))
    {
        if(found) *found = true;

        rgb.r = it->r;
        rgb.g = it->g;
        rgb.b = it->b;
    }
    else
    {
        if(found) *found = false;
    }

    return rgb;
}


////////////////////////////////////////////////////////////////////////////////
// Color Wheel Functions                                                      //
////////////////////////////////////////////////////////////////////////////////

//Complementary
std::vector<HSL> ColorHelper::Complementary(const HSL &hsl)
{
    return std::vector<HSL> {
        hsl,
        _HSL_PLUS_ANGLE(hsl, 180)
    };
}

std::vector<HSV> ColorHelper::Complementary(const HSV &hsv)
{
    return std::vector<HSV> {
        hsv,
        _HSV_PLUS_ANGLE(hsv, 180)
    };
}

//Split Complementary
std::vector<HSL> ColorHelper::SplitComplementary(const HSL &hsl)
{
    return std::vector<HSL> {
        hsl,
        _HSL_PLUS_ANGLE(hsl, +150),
        _HSL_PLUS_ANGLE(hsl, -150)
    };
}
std::vector<HSV> ColorHelper::SplitComplementary(const HSV &hsv)
{
    return std::vector<HSV> {
        hsv,
        _HSV_PLUS_ANGLE(hsv, +150),
        _HSV_PLUS_ANGLE(hsv, -150)
    };
}

//Analogous
std::vector<HSL> ColorHelper::Analogous(const HSL &hsl)
{
    return std::vector<HSL> {
        hsl,
        _HSL_PLUS_ANGLE(hsl, +30),
        _HSL_PLUS_ANGLE(hsl, -30)
    };
}

std::vector<HSV> ColorHelper::Analogous(const HSV &hsv)
{
    return std::vector<HSV> {
        hsv,
        _HSV_PLUS_ANGLE(hsv, +30),
        _HSV_PLUS_ANGLE(hsv, -30)
    };
}


//Triad
std::vector<HSL> Triad(const HSL &hsl, float angleInDegrees /* = 120 */)
{
    return std::vector<HSL> {
        hsl,
        _HSL_PLUS_ANGLE(hsl,     angleInDegrees),
        _HSL_PLUS_ANGLE(hsl, 2 * angleInDegrees)
    };
}

std::vector<HSV> Triad(const HSV &hsv, float angleInDegrees /* = 120 */)
{
    return std::vector<HSV> {
        hsv,
        _HSV_PLUS_ANGLE(hsv,     angleInDegrees),
        _HSV_PLUS_ANGLE(hsv, 2 * angleInDegrees)
    };
}


//Tetrad
std::vector<HSL> Tetrad(const HSL &hsl, float angleInDegrees /* = 90 */)
{
    return std::vector<HSL> {
        hsl,
        _HSL_PLUS_ANGLE(hsl,     angleInDegrees),
        _HSL_PLUS_ANGLE(hsl, 2 * angleInDegrees),
        _HSL_PLUS_ANGLE(hsl, 3 * angleInDegrees)
    };
}

std::vector<HSV> Tetrad(const HSV &hsv, float angleInDegrees /* = 90 */)
{
    return std::vector<HSV> {
        hsv,
        _HSV_PLUS_ANGLE(hsv,     angleInDegrees),
        _HSV_PLUS_ANGLE(hsv, 2 * angleInDegrees),
        _HSV_PLUS_ANGLE(hsv, 3 * angleInDegrees)
    };
}


//Tetrad Square
std::vector<HSL> TetradSquare(const HSL &hsl, float angleInDegrees = 90)
{
    return std::vector<HSL> {
        hsl,
        _HSL_PLUS_ANGLE(hsl,     angleInDegrees),
        _HSL_PLUS_ANGLE(hsl, 2 * angleInDegrees),
        _HSL_PLUS_ANGLE(hsl, 3 * angleInDegrees)
    };
}
std::vector<HSV> TetradSquare(const HSV &hsv, float angleInDegrees = 90)
{
    return std::vector<HSV> {
        hsv,
        _HSV_PLUS_ANGLE(hsv,     angleInDegrees),
        _HSV_PLUS_ANGLE(hsv, 2 * angleInDegrees),
        _HSV_PLUS_ANGLE(hsv, 3 * angleInDegrees)
    };
}


////////////////////////////////////////////////////////////////////////////////
// Stream Operators                                                           //
////////////////////////////////////////////////////////////////////////////////
std::ostream& ColorHelper::operator<<(std::ostream &os, const RGB &rgb)
{
    os << "RGB (" << rgb.r << ", " << rgb.g << ", " << rgb.b << ")";
    return os;
}

std::ostream& ColorHelper::operator<<(std::ostream &os, const HSV &hsl)
{
    os << "HSV (" << hsl.h << ", " << hsl.s << ", " << hsl.v << ")";
    return os;
}

std::ostream& ColorHelper::operator<<(std::ostream &os, const HSL &hsl)
{
    os << "HSL (" << hsl.h << ", " << hsl.s << ", " << hsl.l << ")";
    return os;
}

std::ostream& ColorHelper::operator<<(std::ostream &os, const CMY &cmy)
{
    os << "CMY (" << cmy.c << ", " << cmy.m  << ", " << cmy.y << ")";

    return os;
}


////////////////////////////////////////////////////////////////////////////////
// Private Functions                                                          //
////////////////////////////////////////////////////////////////////////////////
float HSL_hue_to_RGB_comp(float v1, float v2, float vH)
{
    if(vH < 0) vH += 1;
    if(vH > 1) vH -= 1;

    if((6 * vH) < 1)
        return (v1 + (v2 - v1) * 6.0f * vH);

    if((2 * vH) < 1)
        return v2;

    if((3 * vH) < 2)
        return (v1 + (v2 - v1) * (kTwoThird - vH) * 6);

    return v1;
}
