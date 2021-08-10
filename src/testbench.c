#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "../include/naive.h"
#include "../include/neon.h"
 
uint8_t *read(char *filepath, size_t dimensions) {
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

int checkBlock(int output[8][8], int output2[8][8]){
  int i, j;
  for(i = 0; i < 8; i++) {
    for(j = 0; j < 8; j++) {
      if(output[i][j] > (output2[i][j] + 2) || output[i][j] < (output2[i][j] - 2)) {
        return EXIT_FAILURE;
      }
    }
  }
  return EXIT_SUCCESS;
}

void print_matrix1(int matrix[8][8], int width, int height) {
  int i, j;
  for (i = 0; i < width; i++) {
    for (j = 0; j < height; j++) {
      printf("%4d ", matrix[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}

int testcase(char *input_file, int width, int height) {
  uint8_t *image = read(input_file, width*height);
  int i, j, k, l;
  int width_offset = width / 8;
  int height_offset = height / 8;

  for (i = 0; i < height_offset; i++) {
    for (j = 0; j < width_offset; j++) {
      int block[8][8];
      int block2[8][8];
      int output[8][8];
      int output2[8][8];

      for (k = 0; k < 8; k++) {
        for (l = 0; l < 8; l++) {
          int index = width*((i*8) + k) + ((j*8) + l);
          block[k][l] = image[index];
          block2[k][l] = image[index];
        }
      }

      neon(block, output); // change to what method will be the fully optimized algo
      naive(block2, output2);

      if(checkBlock(output, output2) == 1) {
        return EXIT_FAILURE;
      }
    }
  } 
  return EXIT_SUCCESS;  
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Error: invalid number of arguments (example: ./main ./test/8x8_64_byte)\n");
    return EXIT_FAILURE;
  }
  
  char *input_file = argv[1]; // "./test/testimage.png",
  
  if(testcase(input_file, 320, 240) == 0) {
    printf("testcase Success\n");
  } else {
    printf("testcase Failure\n");
  }
  
  return EXIT_SUCCESS;
}
