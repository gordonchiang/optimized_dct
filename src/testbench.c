#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "../include/unoptimized.h"


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

int checkBlock(int output[8][8], int answer[8][8], int startX, int startY){
    int i, j;
    for(i = 0; i < 8; i++) {
        for(j = 0; j < 8; j++) {
            if(output[i][j] != answer[startX + i][startY + j]) {
                printf("%d %d\n", output[i][j], answer[startX + i][startY + j]);
                return EXIT_FAILURE;
            }
        }
    }
    return EXIT_SUCCESS;
}

int testcase(char *input_file, int answer[8][8], int width, int height) {
    uint8_t *image = read(input_file, width*height);
    int i, j, k, l;
    int width_offset = width / 8;
    int height_offset = height / 8;

    for (i = 0; i < height_offset; i++) {
        for (j = 0; j < width_offset; j++) {
            int block[8][8];
            int output[8][8];

            for (k = 0; k < 8; k++) {
                for (l = 0; l < 8; l++) {
                    int index = width*((i*8) + k) + ((j*8) + l);
                    block[k][l] = image[index];
                }
            }

            unoptimized(block, output); // change to what method will be the fully optimized algo
            if(checkBlock(output, answer, i*8, j*8) == 1) {
                return EXIT_FAILURE;
            }
        } 
    } 
    return EXIT_SUCCESS;  
}



int testbench() {
    int answer[8][8] = {
        {657, 8, -10, 31, -28, 16, -24, -22},
        {-107, -2, 4, -6, 6, -6, 2, 0},
        {109, 2, 4, -8, 14, -25, -5, 2},
        {13, 0, -9, 12, -15, 11, -4, -3},
        {-50, -36, 2, 0, 0, 0, 9, 0},
        {4, 8, 2, -10, 14, -13, 1, 6},
        {45, 40, -15, 26, -4, 19, -11, -6},
        {-10, -19, 4, 4, -11, 9, 1, -9},
    };

    if(testcase("./test/8x8_64_byte", answer, 8, 8) == 0) {
        printf("testcase 1: Success\n");
    } else {
        printf("testcase 1: Failure\n");
    }

    if(testcase("./test/8x8_64_byte", answer, 8, 8) == 0) {
        printf("testcase 2: Success\n");
    } else {
        printf("testcase 2: Failure\n");
    }

    if(testcase("./test/8x8_64_byte", answer, 8, 8) == 0) {
        printf("testcase 3: Success\n");
    } else {
        printf("testcase 3: Failure\n");
    }
    return EXIT_SUCCESS;
}