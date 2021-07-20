#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define C1 32138
#define C2 30274
#define C3 27246
#define C4 23170
#define C5 18205
#define C6 12540
#define C7 6393

int unoptimized_algo(int input[8][8], int output[8][8]) {
  int x, y, i, j;
  for(y = 2; y != 0; y--) {
    for(x = 0; x < 8; x++) {
      int temp1, temp2, temp3, temp4;

      temp1 = input[0][x] + input[7][x];
      temp2 = input[1][x] + input[6][x];
      temp3 = input[2][x] + input[5][x];
      temp4 = input[3][x] + input[4][x];

      /*
      * 
      * int temp[4];
      * temp[0] = input[0][x] + input[7][x];
      * temp[1] = input[1][x] + input[6][x];
      * temp[2] = input[2][x] + input[5][x];
      * temp[3] = input[3][x] + input[4][x];
      *   
      * int arr1[4] = {C4, C4, C4, C4};
      * int arr2[4] = {C2, C6, -C6, -C2};
      * int arr3[4] = {C4, -C4, -C4, C4};
      * int arr4[4] = {C6, -C2, C2, -C6};
      * 
      * int16x4_t outpurMul1, outpurMul2, outpurMul3, outpurMul4, inputInitial, cArr1, cArr2, cArr3, cArr4;
      * 
      * inputIntial = vld1_s16(temp);
      * cArr1 = vld1_s16(arr1);
      * cArr2 = vld1_s16(arr2);
      * cArr3 = vld1_s16(arr3);
      * cArr4 = vld1_s16(arr4);
      * 
      * 
      * // This is C[x] * temp1, C[x] * temp2, C[x] * temp3, C[x] * temp4
      * outputMul1 = vmul_s16(cArr1, inputIntial);
      * outputMul2 = vmul_s16(cArr2, inputIntial);
      * outputMul3 = vmul_s16(cArr3, inputIntial);
      * outputMul4 = vmul_s16(cArr4, inputIntial);
      * 
      * 
      * 
      * // This is the summation of each of the mulitplcation Steps I honestly don't know if this actually saves any time at all
      * int16x4_t addedDRegisters;
      * int32x2_t pairwiseAddedOnce;
      * int64x1_t pairwiseAddedTwice;
      * 
      * addedDRegisters = vadd_s16(vget_low_s16(outputMul1), vget_high_s16(outputMul1));
      * pairwiseAddedOnce = vpaddl_s16(addedDRegisters);
      * pairwiseAddedTwice = vpaddl_s32(pairwiseAddedOnce);
      * output[x][0] = (int)vget_lane_s64(pairwiseAddedTwice, 0);
      *
      * addedDRegisters = vadd_s16(vget_low_s16(outputMul2), vget_high_s16(outputMul2));
      * pairwiseAddedOnce = vpaddl_s16(addedDRegisters);
      * pairwiseAddedTwice = vpaddl_s32(pairwiseAddedOnce);
      * output[x][2] = (int)vget_lane_s64(pairwiseAddedTwice, 0);
      * 
      * addedDRegisters = vadd_s16(vget_low_s16(outputMul3), vget_high_s16(outputMul3));
      * pairwiseAddedOnce = vpaddl_s16(addedDRegisters);
      * pairwiseAddedTwice = vpaddl_s32(pairwiseAddedOnce);
      * output[x][4] = (int)vget_lane_s64(pairwiseAddedTwice, 0);
      * 
      * addedDRegisters = vadd_s16(vget_low_s16(outputMul3), vget_high_s16(outputMul3));
      * pairwiseAddedOnce = vpaddl_s16(addedDRegisters);
      * pairwiseAddedTwice = vpaddl_s32(pairwiseAddedOnce);
      * output[x][6] = (int)vget_lane_s64(pairwiseAddedTwice, 0);
      * 
      */


      output[x][0] = ((C4 * temp1) +  (C4 * temp2) + (C4 * temp3) + (C4 * temp4)) >> 15;
      output[x][2] = ((C2 * temp1) +  (C6 * temp2) + (-C6 * temp3) + (-C2 * temp4)) >> 15;
      output[x][4] = ((C4 * temp1) +  (-C4 * temp2) + (-C4 * temp3) + (C4 * temp4)) >> 15;
      output[x][6] = ((C6 * temp1) +  (-C2 * temp2) + (C2 * temp3) + (-C6 * temp4)) >> 15;

      temp1 = input[0][x] - input[7][x];
      temp2 = input[1][x] - input[6][x];
      temp3 = input[2][x] - input[5][x];
      temp4 = input[3][x] - input[4][x];

      output[x][1] = ((C1 * temp1) + (C3 * temp2) + (C5 * temp3) + (C7 * temp4)) >> 15;
      output[x][3] = ((C3 * temp1) + (-C7 * temp2) + (-C1 * temp3) + (-C5 * temp4)) >> 15;
      output[x][5] = ((C5 * temp1) + (-C1 * temp2) + (C7 * temp3) + (C3 * temp4)) >> 15;
      output[x][7] = ((C7 * temp1) + (-C5 * temp2) + (C3 * temp3) + (-C1 * temp4)) >> 15;
    }

    for(i = 0; i < 8; i++) {
      for(j = 0; j < 8; j++){
        input[i][j] = output[i][j];
      }
    }
  }

  for(i = 0; i < 8; i++) {
    for(j = 0; j < 8; j++) {
      output[i][j] >>= 2;
    }
  }

  return EXIT_SUCCESS;
}