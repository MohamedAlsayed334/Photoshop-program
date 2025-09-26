#include <iostream>
#include <string>
#include "Image_Class.h"
#include "Darken and Lighten Image filter .cpp"
#include "resize.cpp"
using namespace std;
//<<------------------------1------------------------->>
// the first step in the project
// converting a colored image to gray scale image
void GrayscaleConversion(string filename)
{
    Image image(filename);

      for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {

            int red = image(i, j, 0);
            int green = image(i, j, 1);
            int blue = image(i, j, 2);

            int Greyscale = red*0.299 + green*0.587 + blue*0.114;
            image(i, j, 0) = image(i, j, 1) = image(i, j, 2) = Greyscale;
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
        flipimage(filename);
    }
    return 0;
}

//<<------------------------5------------------------->>
// the filter num. 5 in our project
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

//<<------------------------6------------------------->>
// the filter num. 6 in our project
//  rotate  the image by 90, 180, 270 degrees
Image rotate90(const Image &org) // Function to rotate the image 90 Degrees
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
Image rotate180(const Image &org)
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
Image rotate270(const Image &org) //  also here the width is the height of image & vice versa.
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
int rotate_image(string filename)
{
    int Degree;
    cout << "Enter rotation degree (90 / 180 / 270): ";
    cin >> Degree;

    Image rotated;
    if (Degree == 90)
        rotated = rotate90(filename);
    else if (Degree == 180)
        rotated = rotate180(filename);
    else if (Degree == 270)
        rotated = rotate270(filename);
    else
    {
        cout << "Invalid degree!\n";
        return 1;
    }
    cout << "Enter output filename (with extension .jpg/.png/.bmp/.tga):\n";
    cin >> filename;
    rotated.saveImage(filename);
    cout << "Image saved successfully as " << filename;
    return 0;
}
// filter 8 Resize Image



// filter 9 Merge images

void Merge_images(string &imagename, string &imagename2) {

    Image image1(imagename);
    Image image2(imagename2);

    int width1 = image1.width, width2 = image2.width, height1 = image1.height, height2 = image2.height;
    int maxW, maxH;
    if (width1 > width2) {
        maxW = width1;
    }

    else maxW = width2;

    if (height1 > height2) {
        maxH = height1;
    }
    else maxH = height2;

    resize_merge(imagename, maxW, maxH);
    resize_merge(imagename2, maxW, maxH);


    Image image3(maxW, maxH);

    for (int i = 0; i < image1.width; i++) {

        for (int j = 0; j < image1.height; j++) {

            int red1 = image1(i, j, 0);
            int green1 = image1(i, j, 1);
            int blue1 = image1(i, j, 2);

            int red2 = image2(i, j, 0);
            int green2 = image2(i, j, 1);
            int blue2 = image2(i, j, 2);

            image3(i, j, 0) = round((red1+red2)/2);
            image3(i, j, 1) = round((green1+green2)/2);
            image3(i, j, 2) = round((blue1+blue2)/2);
        }
    }
}




//<<------------------------7------------------------->>
// the filter num. 7 in our project
//  Darken and Lighten Image filter

//-------------------menu----------------------
int main()
{
    string imagename, choice;
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
    Image image(imagename); // checks loading process
    if (!image.loadNewImage(imagename))
    {
        cout << "Error loading image!\n";
        return 1;
    }
    cout << "Please choose the filter (you can choose by number):\n";
    cout << "1- Grayscale Conversion\n";
    cout << "2- Black and White\n";
    cout << "3- Invert Image colors\n";
    cout << "4- Flip Image\n";
    cout << "5- Crop Image\n";
    cout << "6- Rotation Image\n";
    cout << "7- Darken and Lighten Image filter\n";
    cout << "8- Resize Image\n";
    cout << "9- Merge Images\n";
    cout << "Your choice: ";
    getline(cin, choice);
    if (choice == "1" || choice == "Grayscale Conversion")
    {
        GrayscaleConversion(imagename);
    }
    else if (choice == "2" || choice == "Black and White")
    {
        BlackWhiteConvertion(imagename);
    }
    else if (choice == "3" || choice == "Invert Image colors")
    {
        invertimage(imagename);
    }
    else if (choice == "4" || choice == "Flip Image")
    {
        flipimage(imagename);
    }
    else if (choice == "5" || choice == "Crop Image")
    {
        CropImage(imagename);
    }
    else if (choice == "6" || choice == "Rotation Image")
    {
        rotate_image(imagename);
    }
    else if (choice == "7" || choice == "Darken and Lighten Image filter")
    {
        DarkenLightenImage(imagename);
    }
    else if (choice == "8" || choice == "Resize Image")
    {
        ResizeImage(imagename);
    }
    else if (choice == "9" || choice == "Merge Images") {
        string imagename2;
        cin >> imagename2;
        Merge_images(imagename, imagename2);

    }
}
//<<------------------------a way to edit on the same image ------------------------->>
//<<----------- but chatgpt halp me here and i think he help me too much------------->>
// #include <iostream>
// #include <string>
// using namespace std;

// // one full cycle
// bool runOnce() {
//     string imagename, choice;
//     cout << "Please enter the image name: ";
//     cin >> imagename;
//     cin.ignore(); // clear newline

//     cout << "please choose the filter (you can choose by number):\n";
//     cout << "1- Grayscale Conversion\n";
//     cout << "2- Black and White\n";
//     cout << "3- Invert Image colors\n";
//     cout << "4- Flip Image\n";
//     cout << "5- Crop Image\n";
//     cout << "6- Darken and Lighten Image filter\n";
//     cout << "Your choice: ";
//     getline(cin, choice);

//     if (choice == "1" || choice == "Grayscale Conversion")
//         GrayscaleConversion(imagename);
//     else if (choice == "2" || choice == "Black and White")
//         BlackWhiteConvertion(imagename);
//     else if (choice == "3" || choice == "Invert Image colors")
//         invertimage(imagename);
//     else if (choice == "4" || choice == "Flip Image")
//         flipimage(imagename);
//     else if (choice == "5" || choice == "Crop Image")
//         CropImage(imagename);
//     else if (choice == "6" || choice == "Darken and Lighten Image filter")
//         DarkenLightenImage(imagename);

//     // ask if repeat
//     string response;
//     cout << "Do you want to apply another filter? (yes/no): ";
//     cin >> response;
//     cin.ignore(); // clean newline

//     if (response == "yes" || response == "y" || response == "Y" || response == "Yes")
//         return true;   // repeat whole process
//     return false;      // stop
// }

// int main() {
//     while (runOnce()) {
//         // keeps repeating until user says "no"
//     }
//     cout << "Thank you for using our Baby photoshop. Goodbye!" << endl;
//     return 0;
// }