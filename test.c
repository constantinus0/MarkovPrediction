#include <stdio.h>
#include <stdlib.h>
// #include "functions.h"

int status, i, j;
double *series, *diff_series, **data, *binVals;
double min, max;
int diffOrder, nBins, N, D, base, vLen, **symb;
long int s;
long *baseVec;

int main(int argc, char *argv[]){
  // Global Parameters! In final release they should be all given as input arguments!
  diffOrder = 2;
  nBins = 2;
  // end of Global Parameter declaration ...........................................
  
  printf("Testgrounds for Markov-Prediction project\n");

  status = readFile("sample_input.txt", &series, &N);
  if (status == -1) {
      perror("Program will exit!\n");
      return 1;
  }
  printf("Number of lines: %d\n", N);

  D = diffOrder + 1;

  // Create Data matrix to store the data and the difference series (D rows x N columns)
  // index 'j' operates on the difference series, while index 'i' operates on the entries
  data = malloc(D * sizeof(double*));
  if (data == NULL) {perror("Memory allocation failed!\n"); return 2; }
  for (j=0; j<D; j++){ data[j] =  malloc(N * sizeof(double)); }

  // Assign Values to Data Matrix
  // first row (raw data)
  for (i=0; i<N; i++){ data[0][i] = series[i]; }
  // the rest rows (difference series)
  for (j=1; j<D; j++){
    status = diff(data[j-1], N, &diff_series);
    for (i=0; i<N; i++){
      data[j][i] = diff_series[i];
    }
  }

  // Print Data and Difference Series
  for (i=0; i<N; i++){
    for (j=0; j<D; j++){
      printf("%f, ", data[j][i]);
    }
    printf("\n");
  }

  // Phase space:
  //              nDims = D (diff order + 1 for the original series)
  //              base = number of bins (the No of possible "events" in each dimension)

  // Create the base Vector
  status = baseVector(D, nBins, &baseVec);
  for(i=0; i<D; i++){ printf("%d, ",baseVec[i]); } printf("\n");

  // Convert Data Matrix to Symbolic, State Matrix
  status = stateMatrix(data, D, N, nBins, &symb, &binVals);

  // free(series); // freeing "series" causes "core dumped" error!
  free(diff_series);
  for (j=0; j<D; j++){ free(data[j]); } free(data);
  return 0;
}
