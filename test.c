#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

int status,i,j;
double *series;
int N;

int main(int argc, char *argv[]){
  
  printf("Testgrounds for Markov-Prediction project\n");

  status = readFile("sample_input.txt", &series, &N);
  if (status == -1) {
      perror("Program will exit!\n");
      return 1;
  }

  printf("Number of lines: %d\n", N);
  printf("%f\n", series[0]);

  for (i = 0; i < N; i++) {
      printf("(%02d): %lf\n", i+1, series[i]);
  }





  return 0;
}
