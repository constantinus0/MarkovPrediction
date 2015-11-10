#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int status, i, j, k,  nStates, *stateVec;
long int prevId, nextId;
double x;

int transitionMatrix(int **stateMatrix, int nRows, int nCols, int nBins,
		     int *baseVec, int ***transMatrix){

  nStates = pow(nBins, nRows);
  
  // allocate and initialize Transition Matrix
  *transMatrix = malloc(nStates * sizeof(int*));
  for (j=0; j<nStates; j++){
    transMatrix[0][j] = malloc(nBins * sizeof(int));
    for (i=0; i<nBins; i++){
      transMatrix[0][j][i] = 0;
    }
  }

  // allocate stateVector buffer
  stateVec = malloc(nRows * sizeof(int));

  // parse input matrix and increment Transition Matrix (begin at D to ingore the first points that will have no difference values)
  k = nRows;
  while (k<(nCols-1)){
    // read current state
    for (j=0; j<nRows; j++){
      stateVec[j] = stateMatrix[j][k];
    }

    // get stateId from stateVector
    prevId = stateId(stateVec, baseVec, nRows);

    //  get next state id (max order difference)
    nextId = stateMatrix[nRows-1][k+1];

    // increment Transition Matrix
    transMatrix[0][prevId][nextId] += 1;

    k++;
  }

  free(stateVec);
  return nStates;
}
