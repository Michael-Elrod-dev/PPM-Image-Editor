#ifndef PPM_UTILS
#define PPM_UTILS
#define TEN 10
#define NINE 9
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>

typedef struct header {
  char MAGIC_NUMBER[3];
  int HEIGHT, WIDTH, MAX_VAL;
} header_t;

typedef struct pixel {
  unsigned char R, G, B;
} pixel_t;

// PPM Image representation
typedef struct image {
  header_t header;
  pixel_t** pixels;
} image_t;


/*This function will open the files for the images. 
 *There will be 10 noisy images. The pesky tourist will have 9 images.  
 *The file names will be stored in an array of File Pointers.
 *Pass in the array of file pointers. THe command line argument argv[1] will 
 *represent type of file names needed to be created. (average or median)
 *This function will use sprintf to concat argv[1] with the remainder of the
 *file name ex. If "average" is passed in 1st file name will be average_001.ppm
 *the second average_002.ppm, etc. For you C++ lovers - This concept is similar 
 *to stringstreams. However, you are NOT USING stringstreams. You will use 
 *sprintf.
 */
void openInputFiles(char* argv, FILE* inPut[]);

/*This function will remove the noise from the images from space. 
  *This involves taking an average of each channel of each pixel in all 
  *ten images. This becomes the pixel value for the output file. 
  *
  *Store the new pixel values in a local image_t* (don't forget to allocate 
  *the memory)  
  **/
image_t* removeNoiseAverage(image_t* img[]);

/*This function will remove the pesky Tourist from the 9 images provided
  *You will need to allocate the memory for the output file
  *For each pixel in each of the 9 images put the RGB values in an array.
  *one for R, one for G, one for B.
  *Sort the array.
  *The value in the middle (4th element) should then be stored in the output
  *memory created for the output file.
  *return the output image*/
image_t* removeNoiseMedian(image_t* image[]);

pixel_t readPixel(FILE* in, image_t* img);
/*This function reads in the header setting the values in a temporary header
 *then returns that header. */
header_t read_header(FILE* image_file);
/*
 *This function calls the function to read the header. Using that information
 *it calls allocateMemory to allocate the memory for the pixels. Then this 
 *function reads the pixels
 */
image_t* read_ppm(FILE* image_file);
void write_header(FILE* out_file, header_t header);
/*This function writes a ppm image out.  You will need to create a temporary 
 *header_t and set it equal to the images header that is passed to the function. 
 *Calls the write_header function  and then prints the pixels to the output
 *file.*/
void write_p6(FILE* out_file, image_t* image);
/*You can choose the flavor of sorting algorithem you want */
void sort(unsigned int* arr, int n);
/*For me swap was used in conjunction with the sort algorithm*/
void swap(unsigned int* a,unsigned int* b);

image_t* allocateMemory(header_t*);

/*You will need to add the functions needed to clean up (free all allocated 
memroy) and close all file pointers.*/
void closeFiles(FILE* files[], int num_files);
void freeImage(image_t* img);


#endif
