#include <iostream>
#include <string>
#include "Image_Class.h"
using namespace std;
// the fourth filter in our project
//  flip the Image vertically and horizontally
void Verticalflip(string imageVflip)
{
    Image image(imageVflip);

    for (int i = 0; i < image.height / 2; ++i)
    {
        for (int j = 0; j < image.width; ++j)
        {
            pixel tempR = image.getPixel(j, i, 0);
            pixel tempB = image.getPixel(j, i, 1);
            pixel tempG = image.getPixel(j, i, 2);
            image(j, i, 0) = image.getPixel(j, image.height - i - 1, 0);
            image(j, i, 1) = image.getPixel(j, image.height - i - 1, 1);
            image(j, i, 2) = image.getPixel(j, image.height - i - 1, 2);
            image(j, image.height - i - 1, 0) = tempR;
            image(j, image.height - i - 1, 1) = tempB;
            image(j, image.height - i - 1, 2) = tempG;
        }
    }
    cout << "Pls enter image name to store new image\n";
    cout << "and specify extension .jpg, .bmp, .png, .tga: ";

    cin >> imageVflip;
    image.saveImage(imageVflip);
    cout << "Image saved successfully as " << imageVflip << endl;
}
void Horizontalflip(string imageHflip)
{
    Image image(imageHflip);

    for (int i = 0; i < image.width / 2; ++i)
    {
        for (int j = 0; j < image.height; ++j)
        {
            pixel tempR = image.getPixel(i, j, 0);
            pixel tempB = image.getPixel(i, j, 1);
            pixel tempG = image.getPixel(i, j, 2);
            image(i, j, 0) = image.getPixel(image.width - 1 - i, j, 0);
            image(i, j, 1) = image.getPixel(image.width - 1 - i, j, 1);
            image(i, j, 2) = image.getPixel(image.width - 1 - i, j, 2);
            image(image.width - 1 - i, j, 0) = tempR;
            image(image.width - 1 - i, j, 1) = tempB;
            image(image.width - 1 - i, j, 2) = tempG;
        }
    }
    cout << "Pls enter image name to store new image\n";
    cout << "and specify extension .jpg, .bmp, .png, .tga: ";

    cin >> imageHflip;
    image.saveImage(imageHflip);
    cout << "Image saved successfully as " << imageHflip << endl;
}
int flipimage(string filename)
{
    cout << "Which flip do you want?\n";
    cout << "1- Vertical flip\n";
    cout << "2- Horizontal flip\n";
    cout << "Your choice: ";
    string choose;
    cin >> choose;
    if (choose == "1" || choose == "Vertical flip")
    {
        Verticalflip(filename);
    }
    else if (choose == "2" || choose == "Horizontal flip")
    {
        Horizontalflip(filename);
    }
    else
    {
        cout << "Invalid choice. Please choose 1 or 2." << endl;
    }
    return 0;
}