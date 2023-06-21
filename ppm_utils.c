#include "ppm_utils.h"
#include <assert.h>

void openInputFiles(char* name, FILE* input[]) {
    int num_files = strcmp(name, "average") == 0 ? TEN : NINE;
    char filename[20];
    for (int i = 0; i < num_files; i++) {
        sprintf(filename, "%s_%03d.ppm", name, i + 1);
        input[i] = fopen(filename, "r");
        if (input[i] == NULL) {
            printf("Error opening file %s\n", filename);
            exit(EXIT_FAILURE);
        }
    }
}

image_t* removeNoiseAverage(image_t* img[]) {
    int height = img[0]->header.HEIGHT;
    int width = img[0]->header.WIDTH;

    image_t* output = allocateMemory(&img[0]->header);
    
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int sumR = 0, sumG = 0, sumB = 0;
            for (int k = 0; k < TEN; k++) {
                sumR += img[k]->pixels[i][j].R;
                sumG += img[k]->pixels[i][j].G;
                sumB += img[k]->pixels[i][j].B;
            }
            output->pixels[i][j].R = sumR / TEN;
            output->pixels[i][j].G = sumG / TEN;
            output->pixels[i][j].B = sumB / TEN;
        }
    }
    return output;
}

image_t* removeNoiseMedian(image_t* img[]) {
    int height = img[0]->header.HEIGHT;
    int width = img[0]->header.WIDTH;

    image_t* output = allocateMemory(&img[0]->header);
    unsigned int R[NINE], G[NINE], B[NINE];

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            for (int k = 0; k < NINE; k++) {
                R[k] = img[k]->pixels[i][j].R;
                G[k] = img[k]->pixels[i][j].G;
                B[k] = img[k]->pixels[i][j].B;
            }
            sort(R, NINE);
            sort(G, NINE);
            sort(B, NINE);
            output->pixels[i][j].R = R[NINE / 2];
            output->pixels[i][j].G = G[NINE / 2];
            output->pixels[i][j].B = B[NINE / 2];
        }
    }
    return output;
}

void sort(unsigned int* arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}

void swap(unsigned int* a, unsigned int* b) {
    unsigned int temp = *a;
    *a = *b;
    *b = temp;
}

image_t* read_ppm(FILE* image_file) {
    header_t header = read_header(image_file);
    image_t* img = allocateMemory(&header);
    for (int i = 0; i < header.HEIGHT; i++) {
        for (int j = 0; j < header.WIDTH; j++) {
            img->pixels[i][j].R = fgetc(image_file);
            img->pixels[i][j].G = fgetc(image_file);
            img->pixels[i][j].B = fgetc(image_file);
        }
    }
    return img;
}

header_t read_header(FILE* image_file) {
    header_t header;
    fscanf(image_file, "%2s", header.MAGIC_NUMBER);
    fscanf(image_file, "%d %d %d", &header.WIDTH, &header.HEIGHT, &header.MAX_VAL);

    // Consume newline character
    fgetc(image_file);

    return header;
}

void write_p6(FILE* out_file, image_t* image) {
    write_header(out_file, image->header);
    for (int i = 0; i < image->header.HEIGHT; i++) {
        for (int j = 0; j < image->header.WIDTH; j++) {
            fputc(image->pixels[i][j].R, out_file);
            fputc(image->pixels[i][j].G, out_file);
            fputc(image->pixels[i][j].B, out_file);
        }
    }
}

void write_header(FILE* out_file, header_t header) {
    fprintf(out_file, "%s\n%d %d\n%d\n", header.MAGIC_NUMBER, header.WIDTH, header.HEIGHT, header.MAX_VAL);
}

image_t* allocateMemory(header_t* header) {
    image_t* img = (image_t*)malloc(sizeof(image_t));
    img->header = *header;
    img->pixels = (pixel_t**)malloc(header->HEIGHT * sizeof(pixel_t*));
    for (int i = 0; i < header->HEIGHT; i++) {
        img->pixels[i] = (pixel_t*)malloc(header->WIDTH * sizeof(pixel_t));
    }
    return img;
}

void freeImage(image_t* img) {
    for (int i = 0; i < img->header.HEIGHT; i++) {
        free(img->pixels[i]);
    }
    free(img->pixels);
    free(img);
}

void closeFiles(FILE* files[], int n) {
    for (int i = 0; i < n; i++) {
        fclose(files[i]);
    }
}