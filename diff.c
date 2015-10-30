#include <stdio.h>
#include <stdlib.h>

int i;
double d;

int diff(double *data, int length, double **diff) {

  *diff = (double *) malloc(length);

  diff[0][0] = 0;
  for (i=1; i < length; i++) {
    d = data[i] - data[i-1];
    diff[0][i] = d;
    // printf("%f, ", diff[0][i]); //cygwin-gcc needs this line otherwise it produces wrong results!
  } //printf("\n\n");

  return 0;
}
