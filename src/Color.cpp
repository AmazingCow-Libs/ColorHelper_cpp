//----------------------------------------------------------------------------//
//               █      █                                                     //
//               ████████                                                     //
//             ██        ██                                                   //
//            ███  █  █  ███        Color.cpp                                 //
//            █ █        █ █        colorhelper_cpp                           //
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
#include "../include/Color.h"
//std
#include <algorithm>
#include <sstream>


////////////////////////////////////////////////////////////////////////////////
// Stream Operators                                                           //
////////////////////////////////////////////////////////////////////////////////
std::ostream& operator<<(std::ostream &os, const Color::RGB &value)
{
    os << "R:" << value.r << " "
       << "G:" << value.g << " "
       << "B:" << value.b;

    return os;
}

std::ostream& operator<<(std::ostream &os, const Color::HSV &value)
{
    os << "H:" << value.h << " "
       << "S:" << value.s << " "
       << "V:" << value.v;

    return os;
}

std::ostream& operator<<(std::ostream &os, const Color::HSL &value)
{
    os << "H:" << value.h << " "
       << "S:" << value.s << " "
       << "L:" << value.l;

    return os;
}

std::ostream& operator<<(std::ostream &os, const Color::CMY &value)
{
    os << "C:" << value.c << " "
       << "M:" << value.m << " "
       << "Y:" << value.y;

    return os;
}




////////////////////////////////////////////////////////////////////////////////
// MACROS                                                                     //
////////////////////////////////////////////////////////////////////////////////
#define _CH_MAX(_a_, _b_, _c_) \
    std::max({_a_, _b_, _c_})

#define _CH_MIN(_a_, _b_, _c_) \
    std::min({_a_, _b_, _c_})



////////////////////////////////////////////////////////////////////////////////
// Static Initializers                                                        //
////////////////////////////////////////////////////////////////////////////////
Color Color::fromHex(const std::string &hex)
{
    Color color;
    color.updateFrom(hex);

    return color;
}

Color Color::fromRGB(const RGB &value)
{
    Color color;
    color.updateFrom(value);

    return color;
}

Color Color::fromHSV(const HSV &value)
{
    Color color;
    color.updateFrom(value);

    return color;
}

Color Color::fromHSL(const HSL &value)
{
    Color color;
    color.updateFrom(value);

    return color;
}

Color Color::fromCMY(const CMY &value)
{
    Color color;
    color.updateFrom(value);

    return color;
}

////////////////////////////////////////////////////////////////////////////////
// Output Methods                                                             //
////////////////////////////////////////////////////////////////////////////////
std::string Color::toHex()
{
    std::stringstream ss;

    ss << std::hex
       << m_rgb.r
       << m_rgb.g
       << m_rgb.b;

    return ss.str();
}

Color::RGB Color::toRGB()
{
    return m_rgb;
}

Color::HSV Color::toHSV()
{
    return RGB_TO_HSV(m_rgb);
}

Color::HSL Color::toHSL()
{
    return RGB_TO_HSL(m_rgb);
}

Color::CMY Color::toCMY()
{
    return RGB_TO_CMY(m_rgb);
}


////////////////////////////////////////////////////////////////////////////////
// Input Methods                                                              //
////////////////////////////////////////////////////////////////////////////////
void Color::updateFrom(const std::string &hex)
{
    //COWTODO: Implement.
    m_rgb = RGB{255, 0, 255};
}

void Color::updateFrom(const RGB &value)
{
    m_rgb = value;
}

void Color::updateFrom(const HSV &value)
{
    m_rgb = HSV_TO_RGB(value);
}

void Color::updateFrom(const HSL &value)
{
    m_rgb = HSL_TO_RGB(value);
}

void Color::updateFrom(const CMY &value)
{
    m_rgb = CMY_TO_RGB(value);
}

////////////////////////////////////////////////////////////////////////////////
// Helper Functions                                                           //
////////////////////////////////////////////////////////////////////////////////
Color::HSV Color::RGB_TO_HSV(const RGB &rgb)
{
    //Formula taken from:
    //http://www.easyrgb.com/index.php?X=MATH&H=20#text20
    HSV hsv {0, 0, 0};

    //Make the values from range of (0,255) to (0,1);
    float normalized_r = (rgb.r / 255.0f);
    float normalized_g = (rgb.g / 255.0f);
    float normalized_b = (rgb.b / 255.0f);

    //Min, Max and Delta from RGB.
    float min_value   = _CH_MAX(normalized_r, normalized_g, normalized_b);
    float max_value   = _CH_MIN(normalized_r, normalized_g, normalized_b);
    float delta_value = max_value - min_value;


    hsv.v = max_value;

    //Color isn't gray - i.e. it has chroma.
    if(delta_value != 0)
    {
        hsv.s = (delta_value / max_value);

        #define _CALC_DELTA(_nr_) \
            (((max_value - _nr_) / 6.0f) + (delta_value / 2.0f)) / delta_value;

        float delta_r = _CALC_DELTA(normalized_r);
        float delta_g = _CALC_DELTA(normalized_g);
        float delta_b = _CALC_DELTA(normalized_b);

        #undef _CALC_DELTA

        if(normalized_r == max_value)
            hsv.h = (delta_b - delta_g);
        else if(normalized_g == max_value)
            hsv.h = (1.0f / 3.0f) + (delta_r - delta_b);
        else if(normalized_b == max_value)
            hsv.h = (2.0f / 3.0f) + (delta_g - delta_r);

        if(hsv.h < 0 ) hsv.h += 1;
        if(hsv.h > 1 ) hsv.h -= 1;
    }

    return hsv;
}

Color::HSL Color::RGB_TO_HSL(const RGB &rgb)
{
    //Formula taken from:
    //http://www.easyrgb.com/index.php?X=MATH&H=18#text18
    HSL hsl { 0, 0, 0 };

    //Make the values from range of (0,255) to (0,1);
    float normalized_r = (rgb.r / 255.0f);
    float normalized_g = (rgb.g / 255.0f);
    float normalized_b = (rgb.b / 255.0f);

    //Make the values from range of (0,255) to (0,1);
    float min_value   = _CH_MIN(normalized_r, normalized_g, normalized_b);
    float max_value   = _CH_MAX(normalized_r, normalized_g, normalized_b);
    float delta_value = (max_value - min_value);


    hsl.l = (max_value + min_value) / 2.0f;

    //Color isn't gray - i.e. it has chroma.
    if(delta_value != 0)
    {
        hsl.s = (hsl.l < 0.5f)
                ? (delta_value / (max_value + min_value))
                : (delta_value / (2 - max_value - min_value));

        #define _CALC_DELTA(_nr_) \
            (((max_value - _nr_) / 6.0f) + (delta_value / 2.0f)) / delta_value;

        float delta_r = _CALC_DELTA(normalized_r);
        float delta_g = _CALC_DELTA(normalized_g);
        float delta_b = _CALC_DELTA(normalized_b);

        #undef _CALC_DELTA

        if(normalized_r == max_value)
            hsl.h = (delta_b - delta_g);
        else if(normalized_g == max_value)
            hsl.h = (1.0f / 3.0f) + (delta_r - delta_b);
        else if(normalized_b == max_value)
            hsl.h = (2.0f / 3.0f) + (delta_g - delta_r);

        if(hsl.h < 0 ) hsl.h += 1;
        if(hsl.h > 1 ) hsl.h -= 1;
    }

    return hsl;
}

Color::CMY Color::RGB_TO_CMY(const RGB &rgb)
{
    //Formula taken from:
    //http://www.easyrgb.com/index.php?X=MATH&H=11#text11
    CMY cmy;

    cmy.c = 1.0f - (rgb.r / 255.0f);
    cmy.c = 1.0f - (rgb.g / 255.0f);
    cmy.c = 1.0f - (rgb.b / 255.0f);

    return cmy;
}


Color::RGB Color::HSV_TO_RGB(const HSV &hsv)
{
    //Formula taken from:
    //http://www.easyrgb.com/index.php?X=MATH&H=21#text21
    RGB rgb;

    if(hsv.s == 0)
    {
        rgb.r = static_cast<int>(hsv.v * 255.0f);
        rgb.g = static_cast<int>(hsv.v * 255.0f);
        rgb.b = static_cast<int>(hsv.v * 255.0f);

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
        { value_r = _tr_; value_g = _tg_; value_b = _tb_; }

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

    rgb.r = static_cast<int>(value_r * 255.0f);
    rgb.g = static_cast<int>(value_g * 255.0f);
    rgb.b = static_cast<int>(value_b * 255.0f);

    return rgb;
}

Color::RGB Color::HSL_TO_RGB(const HSL &hsl)
{
    //Formula taken:
    //http://www.easyrgb.com/index.php?X=MATH&H=19#text19
    RGB rgb;

    if(hsl.s == 0)
    {
        rgb.r = static_cast<int>(hsl.l * 255.0f);
        rgb.g = static_cast<int>(hsl.l * 255.0f);
        rgb.b = static_cast<int>(hsl.l * 255.0f);

        return rgb;
    }


    float value_2 = (hsl.l < 0.5 )
                  ? (hsl.l * (1.0f + hsl.s))
                  : (hsl.l + hsl.s) - (hsl.s * hsl.l);

    float value_1 = (2.0f * hsl.l) - value_2;

    float value_r = HSL_HUE_TO_RGB_HELPER(value_1, value_2, hsl.h + (1.0f / 3.0f));
    float value_g = HSL_HUE_TO_RGB_HELPER(value_1, value_2, hsl.h);
    float value_b = HSL_HUE_TO_RGB_HELPER(value_1, value_2, hsl.h - (1.0f / 3.0f));

    rgb.r = static_cast<int>(255.0f * value_r);
    rgb.g = static_cast<int>(255.0f * value_g);
    rgb.b = static_cast<int>(255.0f * value_b);
}

Color::RGB Color::CMY_TO_RGB(const CMY &value)
{
    //Formula taken from:
    //http://www.easyrgb.com/index.php?X=MATH&H=12#text12
    RGB rgb;

    rgb.r = static_cast<int>((1.0f - value.c) * 255.0f);
    rgb.g = static_cast<int>((1.0f - value.m) * 255.0f);
    rgb.b = static_cast<int>((1.0f - value.y) * 255.0f);

    return rgb;
}


////////////////////////////////////////////////////////////////////////////////
// Private Functions                                                          //
////////////////////////////////////////////////////////////////////////////////
float Color::HSL_HUE_TO_RGB_HELPER(float v1, float v2, float vH)
{
    if(vH < 0) vH += 1;
    if(vH > 1) vH -= 1;

    if((6 * vH) < 1)
        return (v1 + (v2 - v1) * 6.0f * vH);

    if((2 * vH) < 1)
        return v2;

    if((3 * vH) < 2)
        return (v1 + (v2 - v1) * (( 2.0f / 3.0f) - vH) * 6);

    return v1;
}
