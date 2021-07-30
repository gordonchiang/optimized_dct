#include <stdint.h>
#include "arm_neon.h"

#define C1 251
#define C2 237
#define C3 213
#define C4 181
#define C5 142
#define C6 98
#define C7 50

void neon(int input[8][8], int output[8][8]) {
  register int i;
  register int32_t temp0, temp1, temp2, temp3;
  int32_t temp[8][8];

  int32x4_t C_row_1 = {C2, C6, -C6, -C2};
  int32x4_t C_row_2 = {C4, -C4, -C4, C4};
  int32x4_t C_row_3 = {C6, -C2, C2, -C6};
  int32x4_t C_row_4 = {C1, C3, C5, C7};
  int32x4_t C_row_5 = {C3, -C7, -C1, -C5};
  int32x4_t C_row_6 = {C5, -C1, C7, C3};
  int32x4_t C_row_7 = {C7, -C5, C3, -C1};

  int32x4_t prod;

  int64x2_t pairwiseAddedOnce;
  int32x2_t narrowed;
  int64x1_t pairwiseAddedTwice;

  for (i ^= i; !(i&8); i++) {
    temp0 = input[i][0] + input[i][7];
    temp1 = input[i][1] + input[i][6];
    temp2 = input[i][2] + input[i][5];
    temp3 = input[i][3] + input[i][4];

    int32x4_t tempVector0 = { temp0, temp1, temp2, temp3 };

    pairwiseAddedOnce = vpaddlq_s32(tempVector0);
    narrowed = vmovn_s64(pairwiseAddedOnce);
    pairwiseAddedTwice = vpaddl_s32(narrowed);
    temp[0][i] = (int32_t)vget_lane_s64(pairwiseAddedTwice, 0) * C4;

    prod = vmulq_s32(tempVector0, C_row_1);
    pairwiseAddedOnce = vpaddlq_s32(prod);
    narrowed = vmovn_s64(pairwiseAddedOnce);
    pairwiseAddedTwice = vpaddl_s32(narrowed);
    temp[2][i] = (int32_t)vget_lane_s64(pairwiseAddedTwice, 0);

    prod = vmulq_s32(tempVector0, C_row_2);
    pairwiseAddedOnce = vpaddlq_s32(prod);
    narrowed = vmovn_s64(pairwiseAddedOnce);
    pairwiseAddedTwice = vpaddl_s32(narrowed);
    temp[4][i] = (int32_t)vget_lane_s64(pairwiseAddedTwice, 0);

    prod = vmulq_s32(tempVector0, C_row_3);
    pairwiseAddedOnce = vpaddlq_s32(prod);
    narrowed = vmovn_s64(pairwiseAddedOnce);
    pairwiseAddedTwice = vpaddl_s32(narrowed);
    temp[6][i] = (int32_t)vget_lane_s64(pairwiseAddedTwice, 0);

    temp0 -= input[i][7] << 1;
    temp1 -= input[i][6] << 1;
    temp2 -= input[i][5] << 1;
    temp3 -= input[i][4] << 1;

    int32x4_t tempVector1 = { temp0, temp1, temp2, temp3 };

    prod = vmulq_s32(tempVector1, C_row_4);
    pairwiseAddedOnce = vpaddlq_s32(prod);
    narrowed = vmovn_s64(pairwiseAddedOnce);
    pairwiseAddedTwice = vpaddl_s32(narrowed);
    temp[1][i] = (int32_t)vget_lane_s64(pairwiseAddedTwice, 0);

    prod = vmulq_s32(tempVector1, C_row_5);
    pairwiseAddedOnce = vpaddlq_s32(prod);
    narrowed = vmovn_s64(pairwiseAddedOnce);
    pairwiseAddedTwice = vpaddl_s32(narrowed);
    temp[3][i] = (int32_t)vget_lane_s64(pairwiseAddedTwice, 0);

    prod = vmulq_s32(tempVector1, C_row_6);
    pairwiseAddedOnce = vpaddlq_s32(prod);
    narrowed = vmovn_s64(pairwiseAddedOnce);
    pairwiseAddedTwice = vpaddl_s32(narrowed);
    temp[5][i] = (int32_t)vget_lane_s64(pairwiseAddedTwice, 0);

    prod = vmulq_s32(tempVector1, C_row_7);
    pairwiseAddedOnce = vpaddlq_s32(prod);
    narrowed = vmovn_s64(pairwiseAddedOnce);
    pairwiseAddedTwice = vpaddl_s32(narrowed);
    temp[7][i] = (int32_t)vget_lane_s64(pairwiseAddedTwice, 0);
  }

  for(i ^= i; !(i&8); i++) {
    temp0 = temp[i][0] + temp[i][7];
    temp1 = temp[i][1] + temp[i][6];
    temp2 = temp[i][2] + temp[i][5];
    temp3 = temp[i][3] + temp[i][4];

    int32x4_t tempVector0 = { temp0, temp1, temp2, temp3 };

    pairwiseAddedOnce = vpaddlq_s32(tempVector0);
    narrowed = vmovn_s64(pairwiseAddedOnce);
    pairwiseAddedTwice = vpaddl_s32(narrowed);
    output[i][0] = ((int32_t)vget_lane_s64(pairwiseAddedTwice, 0) * C4) >> 18;

    prod = vmulq_s32(tempVector0, C_row_1);
    pairwiseAddedOnce = vpaddlq_s32(prod);
    narrowed = vmovn_s64(pairwiseAddedOnce);
    pairwiseAddedTwice = vpaddl_s32(narrowed);
    output[i][2] = (int32_t)vget_lane_s64(pairwiseAddedTwice, 0) >> 18;

    prod = vmulq_s32(tempVector0, C_row_2);
    pairwiseAddedOnce = vpaddlq_s32(prod);
    narrowed = vmovn_s64(pairwiseAddedOnce);
    pairwiseAddedTwice = vpaddl_s32(narrowed);
    output[i][4] = (int32_t)vget_lane_s64(pairwiseAddedTwice, 0) >> 18;

    prod = vmulq_s32(tempVector0, C_row_3);
    pairwiseAddedOnce = vpaddlq_s32(prod);
    narrowed = vmovn_s64(pairwiseAddedOnce);
    pairwiseAddedTwice = vpaddl_s32(narrowed);
    output[i][6] = (int32_t)vget_lane_s64(pairwiseAddedTwice, 0) >> 18;

    temp0 -= temp[i][7] << 1;
    temp1 -= temp[i][6] << 1;
    temp2 -= temp[i][5] << 1;
    temp3 -= temp[i][4] << 1;

    int32x4_t tempVector1 = { temp0, temp1, temp2, temp3 };

    prod = vmulq_s32(tempVector1, C_row_4);
    pairwiseAddedOnce = vpaddlq_s32(prod);
    narrowed = vmovn_s64(pairwiseAddedOnce);
    pairwiseAddedTwice = vpaddl_s32(narrowed);
    output[i][1] = (int32_t)vget_lane_s64(pairwiseAddedTwice, 0) >> 18;;

    prod = vmulq_s32(tempVector1, C_row_5);
    pairwiseAddedOnce = vpaddlq_s32(prod);
    narrowed = vmovn_s64(pairwiseAddedOnce);
    pairwiseAddedTwice = vpaddl_s32(narrowed);
    output[i][3] = (int32_t)vget_lane_s64(pairwiseAddedTwice, 0) >> 18;

    prod = vmulq_s32(tempVector1, C_row_6);
    pairwiseAddedOnce = vpaddlq_s32(prod);
    narrowed = vmovn_s64(pairwiseAddedOnce);
    pairwiseAddedTwice = vpaddl_s32(narrowed);
    output[i][5] = (int32_t)vget_lane_s64(pairwiseAddedTwice, 0) >> 18;

    prod = vmulq_s32(tempVector1, C_row_7);
    pairwiseAddedOnce = vpaddlq_s32(prod);
    narrowed = vmovn_s64(pairwiseAddedOnce);
    pairwiseAddedTwice = vpaddl_s32(narrowed);
    output[i][7] = (int32_t)vget_lane_s64(pairwiseAddedTwice, 0) >> 18;
  }
}
