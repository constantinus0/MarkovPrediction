#include <stdio.h>
#include <stdlib.h>

int i;

int diff(double *data, int length, double **diff) {


  *diff = (double *) malloc(length);

  diff[0][0] = 0;
  for (i=1; i < length; i++) {
    diff[0][i] = data[i] - data[i-1];
   }


  return 0;
}
