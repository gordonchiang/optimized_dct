#include <stdint.h>

// Scale factor << 8
#define C1 251
#define C2 237
#define C3 213
#define C4 181
#define C5 142
#define C6 98
#define C7 50

// This algorithm builds on top of UNOPTIMIZED
// It unrolls the loop
// Reduces the strength of operators
// Attempts to minimize cache misses
// Optimizes loop initialization and exit
// Lowers the SF so values fit into 1 register
void unrolled(int32_t input[8][8], int32_t output[8][8]) {
  // input actually only uint8_t
  register int i;
  register int32_t temp1, temp2, temp3, temp4, temp5, temp6, temp7, temp8, inputCalc1, inputCalc2;
  int32_t temp[8][8];

  for (i ^= i; !(i&8); i++) {
    inputCalc1 = input[i][0];
    inputCalc2 = input[i][7];
    temp1 = inputCalc1 + inputCalc2;
    temp5 = inputCalc1 - inputCalc2;
    inputCalc1 = input[i][1];
    inputCalc2 = input[i][6];
    temp2 = inputCalc1 + inputCalc2;
    temp6 = inputCalc1 - inputCalc2;
    inputCalc1 = input[i][2];
    inputCalc2 = input[i][5];
    temp3 = inputCalc1 + inputCalc2;
    temp7 = inputCalc1 - inputCalc2;
    inputCalc1 = input[i][3];
    inputCalc2 = input[i][4];
    temp4 = inputCalc1 + inputCalc2;
    temp8 = inputCalc1 - inputCalc2;

    // Maintain transpose-ness
    temp[0][i] = (temp1 + temp2 + temp3 + temp4) * C4;
    temp[1][i] = ((C1 * temp5) + (C3 * temp6) + (C5 * temp7) + (C7 * temp8));
    temp[2][i] = ((C2 * temp1) + (C6 * temp2) + (-C6 * temp3) + (-C2 * temp4));
    temp[3][i] = ((C3 * temp5) + (-C7 * temp6) + (-C1 * temp7) + (-C5 * temp8));
    temp[4][i] = ((temp1 + temp4) * C4 + (temp2 + temp3) * -C4);
    temp[5][i] = ((C5 * temp5) + (-C1 * temp6) + (C7 * temp7) + (C3 * temp8));
    temp[6][i] = ((C6 * temp1) + (-C2 * temp2) + (C2 * temp3) + (-C6 * temp4));
    temp[7][i] = ((C7 * temp5) + (-C5 * temp6) + (C3 * temp7) + (-C1 * temp8));
  }

  for(i ^= i; !(i&8); i++) {
    inputCalc1 = temp[i][0];
    inputCalc2 = temp[i][7];
    temp1 = inputCalc1 + inputCalc2;
    temp5 = inputCalc1 - inputCalc2;
    inputCalc1 = temp[i][1];
    inputCalc2 = temp[i][6];
    temp2 = inputCalc1 + inputCalc2;
    temp6 = inputCalc1 - inputCalc2;
    inputCalc1 = temp[i][2];
    inputCalc2 = temp[i][5];
    temp3 = inputCalc1 + inputCalc2;
    temp7 = inputCalc1 - inputCalc2;
    inputCalc1 = temp[i][3];
    inputCalc2 = temp[i][4];
    temp4 = inputCalc1 + inputCalc2;
    temp8 = inputCalc1 - inputCalc2;

    // Transpose again to get original image
    // Divide each output element by SF
    // Divide by an additional factor of 4 (>> 2)
    output[i][0] = ((temp1 + temp2 + temp3 + temp4) * C4) >> 18;
    output[i][1] = ((C1 * temp5) + (C3 * temp6) + (C5 * temp7) + (C7 * temp8)) >> 18;
    output[i][2] = ((C2 * temp1) + (C6 * temp2) + (-C6 * temp3) + (-C2 * temp4)) >> 18;
    output[i][3] = ((C3 * temp5) + (-C7 * temp6) + (-C1 * temp7) + (-C5 * temp8)) >> 18;
    output[i][4] = ((temp1 + temp4) * C4 + (temp2 + temp3) * -C4) >> 18;
    output[i][5] = ((C5 * temp5) + (-C1 * temp6) + (C7 * temp7) + (C3 * temp8)) >> 18;
    output[i][6] = ((C6 * temp1) + (-C2 * temp2) + (C2 * temp3) + (-C6 * temp4)) >> 18;
    output[i][7] = ((C7 * temp5) + (-C5 * temp6) + (C3 * temp7) + (-C1 * temp8)) >> 18;
  }
}
