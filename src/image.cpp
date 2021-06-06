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
#include <ios>
#include <cmath>
#include <fstream>


#define FAIL false;
#define SUCCESS true;


Image::Image(const Image & img) {
    this->width = img.width;
    this->height = img.height;
    this->depth = img.depth;
    this->img_type = img.img_type;
    this->colour = img.colour;
    this->pixels = img.pixels;
}


Image::~Image() {
    if(this->pixels) {
        for(int c = 0; c < this->img_type; ++c) {
            for(int i = 0; i < this->height; ++i) {
                delete [] this->pixels[c][i];
            }
            delete [] this->pixels[c];
        }
        delete [] this->pixels;
    }
}


bool Image::load(std::string img_title) {
    std::string magic_number;
    std::string comment;
    std::ifstream source;
    std::string file_name;

    file_name.append("pic/");
    file_name.append(img_title);

    source.open(file_name);
    if(!source.good()) {
        std::cerr << "Error. Could not load an image.\n";
        return FAIL;
    }

    // check whether input image is saved in pgm or ppm format or not
    getline(source, magic_number);
    if(magic_number[0] != 'P' || (magic_number[1] != '2' && magic_number[1] != '3')) {
        std::cerr << "Error. This is neither PGM nor PPM image.\n";
        return FAIL;
    }

    // load "magic number"
    if(magic_number[1] == '2') {
        this->img_type = 1;
    }
    if(magic_number[1] == '3') {
        this->img_type = 3;
    }

    this->colour = 0;

    // ignore comments
    int len = source.tellg();
    std::getline(source, comment);
    if(comment[0] == '#') {
        while(comment[0] == '#') {
            len = source.tellg();
            std::getline(source, comment);
        }
        // return to position before "getline".
        source.seekg(len, std::ios_base::beg);
    }
    else {
        // return to position before "getline".
        source.seekg(len, std::ios_base::beg);
    }

    // load image width, height and depth
    source >> this->width;
    source >> this->height;
    source >> this->depth;

    // allocate memory space
    this->pixels = new int **[this->img_type];
    for(int c = 0; c < this->img_type; ++c) {
        pixels[c] = new int *[this->height];
        for(int i = 0; i < this->height; ++i) {
            pixels[c][i] = new int[this->width];
        }
    }

    // load pixels for every colour
    for(int i = 0; i < this->height; ++i) {
        for(int j = 0; j < this->width; ++j) {
            for(int c = 0; c < this->img_type; ++c) {
                source >> pixels[c][i][j];
            }
        }
    }
    source.close();

    return SUCCESS;
}


bool Image::save(std::string img_title) {
    std::string magic_num;
    std::ofstream file;
    std::string file_name;

    file_name.append("pic/");
    file_name.append(img_title);

    if(this->img_type == 1) {
        magic_num = "P2";
        file_name.append(".pgm");
    }

    if(this->img_type == 3) {
        magic_num = "P3";
        file_name.append(".ppm");
    }

    file.open(file_name);
    if(!file.good()) {
        std::cerr << "Error. Could not save an image.\n";
        return FAIL;
    }

    // write "magic number", width, height and depth
    file << magic_num << "\n";
    file << this->width << " " << this->height << " " << this->depth << "\n";

    // write pixels of every colour
    for(int i = 0; i < this->height; ++i) {
        for(int j = 0; j < this->width; ++j) {
            for(int c = 0; c < this->img_type; ++c) {
                file << this->pixels[c][i][j] << " ";
            }
        }
        file << "\n";
    }
    file.close();

    return SUCCESS;
}


void Image::display() {
    // save changes to temporary file, display an image and then remove temporary file
    std::string tmp = "temporary";
    std::string display_order = "";
    std::string remove_order = "";

    this->save(tmp); 
    if(this->img_type == 1) {
        tmp.append(".pgm");
    }
    if(this->img_type == 3) {
        tmp.append(".ppm");
    }  

    display_order.append("display pic/");
    display_order.append(tmp);
    system(display_order.c_str());

    remove_order.append("rm pic/");
    remove_order.append(tmp);
    system(remove_order.c_str());
}


bool Image::selectColour() {
    std::string selection;   
    bool selected = false;     

    if(this->img_type == 3) {     
        while(!selected) {
            std::cout << "\nSelect a colour to be processed:\n";
            std::cout << "r - red\n" << "g - green\n" << "b - blue\n";
            std::cout << "\nYour selection: ";
            std::cin >> selection;
            std::cout << "\n";

            system("clear");

            if(selection.length() == 1) {
                switch(selection[0]) {
                case 'r':
                    this->colour = 0;
                    std::cout << "You have selected red.\n";
                    selected = true;
                    break;
                case 'g':
                    this->colour= 1;
                    std::cout << "You have selected green.\n";
                    selected = true;
                    break;
                case 'b':
                    this->colour = 2;
                    std::cout << "You have selected blue.\n";
                    selected = true;
                    break;
                default:    // for wrong input
                    std::cin.clear();
                    std::cerr << "Error. Your selection does not match any of the available options.\n";
                    break;
                }
            }
            else {      // for too long input
                std::cin.clear();
                std::cerr << "Error. Your selection does not match any of the available options.\n";
            }
        }
    }
    else {      // for pgm images
        std::cin.clear();
        std::cerr << "Error. Current image is not colorful.\n";
        return FAIL;
    }
    return SUCCESS;
}


bool Image::conversion2grey() {
    if(this->img_type == 3) {
        int ***tmp;
        tmp = new int **[1];
        tmp[0] = new int *[this->height];
        for(int i = 0; i < this->height; ++i) {
            tmp[0][i] = new int[this->width];
        }
        for(int i = 0; i < this->height; ++i) {
            for(int j = 0; j < this->width; ++j) {
                int new_pixel = 0;
                for(int c = 0; c < this->img_type; ++c) {
                    new_pixel += this->pixels[c][i][j];
                }
                tmp[0][i][j] = new_pixel / 3;
            }
        }

        for(int c = 0; c < this->img_type; ++c) {
            for(int i = 0; i < this->height; ++i) {
                delete [] this->pixels[c][i];
            }
            delete [] this->pixels[c];
        }
        delete [] this->pixels;

        this->img_type = 1;
        this->colour = 0;
        this->pixels = tmp;
    }
    else {
        std::cerr << "Error. Current image is not colorful.\n";
        return FAIL;
    }
    return SUCCESS;
}


void Image::negative() {
    for(int i = 0; i < this->height; ++i) {
        for(int j = 0; j < this->width; ++j) {
            int current = this->pixels[this->colour][i][j];
            this->pixels[this->colour][i][j] = this->depth - current;
        }
    }
}


void Image::thresholding(double threshold) {
    int limit = threshold * this->depth; 

    for(int i = 0; i < this->height; ++i) {
        for(int j = 0; j < this->width; ++j) {
            int current = this->pixels[this->colour][i][j];
            this->pixels[this->colour][i][j] = (current <= limit ? 0 : this->depth);
        }
    }
}


void Image::halfThresholdingBlack(double threshold) {
    int limit = threshold * this->depth; 

    for(int i = 0; i < this->height; ++i) {
        for(int j = 0; j < this->width; ++j) {
            int current = this->pixels[this->colour][i][j];
            this->pixels[this->colour][i][j] = (current <= limit ? 0 : current);
        }
    }
}


void Image::halfThresholdingWhite(double threshold) {
    int limit = threshold * this->depth; 

    for(int i = 0; i < this->height; ++i) {
        for(int j = 0; j < this->width; ++j) {
            int current = this->pixels[this->colour][i][j];
            this->pixels[this->colour][i][j] = (current <= limit ? current : this->depth);
        }
    }
}


void Image::gammaCorrection(double gamma) {
    for(int i = 0; i < this->height; ++i) {
        for(int j = 0; j < this->width; ++j) {
            int current = this->pixels[this->colour][i][j];
            this->pixels[this->colour][i][j] = int(pow((double(current) / double(this->depth)), (1.0 / gamma)) * this->depth);
        }
     }
}


void Image::levelAdjustment(double level) {
    int black = this->depth * level;
    int white = this->depth * (1 - level); 

    for(int i = 0; i < this->height; ++i) {
        for(int j = 0; j < this->width; ++j) {
            int current = this->pixels[this->colour][i][j];
            if(current <= black) {
                this->pixels[this->colour][i][j] = 0;
            }
            else if(current < white) {
                this->pixels[this->colour][i][j] = int(this->depth / (white - black) * (current - black));
            }
            else {
                this->pixels[this->colour][i][j] = this->depth;
            }
        }
    }
}


void Image::contouring() {
    for(int i = 0; i < this->height - 1; ++i) {
        for(int j = 0; j < this->width - 1; ++j) {
            int current = this->pixels[this->colour][i][j];
            int val1 = abs(this->pixels[this->colour][i+1][j] - current);
            int val2 = abs(this->pixels[this->colour][i][j+1] - current);
            int val = val1 + val2;
            this->pixels[this->colour][i][j] = (val <= this->depth ? val : this->depth);
        }
    }
}


void Image::horizontalBlurring(int radius) {
    int **tmp;
    tmp = new int *[this->height];
    for(int i = 0; i < this->height; ++i) {
        tmp[i] = new int [this->width];
        for(int j = 0; j < this->width; ++j) {
            tmp[i][j] = this->pixels[this->colour][i][j];
        }
    }

    for(int i = 0; i < this->height - 1; ++i) {
        for(int j = 0; j < this->width - 1; ++j) {
            int left = 0;
            int right = 0;
            int counter = 0;
            for(int r = 1; r < radius + 1; ++r) {
                if(j - r >= 0) {
                    left += this->pixels[this->colour][i][j-r];
                    counter++;
                }
                if(j + r <= this->width - 1) {
                    right += this->pixels[this->colour][i][j+r];
                    counter++;
                }
            }
            tmp[i][j] += left + right;
            tmp[i][j] /= counter + 1;
            if(tmp[i][j] > this->depth) {
                tmp[i][j] = this->depth;
            }
        }
    }
    this->pixels[this->colour] = tmp;
}


void Image::verticalBlurring(int radius) {
    int **tmp;
    tmp = new int *[this->height];
    for(int i = 0; i < this->height; ++i) {
        tmp[i] = new int [this->width];
        for(int j = 0; j < this->width; ++j) {
            tmp[i][j] = this->pixels[this->colour][i][j];
        }
    }
        
    for(int j = 0; j < this->width - 1; ++j) {
        for(int i = 0; i < this->height - 1; ++i) {
            int up = 0;
            int down = 0;
            int counter = 0;
            for(int r = 1; r < radius + 1; ++r) {
                if(i - r >= 0) {
                    up += this->pixels[this->colour][i-r][j];
                    counter++;
                }
                if(i + r <= this->height - 1) {
                    down += this->pixels[this->colour][i+r][j];
                    counter++;
                }
            }
            tmp[i][j] += up + down;
            tmp[i][j] /= counter + 1;
            if(tmp[i][j] > this->depth) {
                tmp[i][j] = this->depth;
            }
        }
    }
    this->pixels[this->colour] = tmp;
}


void Image::fullBlurring(int radius) {
    int **tmp;
    tmp = new int *[this->height];
    for(int i = 0; i < this->height; ++i) {
        tmp[i] = new int [this->width];
        for(int j = 0; j < this->width; ++j) {
            tmp[i][j] = this->pixels[this->colour][i][j];
        }
    }

    for(int i = 0; i < this->height - 1; ++i) {
        for(int j = 0; j < this->width - 1; ++j) {
            int up = 0;
            int down = 0;
            int left = 0;
            int right = 0;
            int counter = 0;
            for(int r = 1; r < radius + 1; ++r) {
                if(i - r >= 0) {
                    up += this->pixels[this->colour][i-r][j];
                    counter++;
                }
                if(i + r <= this->height - 1) {
                    down += this->pixels[this->colour][i+r][j];
                    counter++;
                }
                if(j - r >= 0) {
                    left += this->pixels[this->colour][i][j-r];
                    counter++;
                }
                if(j + r <= this->width - 1) {
                    right += this->pixels[this->colour][i][j+r];
                    counter++;
                }
            }
            tmp[i][j] += up + down + left + right;
            tmp[i][j] /= counter + 1;
            if(tmp[i][j] > this->depth) {
                tmp[i][j] = this->depth;
            }
        }
    }
    this->pixels[this->colour] = tmp;
}


void Image::histogramStretching() {
    int min = this->depth;
    int max = 0;

    for(int i = 0; i < this->height; ++i) {
        for(int j = 0; j < this->width; ++j) {
            int current = this->pixels[this->colour][i][j];
            if(current > max) {
                max = current;
            }
            if(current < min) {
                min = current;
            }
        }
    }

    for(int i = 0; i < this->height; ++i) {
        for(int j = 0; j < this->width; ++j) {
            int current = this->pixels[this->colour][i][j];
            this->pixels[this->colour][i][j] = int((current - min) * this->depth / (max - min));
            if(this->pixels[this->colour][i][j] > this->depth) {
                this->pixels[this->colour][i][j] = this->depth;
            }
        }
    }
}
