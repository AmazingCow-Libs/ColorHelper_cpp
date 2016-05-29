
#include "../include/Color.h"
#include <iostream>

using namespace std;


int main()
{
    auto color = Color::fromRGB({255, 0, 255});
    auto rgb = color.toRGB();
    auto hsv = color.toHSV();
    auto hsl = color.toHSL();
    auto cmy = color.toCMY();

    cout << rgb << endl;
    cout << hsv << endl;
    cout << hsl << endl;
    cout << cmy << endl;
}

