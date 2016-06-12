//----------------------------------------------------------------------------//
//               █      █                                                     //
//               ████████                                                     //
//             ██        ██                                                   //
//            ███  █  █  ███        Color.h                                   //
//            █ █        █ █        Colorelper_cpp                           //
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

//
#include <ostream>
#include <string>
#include <vector>

namespace ColorHelper {

////////////////////////////////////////////////////////////////////////////////
// Types                                                                      //
////////////////////////////////////////////////////////////////////////////////
typedef std::string HEX;

struct RGB  { int   r;   int g;   int b;          }; //Range of (0, 255)
struct HSV  { float h; float s; float v;          }; //Range of (0,   1)
struct HSL  { float h; float s; float l;          }; //Range of (0,   1)
struct CMY  { float c; float m; float y;          }; //Range of (0,   1)
struct CMYK { float c; float m; float y; float k; }; //Range of (0,   1)

struct Color
{
    union {
        RGB  rgb;
        HSV  hsv;
        HSL  hsl;
        CMY  cmy;
        CMYK cmyk;
    };
};

////////////////////////////////////////////////////////////////////////////////
// Conversions                                                                //
////////////////////////////////////////////////////////////////////////////////
//RGB - HEX
HEX RGB_to_HEX(const RGB &rgb);
RGB HEX_to_RGB(const HEX &hex);

//RGB - HSV
HSV RGB_to_HSV(const RGB &rgb);
RGB HSV_to_RGB(const HSV &hsv);

//RGB - HSL
HSL RGB_to_HSL(const RGB &rgb);
RGB HSL_to_RGB(const HSL &hsl);

//RGB - CMY
CMY RGB_to_CMY(const RGB &rgb);
RGB CMY_to_RGB(const CMY &cmy);

//RGB - CMYK
CMYK RGB_to_CMYK(const RGB &rgb);  //COWTODO: Implement this function
RGB CMYK_to_RGB(const CMYK &cmyk); //COWTODO: Implement this function

//RGB - Name
std::string RGB_to_Name(const RGB &rgb, bool *found = nullptr);
RGB Name_To_RGB(const std::string &name, bool *found = nullptr);


////////////////////////////////////////////////////////////////////////////////
// Color Wheel Functions                                                      //
////////////////////////////////////////////////////////////////////////////////
//Complementary
std::vector<HSL> Complementary(const HSL &hsl);
std::vector<HSV> Complementary(const HSV &hsv);

//Split Complementary
std::vector<HSL> SplitComplementary(const HSL &hsl);
std::vector<HSV> SplitComplementary(const HSV &hsv);

//Analogous
std::vector<HSL> Analogous(const HSL &hsl);
std::vector<HSV> Analogous(const HSV &hsv);

//Triad
std::vector<HSL> Triad(const HSL &hsl, float angleInDegrees = 120);
std::vector<HSV> Triad(const HSV &hsv, float angleInDegrees = 120);

//Tetrad
std::vector<HSL> Tetrad(const HSL &hsl, float angleInDegrees = 90);
std::vector<HSV> Tetrad(const HSV &hsv, float angleInDegrees = 90);

//Tetrad Square
std::vector<HSL> TetradSquare(const HSL &hsl, float angleInDegrees = 90);
std::vector<HSV> TetradSquare(const HSV &hsv, float angleInDegrees = 90);


////////////////////////////////////////////////////////////////////////////////
// Stream Operators                                                           //
////////////////////////////////////////////////////////////////////////////////
std::ostream& operator<<(std::ostream &os, const RGB &rgb);
std::ostream& operator<<(std::ostream &os, const HSV &hsv);
std::ostream& operator<<(std::ostream &os, const HSL &hsl);
std::ostream& operator<<(std::ostream &os, const CMY &cmy);


}//namespace ColorHelper {
#endif // defined( __ColorHelper_include_Color_h__ ) //
