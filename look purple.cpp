#include <iostream>
#include <string>
#include "Image_Class.h"
using namespace std;

void WanoNight(Image &img)
{
    for (int i = 0; i < img.width; ++i)
    {
        for (int j = 0; j < img.height; ++j)
        {
            // purple tone
            int r = int(img(i, j, 0) * 1.2); // More red
            int g = int(img(i, j, 1) * 0.7); //  less green
            int b = int(img(i, j, 2) * 1.3); // More blue

            // make a valid range
            r = min(r, 255);
            g = min(g, 255);
            b = min(b, 255);

            img(i, j, 0) = r;
            img(i, j, 1) = g;
            img(i, j, 2) = b;
        }
    }
}
