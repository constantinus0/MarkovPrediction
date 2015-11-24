#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int status, i, j, k,  nStates, *stateVec;
long int prevId, nextId;
int sum;

int probabilityMatrix(int **transMatrix, int nStates, int nBins,
		      double ***probMatrix){

  *probMatrix = malloc(nStates * sizeof(double*));
  for (i=0; i<nStates; i++){ probMatrix[0][i] = malloc(nBins * sizeof(double)); }

  for (i=0; i<nStates; i++){
   sum = 0;
    for (j=0; j<nBins; j++){
     sum += transMatrix[i][j];
    }

    for (j=0; j<nBins; j++) {
      if (sum > 0){
        probMatrix[0][i][j] = (double) transMatrix[i][j] / ((double) sum);
      }
      else{
        printf("No data for state id: %d\n", i);
	probMatrix[0][i][j] = 0;
      }
    }

    // convert to cumulative probability matrix
    for (j=1; j<nBins; j++) {
      probMatrix[0][i][j] = probMatrix[0][i][j-1] + probMatrix[0][i][j];
    }
    
  }

  

  return 0;
}
