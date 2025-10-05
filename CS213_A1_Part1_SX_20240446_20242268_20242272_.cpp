#include <iostream>
#include <string>
#include "Image_Class.h"
#include "look purple.cpp"
#include "Sunlight.cpp"
using namespace std;

/* "بسم الله الرحمن الرحيم"
-------------------------------------------
 Team Members:
 > Mazen Sherif Al-Shahat        20240446
 Work Done : Filters 1 ,7 ,9
 > Mohammed ElSayed AbdEl-Hamid  20242268
 Work Done : Filters 2 ,4 ,5 ,8
 > Mohammed Tamer Salah          20242272
 Work Done : Filters 3 ,6

 Menu was Done By All Team Members.
-------------------------------------------
 Program Details :
 it is a baby photoshop program that takes an image and apply a bunch of filters such as:
 1 - GrayScale Filter makes the image in Grey ratios like the old images.
 2 - Black & White makes the image in Black & white.
 3 - Invert Image Color inverts the color into the opposite one (e.g. black --> white)
 4 - Flip Image flips the image horizontally & vertically.
 5 - Crop Image crops the image to specified size & part of image.
 6 - Rotation Image rotates the image by 90 , 180 , 270 Degrees.
 -------------------------------------------
 */

//<<------------------------1------------------------->>
// the first step in the project
// converting a colored image to gray scale image
void GrayscaleConversion(Image &image)
{

    for (int i = 0; i < image.width; i++)
    {
        for (int j = 0; j < image.height; j++)
        {

            int red = image(i, j, 0);
            int green = image(i, j, 1);
            int blue = image(i, j, 2);

            int Greyscale = red * 0.299 + green * 0.587 + blue * 0.114;
            image(i, j, 0) = image(i, j, 1) = image(i, j, 2) = Greyscale;
        }
    }
}
//<<------------------------2------------------------->>
// the second filter in our project
//  converting a colored image to black and white image
void BlackWhiteConvertion(Image &image)
{
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
}
//<<------------------------3------------------------->>
// the third filter in our project
//  Invert the Image colors
void invertimage(Image &image)
{
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
}

//<<------------------------4------------------------->>
// the fourth filter in our project
//  flip the Image vertically and horizontally
void Verticalflip(Image &image)
{

    for (int i = 0; i < image.height / 2; ++i)
    {
        for (int j = 0; j < image.width; ++j)
        {
            pixel tempR = image.getPixel(j, i, 0);
            pixel tempG = image.getPixel(j, i, 1);
            pixel tempB = image.getPixel(j, i, 2);
            image(j, i, 0) = image.getPixel(j, image.height - i - 1, 0);
            image(j, i, 1) = image.getPixel(j, image.height - i - 1, 1);
            image(j, i, 2) = image.getPixel(j, image.height - i - 1, 2);
            image(j, image.height - i - 1, 0) = tempR;
            image(j, image.height - i - 1, 1) = tempG;
            image(j, image.height - i - 1, 2) = tempB;
        }
    }
}
void Horizontalflip(Image &image)
{
    for (int i = 0; i < image.width / 2; ++i)
    {
        for (int j = 0; j < image.height; ++j)
        {
            pixel tempR = image.getPixel(i, j, 0);
            pixel tempG = image.getPixel(i, j, 1);
            pixel tempB = image.getPixel(i, j, 2);
            image(i, j, 0) = image.getPixel(image.width - 1 - i, j, 0);
            image(i, j, 1) = image.getPixel(image.width - 1 - i, j, 1);
            image(i, j, 2) = image.getPixel(image.width - 1 - i, j, 2);
            image(image.width - 1 - i, j, 0) = tempR;
            image(image.width - 1 - i, j, 1) = tempG;
            image(image.width - 1 - i, j, 2) = tempB;
        }
    }
}
void flipimage(Image &filename)
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
        flipimage(filename);
    }
}

//<<------------------------5------------------------->>
// the filter num. 5 in our project
//  crop the image

Image CROP(Image &image, int height, int width, int x, int y)
{
    Image croppedImage(width, height);
    for (int i = 0; i < width; ++i)
    {
        for (int j = 0; j < height; ++j)
        {
            croppedImage(i, j, 0) = image(x + i, y + j, 0);
            croppedImage(i, j, 1) = image(x + i, y + j, 1);
            croppedImage(i, j, 2) = image(x + i, y + j, 2);
        }
    }
    return croppedImage;
}
void CropImage(Image &image)
{
    cout << "pleas enter the x and y point that you will start to crop from\n";
    int x, y;
    cout << "x:";
    cin >> x;
    cout << "y:";
    cin >> y;
    cout << "pleas enter the width and height of the cropped image\n";
    int w, h;
    cout << "width:";
    cin >> w;
    cout << "height:";
    cin >> h;
    if (x < 0 || y < 0 || w <= 0 || h <= 0 || x + w > image.width || y + h > image.height)
    {
        cout << "Error: Invalid crop dimensions,try again" << endl;
        CropImage(image);
    }

    image = CROP(image, h, w, x, y);
}

//<<------------------------6------------------------->>
// the filter num. 6 in our project
//  rotate  the image by 90, 180, 270 degrees
Image rotate90(Image &org)
{
    Image output(org.height, org.width);
    for (int i = 0; i < org.width; ++i)
    {
        for (int j = 0; j < org.height; ++j)
        {
            for (int k = 0; k < org.channels; ++k)
                output(org.height - 1 - j, i, k) = org(i, j, k);
        }
    }
    return output;
}
Image rotate180(Image &org)
{
    Image output(org.width, org.height);
    for (int i = 0; i < org.width; ++i)
    {
        for (int j = 0; j < org.height; ++j)
        {
            for (int k = 0; k < org.channels; ++k)
                output(org.width - 1 - i, org.height - 1 - j, k) = org(i, j, k);
        }
    }
    return output;
}
Image rotate270(Image &org)
{
    Image output(org.height, org.width);
    for (int i = 0; i < org.width; ++i)
    {
        for (int j = 0; j < org.height; ++j)
        {
            for (int k = 0; k < org.channels; ++k)
                output(j, org.width - 1 - i, k) = org(i, j, k);
        }
    }
    return output;
}
int rotate_image(Image &filename)
{
    int Degree;
    cout << "Enter rotation degree (90 / 180 / 270): ";
    cin >> Degree;

    if (Degree == 90)
        filename = rotate90(filename);
    else if (Degree == 180)
        filename = rotate180(filename);
    else if (Degree == 270)
        filename = rotate270(filename);
    else
    {
        cout << "Invalid degree!\n";
        return 1;
    }
    return 0;
}
// filter 7 in our project
// Darken and Lighten Image filter

void DarkenLightenImage(Image &img)
{
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
            DarkenLightenImage(img);
        }

        for (int i = 0; i < img.width; ++i)
        {
            for (int j = 0; j < img.height; ++j)
            {
                for (int k = 0; k < 3; ++k)
                {
                    img(i, j, k) = img(i, j, k) * (1 - factor);
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
            DarkenLightenImage(img);
        }

        for (int i = 0; i < img.width; ++i)
        {
            for (int j = 0; j < img.height; ++j)
            {
                for (int k = 0; k < 3; ++k)
                {
                    float num;
                    num = img(i, j, k);
                    num = num * (1 + factor);
                    if (num > 255)
                    {
                        img(i, j, k) = 255;
                    }
                    else
                    {
                        img(i, j, k) = num;
                    }
                }
            }
        }
    }
    else
    {
        cout << "Invalid choice. Please choose 1 or 2." << endl;
        DarkenLightenImage(img);
    }
}
// filter 8 Resize Image

Image resize(Image &image, int i_width, int i_height)
{

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
            if (image.width == i_width && image.height == i_height)
            {
                return image;
            }
            //  Round to nearest integer to go to nearest pixel
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
    return resizedImage;
}
void ResizeImage(Image &img)
{
    cout << "Choose an option(you can choose by number):\n";
    cout << "1. Shrink Image\n";
    cout << "2. Stretch Image\n";
    cout << "Your choice: ";
    int choice;
    cin >> choice;
    if (choice == 1)
    {
        cout << "please enter the new size of the image\n";
        int i_width, i_height;
        cout << "Width: ";
        cin >> i_width;
        cout << "Height: ";
        cin >> i_height;
        cin.ignore();
        if (i_width >= img.width || i_height >= img.height)
        {
            cout << "Error: New dimensions must be less than the original dimensions, try again" << endl;
            ResizeImage(img);
        }
        else
        {
            resize(img, i_width, i_height);
        }
    }
    else if (choice == 2)
    {
        cout << "please enter the new size of the image\n";
        int i_width, i_height;
        cout << "Width: ";
        cin >> i_width;
        cout << "Height: ";
        cin >> i_height;
        cin.ignore();
        if (i_width <= img.width || i_height <= img.height)
        {
            cout << "Error: New dimensions must be less than the original dimensions, try again" << endl;
            ResizeImage(img);
        }
        else
        {
            resize(img, i_width, i_height);
        }
    }
    else
    {
        cout << "Invalid choice. Please choose 1 or 2." << endl;
        ResizeImage(img);
    }
}

// filter 9 Merge images

void Merge_images(Image &img, string imagename2)
{

    Image image2(imagename2);

    int width1 = img.width, width2 = image2.width, height1 = img.height, height2 = image2.height;
    int maxW, maxH;
    if (width1 > width2)
    {
        maxW = width1;
    }

    else
        maxW = width2;

    if (height1 > height2)
    {
        maxH = height1;
    }
    else
        maxH = height2;

    img = resize(img, maxW, maxH);
    image2 = resize(image2, maxW, maxH);

    Image image3(maxW, maxH);

    for (int i = 0; i < img.width; i++)
    {

        for (int j = 0; j < img.height; j++)
        {

            int red1 = img(i, j, 0);
            int green1 = img(i, j, 1);
            int blue1 = img(i, j, 2);

            int red2 = image2(i, j, 0);
            int green2 = image2(i, j, 1);
            int blue2 = image2(i, j, 2);

            image3(i, j, 0) = round((red1 + red2) / 2);
            image3(i, j, 1) = round((green1 + green2) / 2);
            image3(i, j, 2) = round((blue1 + blue2) / 2);
        }
    }
    img = image3;
}

//<<-----------------------10------------------------>>
void Save_image(Image &img, const string &org_name) // it automatically checks if the extinction is right or not
{
    string filename;
    string Y_N;
    cout << "Would you like to save the image by the old name or not? (Yes/No)";
    cin >> Y_N;
    if (Y_N == "Yes" || Y_N == "yes")
    {
        img.saveImage(org_name);
        cout << "Image saved successfully as " << org_name << endl;
    }
    else if (Y_N == "No" || Y_N == "no")
    {
        cout << "Pls enter image name to store new image\n";
        cout << "and specify extension .jpg, .bmp, .png, .tga: ";
        cin >> filename;
        img.saveImage(filename);
        cout << "Image saved successfully as " << filename << endl;
    }
    else
    {
        cout << "Invalid response ,try agin\n";
        Save_image(img, org_name);
    }
}
//-------------------menu----------------------
int main()
{
    cout << "welcome to our Baby photoshop Program, pls press Enter to start\n";
    string start;
    getline(cin, start);
    if ((start == ""))
    {
        Image img;
        string imagename;
        cout << "Please enter the image name: ";
        getline(cin, imagename);

        if (!img.loadNewImage(imagename))
        {
            cout << "Error loading image!\n";
            return 1;
        }
        cout << "Image loaded successfully: " << imagename << "\n";
        int running = 1;
        while (running)
        {
            string choice;
            cout << "Please choose the filter (you can choose by number):\n";
            cout << "0- Exit Program\n";
            cout << "1- Grayscale Conversion\n";
            cout << "2- Black and White\n";
            cout << "3- Invert Image colors\n";
            cout << "4- Flip Image\n";
            cout << "5- Crop Image\n";
            cout << "6- Rotation Image\n";
            cout << "7- Darken and Lighten Image filter\n";
            cout << "8- Resize Image\n";
            cout << "9- Merge Images\n";
            cout << "10- Wano Night (Purple look)\n";
            cout << "11- Wano Sunlight\n";
            cout << "12- Save Image\n";
            cout << "13- Load New Image\n";
            cout << "Your choice: ";
            getline(cin, choice);
            // cin.ignore(); <<---- سبب المشكله
            if (choice == "1" || choice == "Grayscale Conversion")
            {
                GrayscaleConversion(img);
            }
            else if (choice == "2" || choice == "Black and White")
            {
                BlackWhiteConvertion(img);
            }
            else if (choice == "3" || choice == "Invert Image colors")
            {
                invertimage(img);
            }
            else if (choice == "4" || choice == "Flip Image")
            {
                flipimage(img);
            }
            else if (choice == "5" || choice == "Crop Image")
            {
                CropImage(img);
            }
            else if (choice == "6" || choice == "Rotation Image")
            {
                rotate_image(img);
            }
            else if (choice == "7" || choice == "Darken and Lighten Image filter")
            {
                DarkenLightenImage(img);
            }
            else if (choice == "8" || choice == "Resize Image")
            {
                ResizeImage(img);
            }
            else if (choice == "9" || choice == "Merge Images")
            {
                cout << "Please enter the second image name: ";
                string imagename2;
                cin >> imagename2;
                cin.ignore();
                Merge_images(img, imagename2);
            }
            else if (choice == "10" || choice == "Wano Night" || choice == "Purple look")
            {
                WanoNight(img);
            }
            else if (choice == "11" || choice == "Wano Sunlight")
            {
                WanoSunlight(img);
            }
            else if (choice == "0")
            {
                string saved;
                cout << "Do you want to save the changes before leaving? (Yes - No)";
                cin >> saved;
                if (saved == "Yes" || saved == "yes")
                {
                    Save_image(img, imagename);
                }
                running = 0; // <-- exit loop
            }
            else if (choice == "12" || choice == "Save Image")
            {
                Save_image(img, imagename);
                running = 0;
            }
            else if (choice == "13" || choice == "Laod New Image")
            {
                string saved;
                cout << "Do you want to save the changes before leaving? (Yes - No)";
                cin >> saved;
                if (saved == "Yes" || saved == "yes")
                {
                    Save_image(img, imagename);
                }
                else if (saved == "No" || saved == "no")
                {
                    cout << "Changes not Saved\n";
                }
                else
                {
                    cout << "Invalid choice!! Save Skipped";
                }
                cout << "Please enter the new image name: ";
                cin >> imagename;
                cin.ignore();
                if (!img.loadNewImage(imagename))
                {
                    cout << "Error loading image!\n";
                }
                else
                {
                    cout << "Image loaded successfully: " << imagename << "\n";
                }
            }
            else
            {
                cout << "Invalid choice!!\n"
                     << "Pls choose from Menu\n";
            }
            cout << "---------------------------------------------------------\n";
            cout << "---------------------------------------------------------\n";
            cout << "---------------------------------------------------------\n";
        }
    }
}
