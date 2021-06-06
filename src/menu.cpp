/*
Copyright (c) 2021 Marcin Salamandra

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/


#include "../inc/image.hh"
#include <limits>


/**
 * @brief Print error logs
 */
void errorLog() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<int>::max(), '\n');
    std::cerr << "Error. Improper input.\n";
}

/**
 * @brief Print user menu
 */
void printMenu() {
    // user menu
    std::cout << "\nUser menu - image processing\n";
    std::cout << "l - load an image\n";
    std::cout << "s - save current state of the image\n";
    std::cout << "d - display current state of the image\n";
    std::cout << "c - select new colour that will be processed(only for colorful images)\n";
    std::cout << "o - convert PPM to PGM(only for colorful images)\n";
    std::cout << "n - add negative filter to an image\n";
    std::cout << "t - add threshold filter to an image\n";
    std::cout << "b - add half-threshold of black filter to an image\n";
    std::cout << "w - add half-threshold of white filter to an image\n";
    std::cout << "g - add gamma correction filter to an image\n";
    std::cout << "a - add level adjustment liter to an image\n";
    std::cout << "k - add contouring filter to an image\n";
    std::cout << "x - add horizontal blurring filter to an image\n";
    std::cout << "y - add vertical blurring filter to an image\n";
    std::cout << "f - add full blurring filter to an image\n";
    std::cout << "h - add histogram stretching filter to an image\n";
    std::cout << "q - quit the program\n";
}


/**
 * @brief Check whether user input is float pointing number or not
 * @param in User input
 * @return Boolean value - whether the user input is float pointing number or not
 */
bool isDouble(std::string in) {
    bool dot_found = false;

    // first character has to be digit
    if(!isdigit(in[0])) {
        errorLog();
        return false;
    }
    // rest of the characters have to be digits, however there can be one dot
    for(unsigned int i = 1; i < in.length(); ++i) {
        if(!isdigit(in[i]) && in[i] != '.') {
            errorLog();
            return false;
        }
        // there can be only one dot
        if(in[i] == '.' && dot_found) {
            errorLog();
            return false;
        }
        // remember that we have found one dot
        if(in[i] == '.' && !dot_found) {
            dot_found = true;
        }
    }
    return true;
}


/**
 * @brief Check whether user input is integer or not
 * @param in User input
 * @return Boolean value - whether the user input is integer or not
 */
bool isInteger(std::string in) {
    for(unsigned int i = 0; i < in.length(); ++i) {
        if(!isdigit(in[i])) {
            errorLog();
            return false;
        }
    }
    return true;
}


int main() {
    std::string selection = " ";    // for user's selection              
    bool loaded = false;            // whether or not image is loaded 
    std::string file_name;          // for loading and saving images
    Image img;                      // Image class object for our image

    // parameters that are required by some functions
    double threshold;               // parameter for thresholding
    double level;                   // parameter for level adjustment
    double gamma;                   // parameter for gamma correction
    int radius;                     // parameter for blurring
    std::string param_val;          // entered value of parameter

    while(selection[0] != 'q') {
        // user menu
        printMenu();

        // user's selection
        std::cout << "\nYour selection: ";
        std::cin >> selection;
        std::cout << "\n";

        system("clear");

        // process an image according to user's selection
        if(selection.length() == 1) {
            switch(selection[0]) {
            case 'l':
                std::cout << "Enter text file name with saved image: ";
                std::cin >> file_name;
                loaded = img.load(file_name);

                if(loaded) {
                    std::cout << "Image loaded successfully.\n";
                }
                break;
            case 's':
                if(loaded) {
                    std::cout << "Enter text file name with saved image: ";
                    std::cin >> file_name;
                    if(img.save(file_name)) {
                        std::cout << "Image saved successfully.\n";
                    }
                }
                else {   
                    std::cerr << "Error. No image has been loaded yet.\n";
                }
                break;
            case 'd':
                if(loaded) {
                    img.display();
                    std::cout << "Image displayed successfully.\n";
                }
                else {    
                    std::cerr << "Error. No image has been loaded yet.\n";
                }
                break;
            case 'c':
                if(loaded) {
                    if(img.selectColour()) {
                        std::cout << "Colour selected successfully.\n";
                    }
                }
                else {    
                    std::cerr << "Error. No image has been loaded yet.\n";
                }
                break;
            case 'o':
                if(loaded) {
                    if(img.conversion2grey()) {
                        std::cout << "Image converted successfully.\n";
                    }
                }
                else {      
                    std::cerr << "Error. No image has been loaded yet.\n";
                }
                break;
            case 'n':
                if(loaded) {
                    img.negative();
                    std::cout << "Negative filter added successfully.\n";
                }
                else {      
                    std::cerr << "Error. No image has been loaded yet.\n";
                }
                break;
            case 't':
                if(loaded) {
                    std::cout << "Enter threshold value(0; 1): ";
                    std::cin >> param_val;
                    if(isDouble(param_val)) {
                        threshold = std::atof(param_val.c_str());
                        if(threshold >= 0 && threshold <= 1) {
                            img.thresholding(threshold);
                            std::cout << "Thresholding filter added successfully.\n";
                        }
                        else {
                            std::cerr << "Improper value of threshold.\n";
                        }
                    }
                }
                else {      
                    std::cerr << "Error. No image has been loaded yet.\n";
                }
                break;
            case 'b':
                if(loaded) {
                    std::cout << "Enter threshold value(0; 1): ";
                    std::cin >> param_val;
                    if(isDouble(param_val)) {
                        threshold = std::atof(param_val.c_str()); 
                        if(threshold >= 0 && threshold <= 1) {
                            img.halfThresholdingBlack(threshold);
                            std::cout << "Half-thresholding of black filter added successfully.\n";
                        }
                        else {
                            std::cerr << "Improper value of threshold.\n";
                        }
                    }
                }
                else {      
                    std::cerr << "Error. No image has been loaded yet.\n";
                }
                break;
            case 'w':
                if(loaded) {
                    std::cout << "Enter threshold value(0; 1): ";
                    std::cin >> param_val;
                    if(isDouble(param_val)) {
                        threshold = std::atof(param_val.c_str());
                        if(threshold >= 0 && threshold <= 1) {
                            img.halfThresholdingWhite(threshold);
                            std::cout << "Half-thresholding of white filter added successfully.\n";
                        }
                        else {
                            std::cerr << "Improper value of threshold.\n";
                        }
                    }
                }
                else {      
                    std::cerr << "Error. No image has been loaded yet.\n";
                }
                break;
            case 'g':
                if(loaded) {
                    std::cout << "Enter gamma parameter value: ";
                    std::cin >> param_val;
                    if(isDouble(param_val)) {
                        gamma = std::atof(param_val.c_str());
                        if(gamma > 0) {
                            img.gammaCorrection(gamma);
                            std::cout << "Gamma correction filter added successfully.\n";
                        }
                        else {
                            std::cerr << "Improper value of gamma parameter.\n";
                        }
                    }
                }
                else {      
                    std::cerr << "Error. No image has been loaded yet.\n";
                }
                break;
            case 'a':
                if(loaded) {
                    std::cout << "Enter level adjustment value(0; 0.5): ";
                    std::cin >> param_val;
                    if(isDouble(param_val)) {
                        level = std::atof(param_val.c_str());
                        if(level > 0 && level < 0.5) {
                            img.levelAdjustment(level);
                            std::cout << "Level adjustment filter added successfully.\n";
                        }
                        else {
                            std::cerr << "Improper value of level.\n";
                        }
                    }
                }
                else {      
                    std::cerr << "Error. No image has been loaded yet.\n";
                }
                break;
            case 'k':
                if(loaded) {
                    img.contouring();
                    std::cout << "Contouring filter added successfully.\n";
                }
                else {      
                    std::cerr << "Error. No image has been loaded yet.\n";
                }
                break;
            case 'x':
                if(loaded) {
                    std::cout << "Enter blurring radius value: ";
                    std::cin >> param_val;
                    if(isInteger(param_val)) {
                        radius = std::atoi(param_val.c_str());
                        if(radius > 0) {
                            img.horizontalBlurring(radius);
                            std::cout << "Horizontal blurring filter added successfully.\n";
                        }
                        else {
                            std::cerr << "Improper value of radius.\n";
                        }
                    }
                }
                else {      
                    std::cerr << "Error. No image has been loaded yet.\n";
                }
                break;
            case 'y':
                if(loaded) {
                    std::cout << "Enter blurring radius value: ";
                    std::cin >> param_val;
                    if(isInteger(param_val)) {
                        radius = std::atoi(param_val.c_str());
                        if(radius > 0) {
                            img.verticalBlurring(radius);
                            std::cout << "Vertical blurring filter added successfully.\n";
                        }
                        else {
                            std::cerr << "Improper value of radius.\n";
                        }
                    }
                }
                else {      
                    std::cerr << "Error. No image has been loaded yet.\n";
                }
                break;
            case 'f':
                if(loaded) {
                    std::cout << "Enter blurring radius value: ";
                    std::cin >> param_val;
                    if(isInteger(param_val)) {
                        radius = std::atoi(param_val.c_str());
                        if(radius > 0) {
                            img.fullBlurring(radius);
                            std::cout << "Full blurring filter added successfully.\n";
                        }
                        else {
                            std::cerr << "Improper value of radius.\n";
                        }
                    }
                }
                else {      
                    std::cerr << "Error. No image has been loaded yet.\n";
                }
                break;
            case 'h':
                if(loaded) {
                    img.histogramStretching();
                    std::cout << "Histogram stretching filter added successfully.\n";
                }
                else {      
                    std::cerr << "Error. No image has been loaded yet.\n";
                }
                break;
            case 'q':
                // program ends
                break;
            default:        // user's input doesnt match any of the options in user menu
                std::cin.clear();
                std::cerr << "Error. Your selection does not match any of the available options.\n";
                break;
            }
        }
        else {              // user's input is too long - exactly one character is acceptable
            std::cin.clear();
            std::cerr << "Error. Your selection does not match any of the available options.\n";
        }
    }
    return 0;
}
