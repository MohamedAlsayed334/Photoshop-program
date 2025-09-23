#include <iostream>
#include <string>
#include "Image_Class.h"
#include "Crop image.cpp"
using namespace std;
//<<------------------------1------------------------->>
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
//<<------------------------2------------------------->>
// the second filter in our project
//  converting a colored image to black and white image
int BlackWhiteConvertion(string filename)
{
    Image image(filename);

    for (int i = 0; i < image.width; ++i)
    {
        for (int j = 0; j < image.height; ++j)
        {
            unsigned int average = 0;

            for (int k = 0; k < 3; ++k)
            {
                average += image(i, j, k);
            }

            average /= 3;
            if (average >= 128)
            {
                image(i, j, 0) = 255;
                image(i, j, 1) = 255;
                image(i, j, 2) = 255;
            }
            else
            {
                image(i, j, 0) = 0;
                image(i, j, 1) = 0;
                image(i, j, 2) = 0;
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
//<<------------------------3------------------------->>
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
//<<------------------------4------------------------->>
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

//-------------------menu----------------------

int main()
{
    string imagename, choose;
    cout << "Please enter the image name: ";
    cin >> imagename;
    cin.ignore(); // <------مهم جدا------->
                  // Input Buffer After cin >> imagename:
                  // ['i', 'm', 'a', 'g', 'e', '.', 'j', 'p', 'g', '\n']
                  // ↑
                  // After reading "image.jpg", the \n remains
    // getline() sees the \n and thinks: "Oh, empty line entered!"
    //     After cin.ignore():
    // Input Buffer: [ ]  // Empty
    // ↑
    // getline() now waits for actual user input
    cout << "please choose the filter (you can choose by number):\n";
    cout << "1- Grayscale Conversion\n";
    cout << "2- Black and White\n";
    cout << "3- Invert Image colors\n";
    cout << "4- Flip Image\n";
    cout << "5- Crop Image\n";
    cout << "Your choice: ";
    getline(cin, choose);
    if (choose == "1" || choose == "Grayscale Conversion")
    {
        GrayscaleConversion(imagename);
    }
    else if (choose == "2" || choose == "Black and White")
    {
        BlackWhiteConvertion(imagename);
    }
    else if (choose == "3" || choose == "Invert Image colors")
    {
        invertimage(imagename);
    }
    else if (choose == "4" || choose == "Flip Image")
    {
        flipimage(imagename);
    }
    else if (choose == "5" || choose == "Crop Image")
    {
        CropImage(imagename);
    }
}