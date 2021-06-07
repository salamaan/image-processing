# image-processing
Image processing console app for images saved in PGM and PPM format.

## Setup
Clone this repository:
```
$ git clone https://github.com/salamaan/image-processing.git
```

Create directory for object files:
```
$ make build
```

Then compile entire program:
```
$ make
```
This command will create an ``` run ``` executable.

## Running the program
To run this app just use this command:
```
$ ./run
```
Then you have user menu:
```
User menu - image processing
l - load an image
s - save current state of the image
d - display current state of the image
c - select new colour that will be processed(only for colorful images)
o - convert PPM to PGM(only for colorful images)
n - add negative filter to an image
t - add threshold filter to an image
b - add half-threshold of black filter to an image
w - add half-threshold of white filter to an image
g - add gamma correction filter to an image
a - add level adjustment liter to an image
k - add contouring filter to an image
x - add horizontal blurring filter to an image
y - add vertical blurring filter to an image
f - add full blurring filter to an image
h - add histogram stretching filter to an image
q - quit the program

Your selection:
```
## Tips
* First of all you have to load an image. You can't use any of the processing methods before loading an image. 
* You can only load images from ``` pic ``` folder. You don't have to enter entire path to an image. Just enter its title e.g. ``` kubus3.ppm ```.
* Some of the processing methods are available only for colorful images(PPM).
* Some of the processing methods require entering a parameter value by a user. Entering value that is not a number in specific range will result in error.
* Every improper user input will result in error.
* You don't have to save an image to display changes.
* If you want to save an image just enter its new title without adding extention. App will automatically recognise image type and add proper extention.
* By default red is the colour that will be processed after loading colorful image. You can select new colour using 'c' method.
* You can add as much filters as you want, there are no limitations.

## Documentation
The program is fully documented in English.

## License 
MIT License.

## Author
Marcin Salamandra.
