#ifndef LOAD_MNIST_H
#define LOAD_MNIST_H


#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>


#define IMAGE_HEIGHT 28
#define IMAGE_WIDTH 28
#define IMAGE_SIZE 784
#define TRAIN_IMAGE_COUNT 60000
#define TEST_IMAGE_COUNT 10000

#define METADATA_IMAGES 4 
#define METADATA_LABELS 2


typedef struct MNIST_Image {
    unsigned char pixel_values[IMAGE_HEIGHT][IMAGE_WIDTH];
    unsigned char label;
} MNIST_IMAGE;


void read_image_file(char *file_path, MNIST_IMAGE image_array[], int image_metadata[], int image_count);

void read_label_file(char *file_path, MNIST_IMAGE image_array[], int label_metadata[], int image_count);

void read_mnist_to_struct(char *image_path, char *label_path, MNIST_IMAGE image_array[], int image_metadata[], int label_metadata[], int image_count);


#endif