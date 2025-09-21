#include <iostream>
#include <string>
#include "Image_Class.h"
#include "Grayscale filter.cpp"
#include "Black and White filter.cpp"
#include "Invert Image filter.cpp"
using namespace std;

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
}