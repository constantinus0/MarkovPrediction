#include <stdio.h>
#include <stdlib.h>
// #include "functions.h"

int status, i, j;
double *series, *diff_series, **data, *binVals, **limits, **transProbMat, *initVec, **output;
double min, max;
int diffOrder, nBins, N, D, base, vLen, **symb, **trans, nStates, *initState, nPred, nScen;
long int s;
int *baseVec;
FILE *fid;

int main(int argc, char *argv[]){
  // Global Parameters! In final release they should be all given as input arguments!
  diffOrder = 2;
  nBins = 21;
  nPred = 50;
  nScen = 10;
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
  /* for (i=0; i<N; i++){ */
  /*   for (j=0; j<D; j++){ */
  /*     printf("%f, ", data[j][i]); */
  /*   } */
  /*   printf("\n"); */
  /* } */

  // Phase space:
  //              nDims = D (diff order + 1, the +1 for the original series)
  //              base = number of bins (the No of possible "events" in each dimension)

  // Create the base Vector
  status = baseVector(D, nBins, &baseVec);
  //printf("BaseVector : ");
  //for(i=0; i<D; i++){ printf("%d, ",baseVec[i]); } printf("\n");

  // Convert Data Matrix to Symbolic, State Matrix
  status = stateMatrix(data, D, N, nBins, &symb, &binVals, &limits);

  /* for (i=0; i<N; i++){ */
  /*   for (j=0; j<D; j++){ */
  /*     printf("%d, ", symb[j][i]); */
  /*   } */
  /*   printf("\n"); */
  /* } */

  /* printf("BinVals: "); */
  /* for (i=0; i<nBins; i++){ printf("%f, ", binVals[i]); } printf("\n"); */

  /* printf("Series limits: \n"); */
  /* for (j=0; j<D; j++){ printf("%f to %f (%f)\n", limits[j][0], limits[j][1], limits[j][2]); } */

  nStates = transitionMatrix(symb, D, N, nBins, baseVec, &trans);
  printf("nStates = %d\n", nStates);

  /* for (i=0; i<nStates; i++){ */
  /*   for (j=0; j<nBins; j++){ */
  /*     printf("%d, ", trans[i][j]); */
  /*   } */
  /*   printf("\n"); */
  /* } */

  status = smooth2d(trans, D, nBins, nStates);
  printf("Interpolated Transition Matrix:\n");
  /* for (i=0; i<nStates; i++){ */
  /*   for (j=0; j<nBins; j++){ */
  /*     printf("%d, ", trans[i][j]); */
  /*   } */
  /*   printf("\n\n"); */
  /* } */
  
  status = probabilityMatrix(trans, nStates, nBins, &transProbMat);
  printf("Transition Probability Matrix. \n");
  /* for (i=0; i<nStates; i++){ */
  /*   for (j=0; j<nBins; j++){ */
  /*     printf("%.2f, ", transProbMat[i][j]); */
  /*   } */
  /*   printf("\n"); */
  /* } */

  // set initial state for prediction module
  initVec = malloc(D * sizeof(double));
  for (j=0; j<D; j++){ initVec[j] = data[j][N-1]; }
  status = prediction(transProbMat, nStates, D, nBins, binVals,
		      nPred, nScen, initVec, baseVec, limits, &output);

  // print results to file
  printf("Writing results to file.\n");
  fid = fopen("prediction.txt", "w");
  for (j=0; j<nPred; j++){
    for (i=0; i<nScen; i++){
      fprintf(fid, "%f, ", output[j][i]);
    }
    fprintf(fid, "\r\n");
  }
  fclose(fid);
  
  free(series);
  free(diff_series);
  for (j=0; j<D; j++){
    free(data[j]);
    free(limits[j]);
  }
  free(data);
  free(limits);

  free(binVals);
  free(initState);
  free(baseVec);
  free(initVec);

  for (j=0; j<nStates; j++){
    free(transProbMat[j]);
    free(symb[j]);
    free(trans[j]);
  }
  free(transProbMat);
  free(symb);
  free(trans);
  
  return 0;
}
