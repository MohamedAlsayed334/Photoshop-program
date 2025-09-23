#include <iostream>
#include <string>
#include "Image_Class.h"
using namespace std;
// the  filter number 8 in our project
//  crop the image
int CropImage(string filename)
{
    Image image(filename);
    cout << "pleas enter the x and y point that you will start to crop from\n";
    int x, y;
    cout << "x:";
    cin >> x;
    cout << "y:";
    cin >> y;
    cout << "pleas enter the width and height of the croped image\n";
    int w, h;
    cout << "width:";
    cin >> w;
    cout << "height:";
    cin >> h;
    if (x < 0 || y < 0 || w <= 0 || h <= 0 || x + w > image.width || y + h > image.height)
    {
        cout << "Error: Invalid crop dimensions,try again" << endl;
        CropImage(filename);
    }
    Image croppedImage(w, h);
    for (int i = 0; i < w; ++i)
    {
        for (int j = 0; j < h; ++j)
        {
            croppedImage(i, j, 0) = image(x + i, y + j, 0);
            croppedImage(i, j, 1) = image(x + i, y + j, 1);
            croppedImage(i, j, 2) = image(x + i, y + j, 2);
        }
    }

    cout << "Pls enter image name to store new image\n";
    cout << "and specify extension .jpg, .bmp, .png, .tga: ";

    cin >> filename;
    croppedImage.saveImage(filename);
    cout << "Image saved successfully as " << filename << endl;
    return 0;
}