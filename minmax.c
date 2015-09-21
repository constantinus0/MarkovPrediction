#include <stdio.h>
#include <stdlib.h>

int i;

int minmax(double *data, int length, double *min, double *max) {

  min[0] = data[0];
  max[0] = data[0];

  for(i=1;i<length;i++){
    if(data[i] < min[0]) min[0] = data[i];
    if(data[i] > max[0]) max[0] = data[i];
  }


  return 0;
}
