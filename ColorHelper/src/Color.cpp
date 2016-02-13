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

//Usings
using namespace colorhelper;

// Static initializers //
Color Color::fromHex(const std::string &hex)
{

}

Color Color::fromRGB(int r, int g, int b)
{
    return Color(ColorRepresentation {
        .rgb       = RGB { r, g, b };
        .colorType = ColorType::RGB;
    });
}

Color Color::fromHSV(float h, float s, float v)
{
    return Color(ColorRepresentation {
        .HSV       = HSV { h, s, v };
        .colorType = ColorType::HSV;
    });
}

Color Color::fromHSL(float h, float s, float l)
{
    return Color(ColorRepresentation {
        .HSL       = HSL { h, s, l };
        .colorType = ColorType::HSL;
    });
}

Color Color::fromCMY(float c, float m, float y)
{
    return Color(ColorRepresentation {
        .CMY       = CMY { c, m, y };
        .colorType = ColorType::CMY;
    });
}

Color Color::fromCMYK(float c, float m, float y, float k)
{
    return Color(ColorRepresentation {
        .CMYK      = CMYK { c, m, y, k };
        .colorType = ColorType::CMYK;
    });
}


// Hex //
void Color::setHex(const std::string &hex)
{

}

std::string getHex() const
{

}


// RGB //
//Setters.
void Color::setRGB(int r, int g, int b)
{
    m_currentRepresentation.rgb       = RGB { r, g, b };
    m_currentRepresentation.colorType = ColorType::RGB;
}

void Color::setRGB_Red(int r)
{

}

void Color::setRGB_Green(int g)
{

}

void Color::setRGB_Blue(int b)
{

}

//Getters.
RGB Color::getRGB() const
{
}

int Color::getRGB_Red() const
{

}

int Color::getRGB_Green() const
{

}
int Color::getRGB_Blue() const
{

}


    // HSV //
public:
    //Setters.
    void setHSV           (float h, float s, float v);
    void setHSV_Hue       (float h);
    void setHSV_Saturation(float s);
    void setHSV_Value     (float v);
    //Getters.
    HSV   getHSV           () const;
    float getHSV_Hue       () const;
    float getHSV_Saturation() const;
    float getHSV_Value     () const;

    // HSL //
public:
    //Setters.
    void setHSL           (float h, float s, float l);
    void setHSL_Hue       (float h);
    void setHSL_Saturation(float s);
    void setHSL_Lumiance  (float l);
    //Getters.
    HSL   getHSL           () const;
    float getHSV_Hue       () const;
    float getHSV_Saturation() const;
    float getHSV_Lumiance  () const;

    // CMY //
public:
    //Setters.
    void setCMY         (float c, float m, float y);
    void setCMY_Cyan    (float c);
    void setCMY_Magenta (float m);
    void setCMY_Yellow  (float y);
    //Getters.
    CMY   getCMY         () const;
    float getCMY_Cyan    () const;
    float getCMY_Magenta () const;
    float getCMY_Yellow  () const;

    // CMYK //
public:
    //Setters.
    void setCMYK         (float c, float m, float y, float k);
    void setCMYK_Cyan    (float c);
    void setCMYK_Magenta (float m);
    void setCMYK_Yellow  (float y);
    void setCMYK_Key     (float k);
    //Getters.
    CMYK  getCMYK         () const;
    float getCMYK_Cyan    () const;
    float getCMYK_Magenta () const;
    float getCMYK_Yellow  () const;
    float getCMYK_Key     () const;

    // CTOR/DTOR //
private:
    Color();
public:
    ~Color();

    // iVars //
private:
    ColorRepresentation m_currentRepresentation;

}; //Class Color.
}  //Namespace colorhelper.

#endif // defined( __ColorHelper_include_Color_h__ ) //
