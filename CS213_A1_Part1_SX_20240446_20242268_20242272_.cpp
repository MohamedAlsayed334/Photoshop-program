#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <limits>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include "Image_Class.h"
using namespace std;
vector<Image> undo;
vector<Image> redo;

/* "بسم الله الرحمن الرحيم"
-------------------------------------------
 Team Members:
 > Mazen Sherif Al-Shahat        20240446
 Work Done : Filters 1,4,7,10
 > Mohammed ElSayed AbdEl-Hamid  20242268
 Work Done : Filters 2,5,8,11
 > Mohammed Tamer Salah          20242272
 Work Done : Filters 3,6,9,12

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
( Will be replaced by Diagram Doc isa)
 -------------------------------------------
 */
//<<-----------------------00------------------------>>
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
//<<-----------------------[-/+] -> [undo/redo] ------------------------->>

void save_current(const Image img)
{
    undo.push_back(img);
    redo.clear();
}
void undo_function(Image &img)
{
    if (undo.empty())
    {
        cout << "No more undos available." << endl;
        return;
    }
    redo.push_back(img);
    img = undo.back();
    undo.pop_back();
    cout << "Undo performed." << endl;
}
void redo_function(Image &img)
{
    if (redo.empty())
    {
        cout << "No more redos available." << endl;
        return;
    }
    undo.push_back(img);
    img = redo.back();
    redo.pop_back();
    cout << "Redo performed." << endl;
}

//<<------------------------1------------------------->>
// the first step in the project
// converting a colored image to gray scale image
void GrayscaleConversion(Image &image)
{
    save_current(image);
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
    save_current(image);
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
    save_current(image);
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
// the fourth filter
// Merging two different images into one
// forward declaration of resize and crop function to be used in the merge function

Image resize(Image &image, int i_width, int i_height);
Image CROP(Image &image, int height, int width, int x, int y);

void Merge_Images(Image &img, Image img2)
{

    Image image3(img.width, img.height);

    for (int i = 0; i < img.width; i++)
    {

        for (int j = 0; j < img.height; j++)
        {

            int red1 = img(i, j, 0);
            int green1 = img(i, j, 1);
            int blue1 = img(i, j, 2);

            int red2 = img2(i, j, 0);
            int green2 = img2(i, j, 1);
            int blue2 = img2(i, j, 2);

            image3(i, j, 0) = round((red1 + red2) / 2);
            image3(i, j, 1) = round((green1 + green2) / 2);
            image3(i, j, 2) = round((blue1 + blue2) / 2);
        }
    }
    img = image3;
}

void MERGE(Image &img, string img2name)
{
    save_current(img);
    Image img2(img2name);

    int width1 = img.width, width2 = img2.width, height1 = img.height, height2 = img2.height;
    int maxW, maxH, minW, minH;
    if (width1 > width2)
    {
        maxW = width1;
        minW = width2;
    }
    else
    {
        maxW = width2;
        minW = width1;
    }
    if (height1 > height2)
    {
        maxH = height1;
        minH = height2;
    }
    else
    {
        maxH = height2;
        minH = height1;
    }

    if (width1 == width2 && height1 == height2)
    {
        Merge_Images(img, img2);
    }

    else
    {
        cout << "Your images do no have the same dimension, Choose an option: " << endl;
        cout << "Option 1- Resize both images to the largest dimensions\n";
        cout << "Option 2- Merge only the common area between the images (Notice that the image will be cropped)\n";
        int option;
        cin >> option;
        if (option == 1)
        {
            resize(img, maxW, maxH);
            resize(img2, maxW, maxH);
            Merge_Images(img, img2);
        }
        else if (option == 2)
        {

            img = CROP(img, minH, minW, 0, 0);
            img2 = CROP(img2, minH, minW, 0, 0);
            Merge_Images(img, img2);
        }
    }
}

//<<------------------------5------------------------->>
// the fifth filter in our project
// flip the Image vertically and horizontally
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
    save_current(filename);
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
    save_current(filename);
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
//<<------------------------7------------------------->>
// filter 7 in our project
// Darken and Lighten Image filter

void DarkenLightenImage(Image &img)
{
    save_current(img);
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
//<<------------------------8------------------------->>
// the filter num. 8 in our project
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
    save_current(image);
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
    cin.ignore();
    if (x < 0 || y < 0 || w <= 0 || h <= 0 || x + w > image.width || y + h > image.height)
    {
        cout << "Error: Invalid crop dimensions,try again" << endl;
        CropImage(image);
    }

    image = CROP(image, h, w, x, y);
}
//<<------------------------9------------------------->>
// filter 9 Frame Image
// framing an image with a simple or fancy frame
void Add_FrameStars(Image &img, int numStars, int thickness)
{
    srand(static_cast<unsigned int>(time(nullptr)));

    int width = img.width;
    int height = img.height;

    for (int n = 0; n < numStars; ++n)
    {
        int x, y;
        int border = rand() % 4;

        if (border == 0)
        {
            x = rand() % width;
            y = rand() % thickness;
        }
        else if (border == 1)
        {
            x = rand() % width;
            y = height - thickness + (rand() % thickness);
        }
        else if (border == 2)
        {
            x = rand() % thickness;
            y = rand() % height;
        }
        else
        {
            x = width - thickness + (rand() % thickness);
            y = rand() % height;
        }

        unsigned char r = 255, g = 255, b = 200;

        for (int dy = -1; dy <= 1; ++dy)
        {
            for (int dx = -1; dx <= 1; ++dx)
            {
                if (abs(dx) + abs(dy) <= 1)
                {
                    int nx = x + dx;
                    int ny = y + dy;
                    if (nx >= 0 && nx < width && ny >= 0 && ny < height)
                    {
                        img.setPixel(nx, ny, 0, r);
                        img.setPixel(nx, ny, 1, g);
                        img.setPixel(nx, ny, 2, b);
                    }
                }
            }
        }
    }
}

Image Add_Frame(const Image &org)
{
    save_current(org);
    int thickness = 0;
    int frameStyle = 0;
    unsigned char cR = 0, cG = 0, cB = 0;
    unsigned char cR2 = 255, cG2 = 255, cB2 = 255;
    int numstar = 0;

    string choice;
    cout << "Choose frame style:\n1- Simple Frame\n2- Fancy Frame\n> ";
    getline(cin, choice);

    if (choice == "1" || choice == "Simple Frame" || choice == "simple frame")
    {
        cout << "Enter frame thickness (pixels): ";
        if (!(cin >> thickness))
            thickness = 10;
        cout << "S = Solid color\nC = Checkerboard\n> ";
        char styleChoice;
        cin >> styleChoice;
        if (styleChoice == 'S' || styleChoice == 's')
        {
            frameStyle = 0;
            int rr, gg, bb;
            cout << "Enter RGB color values (0 - 255 each): ";
            cin >> rr >> gg >> bb;
            cR = static_cast<unsigned char>(clamp(rr, 0, 255));
            cG = static_cast<unsigned char>(clamp(gg, 0, 255));
            cB = static_cast<unsigned char>(clamp(bb, 0, 255));
        }
        else
        {
            frameStyle = 1;
        }
    }
    else if (choice == "2" || choice == "Fancy Frame" || choice == "fancy frame")
    {
        cout << "Enter frame thickness (pixels): ";
        if (!(cin >> thickness))
            thickness = 10;
        cout << "G = Gradient\n> ";
        char styleChoice;
        cin >> styleChoice;
        if (styleChoice == 'G' || styleChoice == 'g')
        {
            frameStyle = 2;
            cout << "1- Gold\n2- Silver\n3- Bronze\n4- Custom\n> ";
            string special;
            cin >> special;

            if (special == "1" || special == "gold")
            {
                cR = 184;
                cG = 134;
                cB = 0; // top
                cR2 = 200;
                cG2 = 150;
                cB2 = 0; // bottom
            }
            else if (special == "2" || special == "silver")
            {
                cR = cG = cB = 105;
                cR2 = cG2 = cB2 = 230;
            }
            else if (special == "3" || special == "bronze")
            {
                cR = 102;
                cG = 51;
                cB = 0;
                cR2 = 205;
                cG2 = 127;
                cB2 = 50;
            }
            else // custom
            {
                int rr, gg, bb;
                cout << "Enter first RGB color (top): ";
                cin >> rr >> gg >> bb;
                cR = static_cast<unsigned char>(clamp(rr, 0, 255));
                cG = static_cast<unsigned char>(clamp(gg, 0, 255));
                cB = static_cast<unsigned char>(clamp(bb, 0, 255));

                cout << "Enter second RGB color (bottom): ";
                cin >> rr >> gg >> bb;
                cR2 = static_cast<unsigned char>(clamp(rr, 0, 255));
                cG2 = static_cast<unsigned char>(clamp(gg, 0, 255));
                cB2 = static_cast<unsigned char>(clamp(bb, 0, 255));
            }

            cout << "Choose number of stars (20 / 40 / 80): ";
            cin >> numstar;
        }
    }
    else
    {
        cout << "Invalid choice! Defaulting to solid black frame.\n";
        frameStyle = 0;
        cR = cG = cB = 0;
    }

    // flush newline left in stream so future getline works.
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    int F_width = org.width + 2 * thickness;
    int F_height = org.height + 2 * thickness;
    Image Frame(F_width, F_height);

    for (int y = 0; y < F_height; ++y)
    {
        for (int x = 0; x < F_width; ++x)
        {
            bool inside = (x >= thickness && x < thickness + org.width && y >= thickness && y < thickness + org.height);
            if (inside)
            {
                for (int c = 0; c < 3; ++c)
                {
                    Frame.setPixel(x, y, c,
                                   org.getPixel(x - thickness, y - thickness, c));
                }
            }
            else
            {
                unsigned char r, g, b;
                if (frameStyle == 0)
                {
                    r = cR;
                    g = cG;
                    b = cB;
                }
                else if (frameStyle == 1)
                {
                    if (((x / 10) + (y / 10)) % 2 == 0)
                        r = g = b = 255;
                    else
                        r = g = b = 0;
                }
                else // gradient
                {
                    double t = static_cast<double>(y) / max(1, F_height - 1);
                    r = static_cast<unsigned char>((1 - t) * cR + t * cR2);
                    g = static_cast<unsigned char>((1 - t) * cG + t * cG2);
                    b = static_cast<unsigned char>((1 - t) * cB + t * cB2);
                }

                Frame.setPixel(x, y, 0, r);
                Frame.setPixel(x, y, 1, g);
                Frame.setPixel(x, y, 2, b);
            }
        }
    }
    if (numstar > 0)
    {
        Add_FrameStars(Frame, numstar, thickness);
    }
    return Frame;
}
//<<------------------------10------------------------>>
// filter 10 edge detection
// edge detecting image
void edge_detection(Image &img)
{
    save_current(img);
    // 1- grey scale

    GrayscaleConversion(img);

    // 2- gaussian filter (blur)

    Image blured(img.width, img.height);

    for (int i = 1; i < img.width - 1; i++)
    {
        for (int j = 1; j < img.height - 1; j++)
        {

            int val = img(i, j, 0) * 4;
            int new_val = 0;
            vector<int> V1(8);
            V1[0] = img(i, j + 1, 0) * 2;
            V1[1] = img(i, j - 1, 0) * 2;
            V1[2] = img(i - 1, j - 1, 0) * 1;
            V1[3] = img(i - 1, j, 0) * 2;
            V1[4] = img(i - 1, j + 1, 0) * 1;
            V1[5] = img(i + 1, j - 1, 0) * 1;
            V1[6] = img(i + 1, j, 0) * 2;
            V1[7] = img(i + 1, j + 1, 0) * 1;

            int cnt = val;
            for (int k = 0; k < 8; k++)
            {
                cnt += V1[k];
            }

            new_val = cnt / 16;
            blured(i, j, 0) = new_val;
            blured(i, j, 1) = new_val;
            blured(i, j, 2) = new_val;
        }
    }

    // 3- sobel operator

    Image edged_image(blured.width, blured.height);
    Image edged_angles(blured.width, blured.height);

    for (int i = 1; i < blured.width - 1; i++)
    {
        for (int j = 1; j < blured.height - 1; j++)
        {

            int val = blured(i, j, 0) * 0;
            int gx = val;

            vector<int> V1(8);
            V1[0] = blured(i - 1, j - 1, 0) * -1;
            V1[1] = blured(i - 1, j, 0) * 0;
            V1[2] = blured(i - 1, j + 1, 0) * 1;

            V1[3] = blured(i, j - 1, 0) * -2;
            V1[4] = blured(i, j + 1, 0) * 2;

            V1[5] = blured(i + 1, j - 1, 0) * -1;
            V1[6] = blured(i + 1, j, 0) * 0;
            V1[7] = blured(i + 1, j + 1, 0) * 1;

            for (int k = 0; k < 8; k++)
            {
                gx += V1[k];
            }

            // run the gy kernel

            int gy = val;
            vector<int> V2(8);
            V2[0] = blured(i - 1, j - 1, 0) * -1;
            V2[1] = blured(i - 1, j, 0) * -2;
            V2[2] = blured(i - 1, j + 1, 0) * -1;

            V2[3] = blured(i, j - 1, 0) * 0;
            V2[4] = blured(i, j + 1, 0) * 0;

            V2[5] = blured(i + 1, j - 1, 0) * 1;
            V2[6] = blured(i + 1, j, 0) * 2;
            V2[7] = blured(i + 1, j + 1, 0) * 1;

            for (int u = 0; u < 8; u++)
            {
                gy += V2[u];
            }

            double gradient_magnitude = sqrt(gx * gx + gy * gy);
            int gm = gradient_magnitude;

            (gradient_magnitude > 70) ? gm = 0 : gm = 255;
            img(i, j, 0) = gm;
            img(i, j, 1) = gm;
            img(i, j, 2) = gm;
        }
    }
}
//<<------------------------11------------------------>>
// filter 11 Resize Image

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
    save_current(img);
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
//<<-----------------------12------------------------>>
// Filter 12 Blur Image (end of Hero level)
// bluring images by box blur algorithm.
// Building summed-area table (integral image)
vector<vector<vector<long long>>> buildSummedTable(const Image &img)
{
    int width = img.width;
    int height = img.height;

    // summed[y][x][channel]
    vector<vector<vector<long long>>> summed(height,
                                             vector<vector<long long>>(width, vector<long long>(3, 0)));

    // initialize first pixel
    for (int c = 0; c < 3; c++)
    {
        summed[0][0][c] = img.getPixel(0, 0, c);
    }

    // first row
    for (int x = 1; x < width; x++)
    {
        for (int c = 0; c < 3; c++)
        {
            summed[0][x][c] = img.getPixel(x, 0, c) + summed[0][x - 1][c];
        }
    }

    // first column
    for (int y = 1; y < height; y++)
    {
        for (int c = 0; c < 3; c++)
        {
            summed[y][0][c] = img.getPixel(0, y, c) + summed[y - 1][0][c];
        }
    }

    // rest of the table
    for (int y = 1; y < height; y++)
    {
        for (int x = 1; x < width; x++)
        {
            for (int c = 0; c < 3; c++)
            {
                summed[y][x][c] = img.getPixel(x, y, c) + summed[y - 1][x][c] + summed[y][x - 1][c] - summed[y - 1][x - 1][c];
            }
        }
    }

    return summed;
}

// Box blur using summed-area table
Image boxBlur(const Image &img)
{
    save_current(img);
    int k = 0;
    cout << "Enter the size of kernel (a.k.a. how blurry of image) : ";
    cin >> k;
    int width = img.width;
    int height = img.height;
    Image blurred(width, height);

    auto summed = buildSummedTable(img);

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            // rectangle corners
            int x1 = max(0, x - k);
            int y1 = max(0, y - k);
            int x2 = min(width - 1, x + k);
            int y2 = min(height - 1, y + k);

            long long area = static_cast<long long>(x2 - x1 + 1) * (y2 - y1 + 1);
            for (int c = 0; c < 3; c++)
            {
                long long total = summed[y2][x2][c];
                if (x1 > 0)
                    total -= summed[y2][x1 - 1][c];
                if (y1 > 0)
                    total -= summed[y1 - 1][x2][c];
                if (x1 > 0 && y1 > 0)
                    total += summed[y1 - 1][x1 - 1][c];

                int avg = static_cast<int>(total / area);
                blurred.setPixel(x, y, c, avg);
            }
        }
    }

    return blurred;
}

//<<-----------------------13------------------------>>
// filter no. 13 Wano Sunlight
void WanoSunlight(Image &img)
{
    save_current(img);
    for (int i = 0; i < img.width; ++i)
    {
        for (int j = 0; j < img.height; ++j)
        {
            int r = int(img(i, j, 0) * 1.2);  // More red = more warm
            int g = int(img(i, j, 1) * 1.1);  //  More green = make a yellow color with red
            int b = int(img(i, j, 2) * 0.85); // less blue

            // make a valid range
            r = min(r, 255);
            g = min(g, 255);

            img(i, j, 0) = r;
            img(i, j, 1) = g;
            img(i, j, 2) = b;
        }
    }
}
//<<-----------------------14------------------------>>
// filter 14 oil painting
void oil_painting(Image &img)
{
    save_current(img);
    Image img2(img.width, img.height);

    int radius = 1;
    int intinsity_level = 20;

    for (int i = 0; i < img.width; i++)
    {
        for (int j = 0; j < img.height; j++)
        {
            vector<int> level_intensity(20, 0);
            vector<int> r_level(20, 0);
            vector<int> g_level(20, 0);
            vector<int> b_level(20, 0);

            for (int x = -radius; x <= radius; x++)
            {
                for (int y = -radius; y <= radius; y++)
                {
                    int pixelX = i + x;
                    int pixelY = j + y;

                    if (pixelX >= 0 && pixelX < img.width && pixelY >= 0 && pixelY < img.height)
                    {
                        int red = img(pixelX, pixelY, 0);
                        int green = img(pixelX, pixelY, 1);
                        int blue = img(pixelX, pixelY, 2);

                        double intinsity = (red + green + blue) / 3;
                        int level = (intinsity * intinsity_level) / 256;

                        level_intensity[level]++;
                        r_level[level] += red;
                        g_level[level] += green;
                        b_level[level] += blue;
                    }
                }
            }

            int max_level = 0;
            int max_index;
            for (int i = 0; i < level_intensity.size(); i++)
            {

                if (level_intensity[i] > max_level)
                {
                    max_level = level_intensity[i];
                    max_index = i;
                }
            }

            int result_r = r_level[max_index] / max_level;
            int result_g = g_level[max_index] / max_level;
            int result_b = b_level[max_index] / max_level;

            img2(i, j, 0) = result_r;
            img2(i, j, 1) = result_g;
            img2(i, j, 2) = result_b;
        }
    }

    img = img2;
}
//<<-----------------------15------------------------>>
// filter no.15 Wano Old TV
//<<-----------------------16------------------------>>
// filter no. 16 Wano Night (Purple look)
void WanoNight(Image &img)
{
    save_current(img);
    for (int i = 0; i < img.width; ++i)
    {
        for (int j = 0; j < img.height; ++j)
        {
            // purple tone
            int r = int(img(i, j, 0) * 1.2); // More red
            int g = int(img(i, j, 1) * 0.7); //  less green
            int b = int(img(i, j, 2) * 1.3); // More blue

            // make a valid range
            r = min(r, 255);
            b = min(b, 255);

            img(i, j, 0) = r;
            img(i, j, 1) = g;
            img(i, j, 2) = b;
        }
    }
}
//<<-----------------------17------------------------>>
// filter Samurai infrared effect

void Infrared_Image(Image &img)
{
    save_current(img);
    for (int y = 0; y < img.height; ++y)
    {
        for (int x = 0; x < img.width; ++x)
        {
            unsigned char R, G, B;
            R = img(x, y, 0);
            G = img(x, y, 1);
            B = img(x, y, 2);

            float intensity = 0.299f * R + 0.587f * G + 0.114f * B;
            intensity = 255.0f - intensity;
            float t = intensity / 255.0f;
            unsigned char r, g, b;
            r = 255;
            g = static_cast<unsigned char>(11 + t * (255 - 11));
            b = static_cast<unsigned char>(11 + t * (255 - 11));

            r = min(255, max(0, int(r)));
            g = min(255, max(0, int(g)));
            b = min(255, max(0, int(b)));

            img(x, y, 0) = r;
            img(x, y, 1) = g;
            img(x, y, 2) = b;
        }
    }
}
//<<-----------------------18------------------------>>
// filter Skewing Images
//<<-----------------------19------------------------>>
// filter increase Saturation
/*------------------- Description --------------------

 this filter makes the colors stronger and more vivid
 by make the user enter the percentage of saturation he need to make

*/
void image_Saturation(Image &img)
{
    save_current(img);
    string choice;
    float factor, percentage;
    cout << "Choose an option(you can choose by number):\n";
    cout << "1. Increase Saturation\n";
    cout << "2. Decrease Saturation\n";
    cout << "Your choice: ";
    cin >> choice;
    if (choice == "1" || choice == "Increase Saturation")
    {
        cout << "Enter Increase Saturation percentage (as a num.): ";
        cin >> percentage;
        factor = percentage / 100;
        if (factor <= 0 || factor > 1)
        {
            cout << "Invalid factor. Please enter a percentage between 0% and 100%" << endl;
            image_Saturation(img);
        }
    }
    else if (choice == "2" || choice == "Decrease Saturation")
    {
        cout << "Enter Decrease Saturation percentage (as a num.): ";
        cin >> percentage;
        factor = percentage / 100;
        if (factor <= 0 || factor > 1)
        {
            cout << "Invalid factor. Please enter a percentage between 0% and 100%" << endl;
            image_Saturation(img);
        }
    }
    else
    {
        cout << "Invalid choice. Please choose 1 or 2." << endl;
        image_Saturation(img);
    }
    Image gray_img = img;
    GrayscaleConversion(gray_img);
    factor = 1 + (percentage / 100.0);
    for (int i = 0; i < img.width; i++)
    {
        for (int j = 0; j < img.height; j++)
        {
            double r = gray_img(i, j, 0);
            double g = gray_img(i, j, 1);
            double b = gray_img(i, j, 2);
            r = r + (img(i, j, 0) - r) * factor;
            g = g + (img(i, j, 1) - g) * factor;
            b = b + (img(i, j, 2) - b) * factor;
            img(i, j, 0) = min(max(int(r), 0), 255);
            img(i, j, 1) = min(max(int(g), 0), 255);
            img(i, j, 2) = min(max(int(b), 0), 255);
        }
    }
}

//=============================================
//=============================================
//=============================================
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
            cout << "00- Save Image\n";
            cout << "000- load New Image\n";
            cout << "1- Grayscale Conversion\n";
            cout << "2- Black and White\n";
            cout << "3- Invert Image colors\n";
            cout << "4- Merge Images\n";
            cout << "5- Flip Image\n";
            cout << "6- Rotation Image\n";
            cout << "7- Darken and Lighten Image filter\n";
            cout << "8- Crop Image\n";
            cout << "9- Frame Image\n";
            cout << "10- Edge Detection\n";
            cout << "11- Resize Image\n";
            cout << "12- Blur Image\n";
            cout << "13- Wano Sunlight\n";
            cout << "14- Oil Painting\n";
            cout << "15- \n";
            cout << "16- Wano Night (Purple look)\n";
            cout << "17- Infrared Image\n";
            cout << "18- \n";
            cout << "19- Image Saturation\n";
            cout << "20- \n";
            cout << "21- Undo\n";
            cout << "22- Redo\n";
            cout << "Your choice: ";
            getline(cin, choice);
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
            else if (choice == "4" || choice == "Merge Image")
            {
                cout << "Please enter the second image name: ";
                string imagename2;
                getline(cin, imagename2);
                // cin.ignore();
                MERGE(img, imagename2);
            }
            else if (choice == "5" || choice == "Flip Image")
            {
                flipimage(img);
            }
            else if (choice == "6" || choice == "Rotation Image")
            {
                rotate_image(img);
            }
            else if (choice == "7" || choice == "Darken and Lighten Image filter")
            {
                DarkenLightenImage(img);
            }
            else if (choice == "8" || choice == "Crop Image")
            {
                CropImage(img);
            }
            else if (choice == "9" || choice == "Frame Images")
            {
                img = Add_Frame(img);
            }
            else if (choice == "10" || choice == "Edge Detection Image")
            {
                edge_detection(img);
            }
            else if (choice == "11" || choice == "Resize Image")
            {
                ResizeImage(img);
            }
            else if (choice == "12" || choice == "Blur Image")
            {
                img = boxBlur(img);
            }

            else if (choice == "13" || choice == "Wano Sunlight")
            {
                WanoSunlight(img);
            }
            else if (choice == "14" || choice == "Oil Image")
            {
                oil_painting(img);
            }
            else if (choice == "16" || choice == "Wano Night" || choice == "Purple look")
            {
                WanoNight(img);
            }
            else if (choice == "17" || choice == "Infrared Image")
            {
                Infrared_Image(img);
            }
            else if (choice == "19" || choice == "Image Saturation")
            {
                image_Saturation(img);
            }
            else if (choice == "21" || choice == "Undo")
            {
                undo_function(img);
            }
            else if (choice == "22" || choice == "Redo")
            {
                redo_function(img);
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
            else if (choice == "00" || choice == "Save Image")
            {
                Save_image(img, imagename);
                running = 0;
            }
            else if (choice == "000" || choice == "Laod New Image")
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
