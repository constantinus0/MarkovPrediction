#include <stdio.h>
#include <stdlib.h>

int status, i, j, k,  nStates, *stateVec;
long int prevId, nextId;
int sum;
time_t t;
double prob;

int prediction(double **probMatrix, int nStates, int nRows, int nBins, double *binVals,
	       int N, double *initVec, int *baseVec, double **lims){

  srand((unsigned) time(&t));

  stateVec = malloc(nRows * sizeof(int));
  
  for (k=0; k<N; k++){

    // get state vector (in bin ids)
    for (j=0; j<nRows; j++){
      stateVec[j] = binVal(initVec[j], lims[j][0], lims[j][1], lims[j][2], nBins);
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
      // couldn't find a match
    }
    else{
      // get next val for max order diff.
      initVec[nRows-1] = binVals[nextId];
      
      for (j=nRows-2; j>=0; j--){
	initVec[j] = initVec[j] + initVec[j+1];
      }
    }
    
    printf("Next Val: %f\n", initVec[0]);
  }

  return 0;
}
