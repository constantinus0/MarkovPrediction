#include <stdio.h>
#include <stdlib.h>
//#include "functions.h"

int status,i,j;
double *series, *diff_series;
double min, max;
int N;

int main(int argc, char *argv[]){
  
  printf("Testgrounds for Markov-Prediction project\n");

  status = readFile("sample_input.txt", &series, &N);
  if (status == -1) {
      perror("Program will exit!\n");
      return 1;
  }

  printf("Number of lines: %d\n", N);

  status = diff(series, N, &diff_series);

  for (i = 0; i < N; i++) {
    printf("(%02d): %lf, %lf\n", i+1, series[i], diff_series[i]);
  }

  status = minmax(series, N, &min, &max);

  printf("Min = %lf\tMax = %lf\n", min, max);

  return 0;
}
