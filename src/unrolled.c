#include <stdint.h>

#define C1 32138
#define C2 30274
#define C3 27246
#define C4 23170
#define C5 18205
#define C6 12540
#define C7 6393

void unrolled(int32_t input[8][8], int32_t output[8][8]) {
  // input actually only uint8_t
  register int i;
  register int64_t temp1, temp2, temp3, temp4;
  int64_t temp[8][8];

  for (i = 0; i < 8; i++) {
    temp1 = input[i][0] + input[i][7];
    temp2 = input[i][1] + input[i][6];
    temp3 = input[i][2] + input[i][5];
    temp4 = input[i][3] + input[i][4];

    // Maintain transpose-ness
    temp[0][i] = (temp1 + temp2 + temp3 + temp4) * C4;
    temp[2][i] = ((C2 * temp1) + (C6 * temp2) + (-C6 * temp3) + (-C2 * temp4));
    temp[4][i] = (temp1 + temp4) * C4 + (temp2 + temp3) * -C4;
    temp[6][i] = ((C6 * temp1) + (-C2 * temp2) + (C2 * temp3) + (-C6 * temp4));

    temp1 = input[i][0] - input[i][7];
    temp2 = input[i][1] - input[i][6];
    temp3 = input[i][2] - input[i][5];
    temp4 = input[i][3] - input[i][4];

    temp[1][i] = ((C1 * temp1) + (C3 * temp2) + (C5 * temp3) + (C7 * temp4));
    temp[3][i] = ((C3 * temp1) + (-C7 * temp2) + (-C1 * temp3) + (-C5 * temp4));
    temp[5][i] = ((C5 * temp1) + (-C1 * temp2) + (C7 * temp3) + (C3 * temp4));
    temp[7][i] = ((C7 * temp1) + (-C5 * temp2) + (C3 * temp3) + (-C1 * temp4));
  }

  for(i = 0; i < 8; i++) {
    temp1 = temp[i][0] + temp[i][7];
    temp2 = temp[i][1] + temp[i][6];
    temp3 = temp[i][2] + temp[i][5];
    temp4 = temp[i][3] + temp[i][4];

    // Transpose again to get original image
    output[i][0] = ((temp1 + temp2 + temp3 + temp4) * C4) >> 32;
    output[i][2] = ((C2 * temp1) + (C6 * temp2) + (-C6 * temp3) + (-C2 * temp4)) >> 32;
    output[i][4] = ((temp1 + temp4) * C4 + (temp2 + temp3) * -C4) >> 32;
    output[i][6] = ((C6 * temp1) + (-C2 * temp2) + (C2 * temp3) + (-C6 * temp4)) >> 32;

    temp1 = temp[i][0] - temp[i][7];
    temp2 = temp[i][1] - temp[i][6];
    temp3 = temp[i][2] - temp[i][5];
    temp4 = temp[i][3] - temp[i][4];

    output[i][1] = ((C1 * temp1) + (C3 * temp2) + (C5 * temp3) + (C7 * temp4)) >> 32;
    output[i][3] = ((C3 * temp1) + (-C7 * temp2) + (-C1 * temp3) + (-C5 * temp4)) >> 32;
    output[i][5] = ((C5 * temp1) + (-C1 * temp2) + (C7 * temp3) + (C3 * temp4)) >> 32;
    output[i][7] = ((C7 * temp1) + (-C5 * temp2) + (C3 * temp3) + (-C1 * temp4)) >> 32;
  }
}
