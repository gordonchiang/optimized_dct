#include <math.h>
#include <stdint.h>

#ifndef M_PI
  #define M_PI 3.14159265358979323846
#endif

void naive(int input[8][8], int output[8][8]) {
  int u, v, i, j;
  for (u = 0; u < 8; u++) {
    double Cu = (u == 0 ? 1/sqrt(2) : 1)/2;

    for (v = 0; v < 8; v++) {
      double Cv = (v == 0 ? 1/sqrt(2) : 1)/2;
      
      double outer_sum = 0;
      for (i = 0; i < 8; i++) {
        double inner_sum = 0;

        for (j = 0; j < 8; j++) {
          inner_sum += input[i][j] * cos((2*i+1)*u*M_PI/16) * cos((2*j+1)*v*M_PI/16);
        }

        outer_sum += inner_sum;
      }
      output[u][v] = Cu * Cv * outer_sum;
    }
  }
}
