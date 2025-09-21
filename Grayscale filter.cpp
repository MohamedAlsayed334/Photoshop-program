#include <iostream>
#include <string>
#include "Image_Class.h"
using namespace std;
// the first step in the project
// converting a colored image to gray scale image
void GrayscaleConversion(string filename)
{
    Image image(filename);

    for (int i = 0; i < image.width; ++i)
    {
        for (int j = 0; j < image.height; ++j)
        {
            unsigned int avg = 0;

            for (int k = 0; k < 3; ++k)
            {
                avg += image(i, j, k);
            }

            avg /= 3;

            image(i, j, 0) = avg;
            image(i, j, 1) = avg;
            image(i, j, 2) = avg;
        }
    }

    cout << "Pls enter image name to store new image\n";
    cout << "and specify extension .jpg, .bmp, .png, .tga: ";

    cin >> filename;
    image.saveImage(filename);
    cout << "Image saved successfully as " << filename << endl;
}