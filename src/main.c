#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

#include "../include/unoptimized_algo.h"
#include "../include/naive.h"

uint8_t *read_image(char *filepath, size_t dimensions) {
  FILE *fp = fopen(filepath, "r");
  if(fp == NULL) {
    perror("Error: unable to open file");
    exit(EXIT_FAILURE);
  }

  uint8_t *buffer = malloc(sizeof(uint8_t) * dimensions);

  // Save data to memory
  fread(buffer, sizeof(uint8_t), dimensions, fp);

  fclose(fp);

  return buffer;
}

void print_matrix(int matrix[8][8], int width, int height) {
  for(int i = 0; i < width; i++) {
    for(int j = 0; j < height; j++) {
      printf("%4d ", matrix[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}

void dct(uint8_t *image, int width, int height) {
  int width_offset = width / 8;
  int height_offset = height / 8;
  for (int i = 0; i < height_offset; i++) {
    for (int j = 0; j < width_offset; j++) {
      uint8_t block[8][8];
      int output[8][8];

      for (int k = 0; k < 8; k++) {
        for (int l = 0; l < 8; l++) {
          int index = width*((i*8) + k) + ((j*8) + l);
          block[k][l] = image[index];
        }
      }

      printf("Block with top-left coordinates: (%d,%d)\n", j*8, i*8);

      // print_matrix(block, 8, 8);

      naive(block, output);
      print_matrix(output, 8, 8);
    } 
  }

  // uint8_t input[8][8];
  // int output[8][8];
  // for(int i = 0; i < 8; i++) {
  //   for(int j = 0; j < 8; j++) {
  //     input[i][j] = image[i*8+j];
  //     output[i][j] = 0;
  //   }
  // }

  // naive(input, output);
  // print_matrix(output, 8, 8);

  // for(int i = 0; i < 8; i++) {
  //   for(int j = 0; j < 8; j++) {
  //     output[i][j] = 0;
  //   }
  // }

  // unoptimized_algo(input, output);
  // print_matrix(output, 8, 8);
}


int main(int argc, char *argv[]) {
  if (argc != 4) {
    printf("Error: invalid number of arguments (example: ./main ./test/64_byte_input 8 8)\n");
    return EXIT_FAILURE;
  }
  char *input_file = argv[1];
  int width = atoi(argv[2]);
  int height = atoi(argv[3]);

  if (width % 8 != 0 || height % 8 != 0) {
    printf("Error: the width and height of the image must each be divisible by 8\n");
    return EXIT_FAILURE;
  }
  uint8_t *image = read_image(input_file, width*height);

  dct(image, width, height);

  return EXIT_SUCCESS;
}