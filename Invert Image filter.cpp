#include <iostream>
#include <string>
#include "Image_Class.h"
using namespace std;
// the third filter in our project
//  Invert the Image colors
int invertimage(string filename)
{
    Image image(filename);

    for (int i = 0; i < image.width; ++i)
    {
        for (int j = 0; j < image.height; ++j)
        {

            for (int k = 0; k < 3; ++k)
            {
                image(i, j, k) = 255 - image(i, j, k);
            }
        }
    }

    cout << "Pls enter image name to store new image\n";
    cout << "and specify extension .jpg, .bmp, .png, .tga: ";

    cin >> filename;
    image.saveImage(filename);
    cout << "Image saved successfully as " << filename << endl;
    return 0;
}