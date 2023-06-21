#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ppm_utils.h"

int main(int argc, char* argv[]) {
    // Check for correct arguments
    if (argc != 3) {
        printf("Usage: %s <average|median> <output_file>\n", argv[0]);
        exit(1);
    }

    // Check directory for input files
    const int num_files = strcmp(argv[1], "average") == 0 ? TEN : NINE;
    FILE* input_files[num_files];
    openInputFiles(argv[1], input_files);

    // Read input files
    image_t* images[num_files];
    for (int i = 0; i < num_files; i++) {
        images[i] = read_ppm(input_files[i]);
    }
    closeFiles(input_files, num_files);

    // Open ouput file
    FILE* output_file = fopen(argv[2], "wb");
    if (output_file == NULL) {
        perror("Error opening output file");
        exit(1);
    }

    // Create new image
    image_t* result;
    if (strcmp(argv[1], "average") == 0) {
        result = removeNoiseAverage(images);
    } else {
        result = removeNoiseMedian(images);
    }

    // Write to output and close
    write_p6(output_file, result);
    fclose(output_file);

    // Free images
    for (int i = 0; i < num_files; i++) {
        freeImage(images[i]);
    }
    freeImage(result);

    return 0;
}
