#include <stdio.h>
#include <stdlib.h>

int status, i, j;
double min, max, d;

int stateMatrix(double **inMatrix, int nRows, int nCols, int nBins,
		int ***outMatrix, double *binVals){
  *outMatrix = malloc(nRows * sizeof(int*));
  for (j=0; j<nRows; j++){ outMatrix[0][j] = malloc(nCols * sizeof(int)); }
  
  for (j=0; j<nRows; j++){
    status = minmax(inMatrix[j], nCols, &min, &max);
    printf("min = %f, max = %f\n", min, max);

    // TO DO: Provision for when min == max!
    // Don't loop on values! Set the symb matrix by hand to a const val.
  }

  
  
  return 0;
}
