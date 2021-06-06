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


#ifndef IMAGE_HH
#define IMAGE_HH


#include <iostream>
#include <string>


/**
 * @brief Class containing data of image and processing methods that can be used on images
 */
class Image {
    private:
        /**
         * @brief Width of image(horizontally)
         */
        int width;
        /**
         * @brief Height of image(vertically)
         */
        int height;
        /**
         * @brief Precision of each pixel, grey scale
         */    
        int depth;
        /**
         * @brief Image type(PGM or PPM), 1 stands for PGM, 3 stands for PPM
         */          
        int img_type;
        /**
         * @brief Which colour will be processed - 0, 1, 2 stands for red(or grey for PGM), green, blue
         */       
        int colour;
        /**
         * @brief Pointer to dynamically allocated memory for pixels - pixels[colour][height][width]
         */         
        int ***pixels = nullptr; 
    
    public:
        /**
         * @brief Nonparametric constructor
         */  
        Image() {};
        /**
         * @brief Copy constructor
         * @param img image object
         */ 
        Image(const Image & img);
        /**
         * @brief Destructor that deletes pointer with allocated memory for pixels
         */
        ~Image();
        /**
         * @brief Load image from a text file
         * @param img_title file name from which image is loaded
         * @return Boolean value - whether the operation was successful or not
         */
        bool load(std::string img_title); 
        /**
         * @brief Save current state of image to a text file
         * @param img_title file name to which image is saved
         * @return Boolean value - whether the operation was successful or not 
         */   
        bool save(std::string img_title);  
        /**
         * @brief Display current state of image on screen
         */  
        void display();
        /**
         * @brief Ask user to select new colour that will be processed
         * @return Boolean value - whether the operation was successful or not
         */                   
        bool selectColour();
        /**
         * @brief Convert colorful image to grey image(PPM to PGM convertion)
         * @return Boolean value - whether the operation was successful or not
         */
        bool conversion2grey(); 
        /**
         * @brief Add negative filter to an image
         */           
        void negative();   
        /**
         * @brief Add thresholding filter to an image
         * @param threshold threshold value in range(0; 1) for thresholding
         */                  
        void thresholding(double threshold);
        /**
         * @brief Add half-thresholding of black filter to an image
         * @param threshold threshold value in range(0; 1) for half-thresholding of black
         */
        void halfThresholdingBlack(double threshold);
        /**
         * @brief Add half-thresholding of white filter to an image
         * @param threshold threshold value in range(0; 1) for half-thresholding of white
         */
        void halfThresholdingWhite(double threshold);
        /**
         * @brief Add gamma correction to an image
         * @param gamma value of gamma parameter
         */ 
        void gammaCorrection(double gamma);
        /**
         * @brief Add level adjustment filter to an image
         * @param level level value in range(0; 0.5) for level adjustment
         */ 
        void levelAdjustment(double level);
        /**
         * @brief Add contouring filter to an image
         */ 
        void contouring();
        /**
         * @brief Add horizontal blurring filter to an image
         * @param radius radius of horizontal blurring
         */ 
        void horizontalBlurring(int radius);
        /**
         * @brief Add nvertical blurring filter to an image
         * @param radius radius of vertical blurring
         */ 
        void verticalBlurring(int radius);
        /**
         * @brief Add both horizontal and vertical blurring to an image
         * @param radius radius of full blurring
         */ 
        void fullBlurring(int radius);
        /**
         * @brief Add histogram stretching filter to an image
         */ 
        void histogramStretching();
};


#endif
