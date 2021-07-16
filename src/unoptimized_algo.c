#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

int unoptimized_algo(uint8_t *input2, int output2[8][8]) {
  double C1 = cos(1*M_PI/16);
  double C2 = cos(2*M_PI/16);
  double C3 = cos(3*M_PI/16);
  double C4 = cos(4*M_PI/16);
  double C5 = cos(5*M_PI/16);
  double C6 = cos(6*M_PI/16);
  double C7 = cos(7*M_PI/16);
  double C[8][8], CT[8][8];
  double output[8][8];
  for(int i = 0; i < 8; i++) {
    for(int j = 0; j < 8; j++) {
      C[i][j] = 0.;
      CT[i][j] = 0.;
      output[i][j] = 0.;
    }
  }
  C[0][0] = C4;
  C[0][1] = C4;
  C[0][2] = C4;
  C[0][3] = C4;
  C[1][0] = C2;
  C[1][1] = C6;
  C[1][2] = -C6;
  C[1][3] = -C2;
  C[2][0] = C4;
  C[2][1] = -C4;
  C[2][2] = -C4;
  C[2][3] = C4;
  C[3][0] = C6;
  C[3][1] = -C2;
  C[3][2] = C2;
  C[3][3] = -C6;
  C[4][4] = C1;
  C[4][5] = C3;
  C[4][6] = C5;
  C[4][7] = C7;
  C[5][4] = C3;
  C[5][5] = -C7;
  C[5][6] = -C1;
  C[5][7] = -C5;
  C[6][4] = C5;
  C[6][5] = -C1;
  C[6][6] = C7;
  C[6][7] = C3;
  C[7][4] = C7;
  C[7][5] = -C5;
  C[7][6] = C3;
  C[7][7] = -C1;

  for(int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      CT[i][j] = C[j][i];
    }
  }

  double input[8][8];
  // printf("input:\n");
  for(int i = 0; i < 8; i++) {
    for(int j = 0; j < 8; j++) {
      input[i][j] = input2[i*8+j];
    }
  }

  for(int i = 0; i < 8; i++) { // row 0
    output[0][i] += C[0][0] * (input[0][i] + input[7][i]);
    output[0][i] += C[0][1] * (input[1][i] + input[6][i]);
    output[0][i] += C[0][2] * (input[2][i] + input[5][i]);
    output[0][i] += C[0][3] * (input[3][i] + input[4][i]);

    // output[0][i] += C[0][4] * (input[0][i] - input[7][i]);
    // output[0][i] += C[0][5] * (input[1][i] - input[6][i]);
    // output[0][i] += C[0][6] * (input[2][i] - input[5][i]);
    // output[0][i] += C[0][7] * (input[3][i] - input[4][i]);
  }

  for(int i = 0; i < 8; i++) { // row 1
    // output[1][i] += C[4][0] * (input[0][i] + input[7][i]);
    // output[1][i] += C[4][1] * (input[1][i] + input[6][i]);
    // output[1][i] += C[4][2] * (input[2][i] + input[5][i]);
    // output[1][i] += C[4][3] * (input[3][i] + input[4][i]);

    output[1][i] += C[4][4] * (input[0][i] - input[7][i]);
    output[1][i] += C[4][5] * (input[1][i] - input[6][i]);
    output[1][i] += C[4][6] * (input[2][i] - input[5][i]);
    output[1][i] += C[4][7] * (input[3][i] - input[4][i]);
  }

  for(int i = 0; i < 8; i++) { // row 2
    output[2][i] += C[1][0] * (input[0][i] + input[7][i]);
    output[2][i] += C[1][1] * (input[1][i] + input[6][i]);
    output[2][i] += C[1][2] * (input[2][i] + input[5][i]);
    output[2][i] += C[1][3] * (input[3][i] + input[4][i]);

    // output[2][i] += C[1][4] * (input[0][i] - input[7][i]);
    // output[2][i] += C[1][5] * (input[1][i] - input[6][i]);
    // output[2][i] += C[1][6] * (input[2][i] - input[5][i]);
    // output[2][i] += C[1][7] * (input[3][i] - input[4][i]);
  }

  for(int i = 0; i < 8; i++) { // row 3
    // output[3][i] += C[5][0] * (input[0][i] + input[7][i]);
    // output[3][i] += C[5][1] * (input[1][i] + input[6][i]);
    // output[3][i] += C[5][2] * (input[2][i] + input[5][i]);
    // output[3][i] += C[5][3] * (input[3][i] + input[4][i]);

    output[3][i] += C[5][4] * (input[0][i] - input[7][i]);
    output[3][i] += C[5][5] * (input[1][i] - input[6][i]);
    output[3][i] += C[5][6] * (input[2][i] - input[5][i]);
    output[3][i] += C[5][7] * (input[3][i] - input[4][i]);
  }

  for(int i = 0; i < 8; i++) { // row 4
    output[4][i] += C[2][0] * (input[0][i] + input[7][i]);
    output[4][i] += C[2][1] * (input[1][i] + input[6][i]);
    output[4][i] += C[2][2] * (input[2][i] + input[5][i]);
    output[4][i] += C[2][3] * (input[3][i] + input[4][i]);

    // output[4][i] += C[2][4] * (input[0][i] - input[7][i]);
    // output[4][i] += C[2][5] * (input[1][i] - input[6][i]);
    // output[4][i] += C[2][6] * (input[2][i] - input[5][i]);
    // output[4][i] += C[2][7] * (input[3][i] - input[4][i]);
  }

  for(int i = 0; i < 8; i++) { // row 5
    // output[5][i] += C[6][0] * (input[0][i] + input[7][i]);
    // output[5][i] += C[6][1] * (input[1][i] + input[6][i]);
    // output[5][i] += C[6][2] * (input[2][i] + input[5][i]);
    // output[5][i] += C[6][3] * (input[3][i] + input[4][i]);

    output[5][i] += C[6][4] * (input[0][i] - input[7][i]);
    output[5][i] += C[6][5] * (input[1][i] - input[6][i]);
    output[5][i] += C[6][6] * (input[2][i] - input[5][i]);
    output[5][i] += C[6][7] * (input[3][i] - input[4][i]);
  }

  for(int i = 0; i < 8; i++) { // row 6
    output[6][i] += C[3][0] * (input[0][i] + input[7][i]);
    output[6][i] += C[3][1] * (input[1][i] + input[6][i]);
    output[6][i] += C[3][2] * (input[2][i] + input[5][i]);
    output[6][i] += C[3][3] * (input[3][i] + input[4][i]);

    // output[6][i] += C[3][4] * (input[0][i] - input[7][i]);
    // output[6][i] += C[3][5] * (input[1][i] - input[6][i]);
    // output[6][i] += C[3][6] * (input[2][i] - input[5][i]);
    // output[6][i] += C[3][7] * (input[3][i] - input[4][i]);
  }

  for(int i = 0; i < 8; i++) { // row 7
    // output[7][i] += C[7][0] * (input[0][i] + input[7][i]);
    // output[7][i] += C[7][1] * (input[1][i] + input[6][i]);
    // output[7][i] += C[7][2] * (input[2][i] + input[5][i]);
    // output[7][i] += C[7][3] * (input[3][i] + input[4][i]);

    output[7][i] += C[7][4] * (input[0][i] - input[7][i]);
    output[7][i] += C[7][5] * (input[1][i] - input[6][i]);
    output[7][i] += C[7][6] * (input[2][i] - input[5][i]);
    output[7][i] += C[7][7] * (input[3][i] - input[4][i]);
  }

  double Ctimesx[8][8];
  for(int i = 0; i < 8; i++) {
    for(int j = 0; j < 8; j++) {
      Ctimesx[i][j] = output[i][j];
      output[i][j] = 0;
    }
  }

  for(int i = 0; i < 8; i++) { // column 0
    output[i][0] += (Ctimesx[i][0] + Ctimesx[i][7]) * CT[0][0];
    output[i][0] += (Ctimesx[i][1] + Ctimesx[i][6]) * CT[1][0];
    output[i][0] += (Ctimesx[i][2] + Ctimesx[i][5]) * CT[2][0];
    output[i][0] += (Ctimesx[i][3] + Ctimesx[i][4]) * CT[3][0];

    // output[i][0] += (Ctimesx[i][0] - Ctimesx[i][7]) * CT[4][0];
    // output[i][0] += (Ctimesx[i][1] - Ctimesx[i][6]) * CT[5][0];
    // output[i][0] += (Ctimesx[i][2] - Ctimesx[i][5]) * CT[6][0];
    // output[i][0] += (Ctimesx[i][3] - Ctimesx[i][4]) * CT[7][0];

    output[i][0] /= 4;
  }

  for(int i = 0; i < 8; i++) { // column 1
    // output[i][1] += (Ctimesx[i][0] + Ctimesx[i][7]) * CT[0][4];
    // output[i][1] += (Ctimesx[i][1] + Ctimesx[i][6]) * CT[1][4];
    // output[i][1] += (Ctimesx[i][2] + Ctimesx[i][5]) * CT[2][4];
    // output[i][1] += (Ctimesx[i][3] + Ctimesx[i][4]) * CT[3][4];

    output[i][1] += (Ctimesx[i][0] - Ctimesx[i][7]) * CT[4][4];
    output[i][1] += (Ctimesx[i][1] - Ctimesx[i][6]) * CT[5][4];
    output[i][1] += (Ctimesx[i][2] - Ctimesx[i][5]) * CT[6][4];
    output[i][1] += (Ctimesx[i][3] - Ctimesx[i][4]) * CT[7][4];

    output[i][1] /= 4;
  }

  for(int i = 0; i < 8; i++) { // column 2
    output[i][2] += (Ctimesx[i][0] + Ctimesx[i][7]) * CT[0][1];
    output[i][2] += (Ctimesx[i][1] + Ctimesx[i][6]) * CT[1][1];
    output[i][2] += (Ctimesx[i][2] + Ctimesx[i][5]) * CT[2][1];
    output[i][2] += (Ctimesx[i][3] + Ctimesx[i][4]) * CT[3][1];

    // output[i][2] += (Ctimesx[i][0] - Ctimesx[i][7]) * CT[4][1];
    // output[i][2] += (Ctimesx[i][1] - Ctimesx[i][6]) * CT[5][1];
    // output[i][2] += (Ctimesx[i][2] - Ctimesx[i][5]) * CT[6][1];
    // output[i][2] += (Ctimesx[i][3] - Ctimesx[i][4]) * CT[7][1];

    output[i][2] /= 4;
  }

    for(int i = 0; i < 8; i++) { // column 3
    // output[i][3] += (Ctimesx[i][0] + Ctimesx[i][7]) * CT[0][5];
    // output[i][3] += (Ctimesx[i][1] + Ctimesx[i][6]) * CT[1][5];
    // output[i][3] += (Ctimesx[i][2] + Ctimesx[i][5]) * CT[2][5];
    // output[i][3] += (Ctimesx[i][3] + Ctimesx[i][4]) * CT[3][5];

    output[i][3] += (Ctimesx[i][0] - Ctimesx[i][7]) * CT[4][5];
    output[i][3] += (Ctimesx[i][1] - Ctimesx[i][6]) * CT[5][5];
    output[i][3] += (Ctimesx[i][2] - Ctimesx[i][5]) * CT[6][5];
    output[i][3] += (Ctimesx[i][3] - Ctimesx[i][4]) * CT[7][5];

    output[i][3] /= 4;
  }

  for(int i = 0; i < 8; i++) { // column 4
    output[i][4] += (Ctimesx[i][0] + Ctimesx[i][7]) * CT[0][2];
    output[i][4] += (Ctimesx[i][1] + Ctimesx[i][6]) * CT[1][2];
    output[i][4] += (Ctimesx[i][2] + Ctimesx[i][5]) * CT[2][2];
    output[i][4] += (Ctimesx[i][3] + Ctimesx[i][4]) * CT[3][2];

    // output[i][4] += (Ctimesx[i][0] - Ctimesx[i][7]) * CT[4][2];
    // output[i][4] += (Ctimesx[i][1] - Ctimesx[i][6]) * CT[5][2];
    // output[i][4] += (Ctimesx[i][2] - Ctimesx[i][5]) * CT[6][2];
    // output[i][4] += (Ctimesx[i][3] - Ctimesx[i][4]) * CT[7][2];

    output[i][4] /= 4;
  }

  for(int i = 0; i < 8; i++) { // column 5
    // output[i][5] += (Ctimesx[i][0] + Ctimesx[i][7]) * CT[0][6];
    // output[i][5] += (Ctimesx[i][1] + Ctimesx[i][6]) * CT[1][6];
    // output[i][5] += (Ctimesx[i][2] + Ctimesx[i][5]) * CT[2][6];
    // output[i][5] += (Ctimesx[i][3] + Ctimesx[i][4]) * CT[3][6];

    output[i][5] += (Ctimesx[i][0] - Ctimesx[i][7]) * CT[4][6];
    output[i][5] += (Ctimesx[i][1] - Ctimesx[i][6]) * CT[5][6];
    output[i][5] += (Ctimesx[i][2] - Ctimesx[i][5]) * CT[6][6];
    output[i][5] += (Ctimesx[i][3] - Ctimesx[i][4]) * CT[7][6];

    output[i][5] /= 4;
  }

  for(int i = 0; i < 8; i++) { // column 6
    output[i][6] += (Ctimesx[i][0] + Ctimesx[i][7]) * CT[0][3];
    output[i][6] += (Ctimesx[i][1] + Ctimesx[i][6]) * CT[1][3];
    output[i][6] += (Ctimesx[i][2] + Ctimesx[i][5]) * CT[2][3];
    output[i][6] += (Ctimesx[i][3] + Ctimesx[i][4]) * CT[3][3];

    // output[i][6] += (Ctimesx[i][0] - Ctimesx[i][7]) * CT[4][3];
    // output[i][6] += (Ctimesx[i][1] - Ctimesx[i][6]) * CT[5][3];
    // output[i][6] += (Ctimesx[i][2] - Ctimesx[i][5]) * CT[6][3];
    // output[i][6] += (Ctimesx[i][3] - Ctimesx[i][4]) * CT[7][3];

    output[i][6] /= 4;
  }

  for(int i = 0; i < 8; i++) { // column 7
    // output[i][7] += (Ctimesx[i][0] + Ctimesx[i][7]) * CT[0][7];
    // output[i][7] += (Ctimesx[i][1] + Ctimesx[i][6]) * CT[1][7];
    // output[i][7] += (Ctimesx[i][2] + Ctimesx[i][5]) * CT[2][7];
    // output[i][7] += (Ctimesx[i][3] + Ctimesx[i][4]) * CT[3][7];

    output[i][7] += (Ctimesx[i][0] - Ctimesx[i][7]) * CT[4][7];
    output[i][7] += (Ctimesx[i][1] - Ctimesx[i][6]) * CT[5][7];
    output[i][7] += (Ctimesx[i][2] - Ctimesx[i][5]) * CT[6][7];
    output[i][7] += (Ctimesx[i][3] - Ctimesx[i][4]) * CT[7][7];

    output[i][7] /= 4;
  }

  for(int i = 0; i < 8; i++) {
    for(int j = 0; j < 8; j++) {
      output2[i][j] = output[i][j];
    }
  }

  return EXIT_SUCCESS;
}