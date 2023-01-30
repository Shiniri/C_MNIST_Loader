
#include <stdio.h>

#include "load_mnist.h"


void read_image_file(char *file_path, MNIST_IMAGE image_array[], int image_metadata[], int image_count) {
    int image_file;
    //unsigned char pixel_values[image_count][IMAGE_SIZE];

    unsigned char *pixel_values[image_count];
    for (int i=0; i<image_count; ++i) {
        pixel_values[i] = (unsigned char*)malloc(IMAGE_SIZE*sizeof(unsigned char));
    }

    // read data from file into pixel_values array
    if ((image_file = open(file_path, O_RDONLY)) == -1) {
        fprintf(stderr, "couldn't open file");
        exit(-1);
    }

    read(image_file, image_metadata, METADATA_LABELS * sizeof(int));
    
    for (int i=0; i<image_count; i++) {
        read(image_file, pixel_values[i], IMAGE_SIZE * sizeof(unsigned char));   
    }

    close(image_file);

    // enter data into image struct
    for(int i=0; i<image_count; i++) {
        for (int j=0; j<IMAGE_HEIGHT; j++) {
            for(int k = 0; k<IMAGE_WIDTH; k++) {
                image_array[i].pixel_values[j][k] = (1.0 * pixel_values[i][j*k]);
            }
        }
    }

    free(pixel_values);
}


void read_label_file(char *file_path, MNIST_IMAGE image_array[], int label_metadata[], int image_count) {
    int label_file;
    unsigned char labels[TRAIN_IMAGE_COUNT];

    // read data from file into labels array
    if ((label_file = open(file_path, O_RDONLY)) == -1) {
        fprintf(stderr, "couldn't open file");
        exit(-1);
    }

    read(label_file, label_metadata, METADATA_LABELS*sizeof(int));

    for (int i=0; i<image_count; i++) {
        read(label_file, &labels[i], sizeof(unsigned char));
    }

    // enter data into image struct
    for (int i=0; i<image_count; i++) {
        image_array[i].label = labels[i];
    }
}


void read_mnist_to_struct(char *image_path, char *label_path, MNIST_IMAGE image_array[], int image_metadata[], int label_metadata[], int image_count) {
    read_image_file(image_path, image_array, image_metadata, image_count);
    read_label_file(label_path, image_array, label_metadata, image_count);
}
