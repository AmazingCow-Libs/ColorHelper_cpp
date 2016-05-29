//----------------------------------------------------------------------------//
//               █      █                                                     //
//               ████████                                                     //
//             ██        ██                                                   //
//            ███  █  █  ███        Color.h                                   //
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

#ifndef __ColorHelper_include_Color_h__
#define __ColorHelper_include_Color_h__

//std
#include <string>
#include <ostream>


class Color
{
    // InnerTypes //
public:
    struct RGB  { int   r;   int g;   int b;          };
    struct HSV  { float h; float s; float v;          };
    struct HSL  { float h; float s; float l;          };
    struct CMY  { float c; float m; float y;          };
    struct CMYK { float c; float m; float y; float k; };


    // Static Initializers //
public:
    static Color fromHex(const std::string &hex);
    static Color fromRGB(const RGB &value);
    static Color fromHSV(const HSV &value);
    static Color fromHSL(const HSL &value);
    static Color fromCMY(const CMY &value);


    // Output Methods //
public:
    std::string toHex();
    RGB         toRGB();
    HSV         toHSV();
    HSL         toHSL();
    CMY         toCMY();


    // Input Methods //
public:
    void updateFrom(const std::string &hex);
    void updateFrom(const RGB &value);
    void updateFrom(const HSV &value);
    void updateFrom(const HSL &value);
    void updateFrom(const CMY &value);


    // Helper Functions //
public:
    static HSV RGB_TO_HSV(const RGB &value);
    static HSL RGB_TO_HSL(const RGB &value);
    static CMY RGB_TO_CMY(const RGB &value);

    static RGB HSV_TO_RGB(const HSV &value);
    static RGB HSL_TO_RGB(const HSL &value);
    static RGB CMY_TO_RGB(const CMY &value);


    // Private Functions //
private:
    static float HSL_HUE_TO_RGB_HELPER(float v1, float v2, float vh);

    // iVars //
private:
    RGB m_rgb;
};



////////////////////////////////////////////////////////////////////////////////
// Stream Operators                                                           //
////////////////////////////////////////////////////////////////////////////////
std::ostream& operator<<(std::ostream &os, const Color::RGB &value);
std::ostream& operator<<(std::ostream &os, const Color::HSV &value);
std::ostream& operator<<(std::ostream &os, const Color::HSL &value);
std::ostream& operator<<(std::ostream &os, const Color::CMY &value);



#endif // defined( __ColorHelper_include_Color_h__ ) //
