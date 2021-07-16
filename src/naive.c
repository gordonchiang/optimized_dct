#include <math.h>
#include <stdint.h>

void naive(uint8_t input[8][8], int output[8][8]) {
  for(int u = 0; u < 8; u++) {
    double Cu = (u == 0 ? 1/sqrt(2) : 1)/2;

    for(int v = 0; v < 8; v++) {
      double Cv = (v == 0 ? 1/sqrt(2) : 1)/2;
      
      double outer_sum = 0;
      for(int i = 0; i < 8; i++) {
        double inner_sum = 0;

        for(int j = 0; j < 8; j++) {
          inner_sum += input[i][j] * cos((2*i+1)*u*M_PI/16) * cos((2*j+1)*v*M_PI/16);
        }

        outer_sum += inner_sum;
      }
      output[u][v] = Cu * Cv * outer_sum;
    }
  }
}
