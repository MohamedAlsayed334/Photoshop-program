#include <iostream>
#include <string>
#include "Image_Class.h"
using namespace std;

void newimage(string filename, int &choice)
{
    Image image(filename);
    cout << "please enter the new size of the image\n";
    int newW, newH;
    cout << "Width: ";
    cin >> newW;
    cout << "Height: ";
    cin >> newH;
    if ((newW >= image.width || newH >= image.height) && choice == 1)
    {
        cout << "Error: New dimensions must be less than the original dimensions, try again" << endl;
        newimage(filename, choice);
    }
    if ((newW <= image.width || newH <= image.height) && choice == 2)
    {
        cout << "Error: New dimensions must be greater than the original dimensions, try again" << endl;
        newimage(filename, choice);
    }

    Image resizedImage(newW, newH);

    float factor_x = float(image.width) / newW;
    float factor_y = float(image.height) / newH;

    for (int i = 0; i < newW; ++i)
    {
        for (int j = 0; j < newH; ++j)
        {
            // make a new pixel to be in  old coordinates
            float xold = i * factor_x;
            float yold = j * factor_y;

            // 2. Round to nearest integer to go to nearest pixel
            int nearest_X = round(xold);
            int nearest_Y = round(yold);

            if (nearest_X >= image.width)
                nearest_X = image.width - 1;
            if (nearest_Y >= image.height)
                nearest_Y = image.height - 1;

            resizedImage(i, j, 0) = image(nearest_X, nearest_Y, 0);
            resizedImage(i, j, 1) = image(nearest_X, nearest_Y, 1);
            resizedImage(i, j, 2) = image(nearest_X, nearest_Y, 2);
        }
    }

    cout << "Pls enter image name to store new image\n";
    cout << "and specify extension .jpg, .bmp, .png, .tga: ";
    cin >> filename;
    cout << "Image saved successfully as " << filename << endl;
    resizedImage.saveImage(filename);
}

void ResizeImage(string filename)
{
    cout << "Choose an option(you can choose by number):\n";
    cout << "1. Shrink Image\n";
    cout << "2. Stretch Image\n";
    cout << "Your choice: ";
    int choice;
    cin >> choice;
    if (choice == 1)
    {
        newimage(filename, choice);
    }
    else if (choice == 2)
    {
        newimage(filename, choice);
    }
    else
    {
        cout << "Invalid choice. Please choose 1 or 2." << endl;
        ResizeImage(filename);
    }
}

void resize_merge(string filename, int &i_width, int &i_height)
{
    Image image(filename);

    Image resizedImage(i_width, i_height);

    float factor_x = float(image.width) / i_width;
    float factor_y = float(image.height) / i_height;

    for (int i = 0; i < i_width; ++i)
    {
        for (int j = 0; j < i_height; ++j)
        {
            // make a new pixel to be in  old coordinates
            float xold = i * factor_x;
            float yold = j * factor_y;

            // 2. Round to nearest integer to go to nearest pixel
            int nearest_X = round(xold);
            int nearest_Y = round(yold);

            if (nearest_X >= image.width)
                nearest_X = image.width - 1;
            if (nearest_Y >= image.height)
                nearest_Y = image.height - 1;

            resizedImage(i, j, 0) = image(nearest_X, nearest_Y, 0);
            resizedImage(i, j, 1) = image(nearest_X, nearest_Y, 1);
            resizedImage(i, j, 2) = image(nearest_X, nearest_Y, 2);
        }
    }

    image = resizedImage;
}
