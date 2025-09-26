#include <iostream>
#include <string>
#include "Image_Class.h"
using namespace std;
string DarkenLightenImage(string filename)
{
    Image image(filename);
    int choice;
    float factor, percentage;
    cout << "Choose an option(you can choose by number):\n";
    cout << "1. Darken Image\n";
    cout << "2. Lighten Image\n";
    cout << "Your choice: ";
    cin >> choice;

    if (choice == 1)
    {
        cout << "Enter darkening percentage (as a num.): ";
        cin >> percentage;
        factor = percentage / 100;
        if (factor <= 0 || factor > 1)
        {
            cout << "Invalid factor. Please enter a percentage between 0% and 100%" << endl;
            DarkenLightenImage(filename);
        }

        for (int i = 0; i < image.width; ++i)
        {
            for (int j = 0; j < image.height; ++j)
            {
                for (int k = 0; k < 3; ++k)
                {
                    image(i, j, k) = image(i, j, k) * (1 - factor);
                }
            }
        }
    }
    else if (choice == 2)
    {
        cout << "Enter lightening percentage (as a num.): ";
        cin >> percentage;
        factor = percentage / 100;
        if (factor <= 0 || factor > 1)
        {
            cout << "Invalid factor. Please enter a percentage between 0% and 100%" << endl;
            DarkenLightenImage(filename);
        }

        for (int i = 0; i < image.width; ++i)
        {
            for (int j = 0; j < image.height; ++j)
            {
                for (int k = 0; k < 3; ++k)
                {
                    float num;
                    num = image(i, j, k);
                    num = num * (1 + factor);
                    if (num > 255)
                    {
                        image(i, j, k) = 255;
                    }
                    else
                    {
                        image(i, j, k) = num;
                    }
                }
            }
        }
    }
    else
    {
        cout << "Invalid choice. Please choose 1 or 2." << endl;
        DarkenLightenImage(filename);
    }

    cout << "Pls enter image name to store new image\n";
    cout << "and specify extension .jpg, .bmp, .png, .tga: ";
    cin >> filename;
    cout << "Image saved successfully as " << filename << endl;
    image.saveImage(filename);
    return filename;
}