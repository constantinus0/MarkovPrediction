#include <stdio.h>
#include <stdlib.h>

int status, i, j, k,  nStates, *stateVec;
long int prevId, nextId;
int sum;
time_t t;
double prob;

int prediction(double **probMatrix, int nStates, int nBins, double *binVals,
	       int N, int *initState, int *baseVec){

  srand((unsigned) time(&t));

  for (k=0; k<N; k++){
    prevId = stateId(initState, baseVec, nBins);

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
      
    }

  }

  return 0;
}
