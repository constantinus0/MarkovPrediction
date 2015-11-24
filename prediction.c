#include <stdio.h>
#include <stdlib.h>

int status, i, j, k, s,  nStates, *stateVec;
long int prevId, nextId;
int sum;
time_t t;
double prob, *vec;

double **prediction(double **probMatrix, int nStates, int nRows, int nBins, double *binVals, int N, int noScen, double *initVec, int *baseVec, double **lims, double ***predMatrix){

  srand((unsigned) time(&t));

  stateVec = malloc(nRows * sizeof(int));
  
  vec = malloc(nRows * sizeof(double));

  // output matrix. Rows: future positions, Cols: different scenarios
  predMatrix[0] = malloc(N * sizeof(double*));
  for (k=0; k<N; k++){ predMatrix[0][k] = malloc(noScen * sizeof(double)); }

  for(s=0; s<noScen; s++){
    // initialize "vec" to "initVec"
    for (j=0; j<nRows; j++){ vec[j] = initVec[j]; }

    //printf("Pred: ");
    
    for (k=0; k<N; k++){
      // get state vector (in bin ids)
      for (j=0; j<nRows; j++){
	stateVec[j] = binVal(vec[j], lims[j][0], lims[j][1], lims[j][2], nBins);
      }

      // get state Id number
      prevId = stateId(stateVec, baseVec, nRows);

      // get random number [0, 1]
      prob = (double) rand() / ((double) RAND_MAX);

      nextId = -1;
      j = 0;
      while (j<nBins){
	if (prob <= probMatrix[prevId][j]){
	  nextId = j;
	  j = nBins; // exit clause
	}
	else{
	  // cont.
	  j++;
	}
      }

      if (nextId < 0){
	printf("\n***Warning! Current state could not be resolved! Consider changing the processing parameters!***\n\n");
	// couldn't find a match
      }
      else{
	// get next val for max order diff.
	vec[nRows-1] = binVals[nextId];

	for (j=nRows-2; j>=0; j--){
	  vec[j] = vec[j] + vec[j+1];
	}
      }

      // printf("%f, ", vec[0]);
      predMatrix[0][k][s] = vec[0];
    }
    // printf("\n");
  }

  return 0;
}
