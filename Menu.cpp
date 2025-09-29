#include <iostream>
#include <string>
#include "Image_Class.h"
#include "Darken and Lighten Image filter .cpp"
#include "resize.cpp"
using namespace std;

/* "بسم الله الرحمن الرحيم"
-------------------------------------------
 Team Members:
 > Mazen ----------              20240---
 Work Done : Filters 1 ,4
 > Mohammed ElSayed AbdEl-Hamid  20242268
 Work Done : Filters 2 ,5
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
}
void Horizontalflip(Image &image)
{
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
    image = croppedImage;
}

//<<------------------------6------------------------->>
// the filter num. 6 in our project
//  rotate  the image by 90, 180, 270 degrees
Image rotate90(Image &org) // Function to rotate the image 90 Degrees
{
    Image output(org.height, org.width); // here the width is the height of image & vice versa.
    for (int i = 0; i < org.width; ++i)
    {
        for (int j = 0; j < org.height; ++j)
        {
            for (int k = 0; k < org.channels; ++k)
                output(org.height - 1 - j, i, k) = org(i, j, k); // this formula calculates the new position of each pixel.
        } // the index of new pos is (height of old image - 1 - the old col index ,  the old row index)
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
        } // it is easier as it is just swap between pixels of height & Width.
    }
    return output;
}
Image rotate270(Image &org) //  also here the width is the height of image & vice versa.
{
    Image output(org.height, org.width);
    for (int i = 0; i < org.width; ++i)
    {
        for (int j = 0; j < org.height; ++j)
        {
            for (int k = 0; k < org.channels; ++k)
                output(j, org.width - 1 - i, k) = org(i, j, k);
        } // the new position is ( the old col. index ,the old width - 1 - the old row index )
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
// filter 8 Resize Image

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

    img = resize_merge(img, maxW, maxH);
    image2 = resize_merge(image2, maxW, maxH);

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

//<<------------------------7------------------------->>
// the filter num. 7 in our project
//  Darken and Lighten Image filter
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
        cout << "Invalid response\n";
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
            cout << "10- Save Image\n";
            cout << "11- Load New Image\n";
            cout << "Your choice: " << "\n";
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
            else if (choice == "10" || choice == "Save Image")
            {
                Save_image(img, imagename);
                running = 0;
            }
            else if (choice == "11" || choice == "Laod New Image")
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
