# PPM-Image-Editor

![Image](https://github.com/Michael-Elrod-dev/PPM-Image-Editor/blob/main/PpmEdit.png)

This project consists of a program that reads multiple PPM (Portable Pixmap) image files and either removes noise from the images or edits out obstuctions. The noise removal is done using an average filtering method while the obstruction removal uses a median.

## Usage
Compile the program using the GCC compiler:

```
gcc -o ppmNoiseRemoval main.c ppm_utils.c
```
Run the program with the input PPM file and the desired output PPM file as command-line arguments:
```
./ppmNoiseRemoval <average|median> <output ppm file>
```
## Program Structure

- main.c: This file contains the main function that opens the input files, processes the images, and writes the result to the output file.
- ppm_utils.c: This file contains utility functions for opening input files, removing noise from images, reading and writing PPM files, and managing memory.

## Functions

- `void openInputFiles(char* argv, FILE* inPut[])`: Opens the input image files.
- `image_t* removeNoiseAverage(image_t* img[])`: Removes noise from images using averaging.
- `image_t* removeNoiseMedian(image_t* img[])`: Removes noise from images using median filtering.
- `pixel_t readPixel(FILE* in, image_t* img)`: Reads a pixel from a PPM file.
- `header_t read_header(FILE* image_file)`: Reads the header of a PPM file.
- `image_t* read_ppm(FILE* image_file)`: Reads a PPM file into an `image_t`.
- `void write_header(FILE* out_file, header_t header)`: Writes the header of a PPM file.
- `void write_p6(FILE* out_file, image_t* image)`: Writes an `image_t` to a PPM file.
- `void sort(unsigned int* arr, int n)`: Sorts an array of unsigned integers.
- `void swap(unsigned int* a, unsigned int* b)`: Swaps two unsigned integers.
- `image_t* allocateMemory(header_t*)`: Allocates memory for an `image_t`.
- `void closeFiles(FILE* files[], int num_files)`: Closes all open file pointers.
- `void freeImage(image_t* img)`: Frees memory allocated for an `image_t`.
