#include <stdint.h>

// Scale factor << 8
#define C1 251
#define C2 237
#define C3 213
#define C4 181
#define C5 142
#define C6 98
#define C7 50

// This algorithm builds on top of UNROLLED
// It introduces software pipelining
void pipelined(int32_t input[8][8], int32_t output[8][8]) {
  register int i;
  register int32_t temp1, temp2, temp3, temp4;
  int32_t temp[8][8];

  // Prologue
  temp1 = input[0][0] + input[0][7];
  temp2 = input[0][1] + input[0][6];
  temp3 = input[0][2] + input[0][5];
  temp4 = input[0][3] + input[0][4];

  temp[0][0] = (temp1 + temp2 + temp3 + temp4) * C4;
  temp[2][0] = ((C2 * temp1) + (C6 * temp2) + (-C6 * temp3) + (-C2 * temp4));
  temp[4][0] = ((temp1 + temp4) * C4 + (temp2 + temp3) * -C4);
  temp[6][0] = ((C6 * temp1) + (-C2 * temp2) + (C2 * temp3) + (-C6 * temp4));

  for (i ^= i; i < 7; i++) {
    temp1 = input[i][0] - input[i][7];
    temp2 = input[i][1] - input[i][6];
    temp3 = input[i][2] - input[i][5];
    temp4 = input[i][3] - input[i][4];

    temp[1][i] = ((C1 * temp1) + (C3 * temp2) + (C5 * temp3) + (C7 * temp4));
    temp[3][i] = ((C3 * temp1) + (-C7 * temp2) + (-C1 * temp3) + (-C5 * temp4));
    temp[5][i] = ((C5 * temp1) + (-C1 * temp2) + (C7 * temp3) + (C3 * temp4));
    temp[7][i] = ((C7 * temp1) + (-C5 * temp2) + (C3 * temp3) + (-C1 * temp4));

    // Next loop
    temp1 = input[i+1][0] + input[i+1][7];
    temp2 = input[i+1][1] + input[i+1][6];
    temp3 = input[i+1][2] + input[i+1][5];
    temp4 = input[i+1][3] + input[i+1][4];

    temp[0][i+1] = (temp1 + temp2 + temp3 + temp4) * C4;
    temp[2][i+1] = ((C2 * temp1) + (C6 * temp2) + (-C6 * temp3) + (-C2 * temp4));
    temp[4][i+1] = ((temp1 + temp4) * C4 + (temp2 + temp3) * -C4);
    temp[6][i+1] = ((C6 * temp1) + (-C2 * temp2) + (C2 * temp3) + (-C6 * temp4));
  }

  // Epilogue
  temp1 = input[7][0] - input[7][7];
  temp2 = input[7][1] - input[7][6];
  temp3 = input[7][2] - input[7][5];
  temp4 = input[7][3] - input[7][4];

  temp[1][7] = ((C1 * temp1) + (C3 * temp2) + (C5 * temp3) + (C7 * temp4));
  temp[3][7] = ((C3 * temp1) + (-C7 * temp2) + (-C1 * temp3) + (-C5 * temp4));
  temp[5][7] = ((C5 * temp1) + (-C1 * temp2) + (C7 * temp3) + (C3 * temp4));
  temp[7][7] = ((C7 * temp1) + (-C5 * temp2) + (C3 * temp3) + (-C1 * temp4));

  // Calculate the 1-D DCT

  // Prologue
  temp1 = temp[0][0] + temp[0][7];
  temp2 = temp[0][1] + temp[0][6];
  temp3 = temp[0][2] + temp[0][5];
  temp4 = temp[0][3] + temp[0][4];

  output[0][0] = ((temp1 + temp2 + temp3 + temp4) * C4) >> 18;
  output[0][2] = ((C2 * temp1) + (C6 * temp2) + (-C6 * temp3) + (-C2 * temp4)) >> 18;
  output[0][4] = ((temp1 + temp4) * C4 + (temp2 + temp3) * -C4) >> 18;
  output[0][6] = ((C6 * temp1) + (-C2 * temp2) + (C2 * temp3) + (-C6 * temp4)) >> 18;

  for(i ^= i; i < 7; i++) {
    temp1 = temp[i][0] - temp[i][7];
    temp2 = temp[i][1] - temp[i][6];
    temp3 = temp[i][2] - temp[i][5];
    temp4 = temp[i][3] - temp[i][4];

    output[i][1] = ((C1 * temp1) + (C3 * temp2) + (C5 * temp3) + (C7 * temp4)) >> 18;
    output[i][3] = ((C3 * temp1) + (-C7 * temp2) + (-C1 * temp3) + (-C5 * temp4)) >> 18;
    output[i][5] = ((C5 * temp1) + (-C1 * temp2) + (C7 * temp3) + (C3 * temp4)) >> 18;
    output[i][7] = ((C7 * temp1) + (-C5 * temp2) + (C3 * temp3) + (-C1 * temp4)) >> 18;

    // Next loop
    temp1 = temp[i+1][0] + temp[i+1][7];
    temp2 = temp[i+1][1] + temp[i+1][6];
    temp3 = temp[i+1][2] + temp[i+1][5];
    temp4 = temp[i+1][3] + temp[i+1][4];

    output[i+1][0] = ((temp1 + temp2 + temp3 + temp4) * C4) >> 18;
    output[i+1][2] = ((C2 * temp1) + (C6 * temp2) + (-C6 * temp3) + (-C2 * temp4)) >> 18;
    output[i+1][4] = ((temp1 + temp4) * C4 + (temp2 + temp3) * -C4) >> 18;
    output[i+1][6] = ((C6 * temp1) + (-C2 * temp2) + (C2 * temp3) + (-C6 * temp4)) >> 18;
  }

  // Epilogue
  temp1 = temp[7][0] - temp[7][7];
  temp2 = temp[7][1] - temp[7][6];
  temp3 = temp[7][2] - temp[7][5];
  temp4 = temp[7][3] - temp[7][4];

  output[7][1] = ((C1 * temp1) + (C3 * temp2) + (C5 * temp3) + (C7 * temp4)) >> 18;
  output[7][3] = ((C3 * temp1) + (-C7 * temp2) + (-C1 * temp3) + (-C5 * temp4)) >> 18;
  output[7][5] = ((C5 * temp1) + (-C1 * temp2) + (C7 * temp3) + (C3 * temp4)) >> 18;
  output[7][7] = ((C7 * temp1) + (-C5 * temp2) + (C3 * temp3) + (-C1 * temp4)) >> 18;
}
