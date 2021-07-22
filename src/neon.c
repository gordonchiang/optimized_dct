#include <stdint.h>
#include "arm_neon.h"

#define C1 32138
#define C2 30274
#define C3 27246
#define C4 23170
#define C5 18205
#define C6 12540
#define C7 6393

void neon(int input[8][8], int output[8][8]) {
  int x, y, i, j;
  for (y = 2; y != 0; y--) {
    for (x = 0; x < 8; x++) {
      // Load temp as a vector
      int32_t temp[4] = {
        input[0][x] + input[7][x], // temp1
        input[1][x] + input[6][x], // temp2
        input[2][x] + input[5][x], // temp3
        input[3][x] + input[4][x], // temp4
      };
     
      int32x4_t inputInitial;
      inputInitial = vld1q_s32(temp);
      // Load C as a vector
      int32_t arr1[4] = {C4, C4, C4, C4};
      int32_t arr2[4] = {C2, C6, -C6, -C2};
      int32_t arr3[4] = {C4, -C4, -C4, C4};
      int32_t arr4[4] = {C6, -C2, C2, -C6};

      int32x4_t cArr1, cArr2, cArr3, cArr4;
      cArr1 = vld1q_s32(arr1);
      cArr2 = vld1q_s32(arr2);
      cArr3 = vld1q_s32(arr3);
      cArr4 = vld1q_s32(arr4);
      
      // This is C[x] * temp1, C[x] * temp2, C[x] * temp3, C[x] * temp4
      // int32x4_t outputMul1, outputMul2, outputMul3, outputMul4;
      int32x4_t outputMul1 = vmulq_s32(cArr1, inputInitial); // output[x][0]
      int32x4_t outputMul2 = vmulq_s32(cArr2, inputInitial); // output[x][2]
      int32x4_t outputMul3 = vmulq_s32(cArr3, inputInitial); // output[x][4]
      int32x4_t outputMul4 = vmulq_s32(cArr4, inputInitial); // output[x][6]

      // have to take every elemnt of the vector and sum it
      // https://github.com/thenifty/neon-guide
      // https://community.arm.com/developer/tools-software/tools/f/armds-forum/556/fastest-s16-summation-reduction-of-a-q-register
      // https://stackoverflow.com/questions/40890319/how-to-add-all-int32-element-in-a-lane-using-neon-intrinsic

      // sum first row
      int64x2_t pairwiseAddedOnce;
      int32x2_t narrowed;
      int64x1_t pairwiseAddedTwice;
      int32_t sum;

      pairwiseAddedOnce = vpaddlq_s32(outputMul1);
      narrowed = vmovn_s64(pairwiseAddedOnce);
      pairwiseAddedTwice = vpaddl_s32(narrowed);
      sum = (int32_t)vget_lane_s64(pairwiseAddedTwice, 0);
      output[x][0] = sum >> 15;

      pairwiseAddedOnce = vpaddlq_s32(outputMul2);
      narrowed = vmovn_s64(pairwiseAddedOnce);
      pairwiseAddedTwice = vpaddl_s32(narrowed);
      sum = (int32_t)vget_lane_s64(pairwiseAddedTwice, 0);
      output[x][2] = sum >> 15;

      pairwiseAddedOnce = vpaddlq_s32(outputMul3);
      narrowed = vmovn_s64(pairwiseAddedOnce);
      pairwiseAddedTwice = vpaddl_s32(narrowed);
      sum = (int32_t)vget_lane_s64(pairwiseAddedTwice, 0);
      output[x][4] = sum >> 15;

      pairwiseAddedOnce = vpaddlq_s32(outputMul4);
      narrowed = vmovn_s64(pairwiseAddedOnce);
      pairwiseAddedTwice = vpaddl_s32(narrowed);
      sum = (int32_t)vget_lane_s64(pairwiseAddedTwice, 0);
      output[x][6] = sum >> 15;
      
      // next

      temp[0] = input[0][x] - input[7][x];
      temp[1] = input[1][x] - input[6][x];
      temp[2] = input[2][x] - input[5][x];
      temp[3] = input[3][x] - input[4][x];
      inputInitial = vld1q_s32(temp);

      // Load C as a vector
      arr1[0] = C1;
      arr1[1] = C3;
      arr1[2] = C5;
      arr1[3] = C7;
      arr2[0] = C3;
      arr2[1] = -C7;
      arr2[2] = -C1;
      arr2[3] = -C5;
      arr3[0] = C5;
      arr3[1] = -C1;
      arr3[2] = C7;
      arr3[3] = C3;
      arr4[0] = C7;
      arr4[1] = -C5;
      arr4[2] = C3;
      arr4[3] = -C1;
      cArr1 = vld1q_s32(arr1);
      cArr2 = vld1q_s32(arr2);
      cArr3 = vld1q_s32(arr3);
      cArr4 = vld1q_s32(arr4);

      outputMul1 = vmulq_s32(cArr1, inputInitial); // output[x][1]
      outputMul2 = vmulq_s32(cArr2, inputInitial); // output[x][3]
      outputMul3 = vmulq_s32(cArr3, inputInitial); // output[x][5]
      outputMul4 = vmulq_s32(cArr4, inputInitial); // output[x][7]

      pairwiseAddedOnce = vpaddlq_s32(outputMul1);
      narrowed = vmovn_s64(pairwiseAddedOnce);
      pairwiseAddedTwice = vpaddl_s32(narrowed);
      sum = (int32_t)vget_lane_s64(pairwiseAddedTwice, 0);
      output[x][1] = sum >> 15;

      pairwiseAddedOnce = vpaddlq_s32(outputMul2);
      narrowed = vmovn_s64(pairwiseAddedOnce);
      pairwiseAddedTwice = vpaddl_s32(narrowed);
      sum = (int32_t)vget_lane_s64(pairwiseAddedTwice, 0);
      output[x][3] = sum >> 15;

      pairwiseAddedOnce = vpaddlq_s32(outputMul3);
      narrowed = vmovn_s64(pairwiseAddedOnce);
      pairwiseAddedTwice = vpaddl_s32(narrowed);
      sum = (int32_t)vget_lane_s64(pairwiseAddedTwice, 0);
      output[x][5] = sum >> 15;

      pairwiseAddedOnce = vpaddlq_s32(outputMul4);
      narrowed = vmovn_s64(pairwiseAddedOnce);
      pairwiseAddedTwice = vpaddl_s32(narrowed);
      sum = (int32_t)vget_lane_s64(pairwiseAddedTwice, 0);
      output[x][7] = sum >> 15;
    }

    for (i = 0; i < 8; i++) {
      for (j = 0; j < 8; j++){
        input[i][j] = output[i][j];
      }
    }
  }

  for (i = 0; i < 8; i++) {
    for (j = 0; j < 8; j++) {
      output[i][j] >>= 2;
    }
  }
}
