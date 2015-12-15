#include <stdio.h>
#include <stdlib.h>

int status, i, j, targetBin, *binValCnt;
double min, max, d, *binValSum;

int stateMatrix(double **inMatrix, int nRows, int nCols, int nBins,
		int ***outMatrix, double **binVals, double ***lims) {

  *binVals = malloc(nBins * sizeof(double));
  binValCnt = malloc(nBins * sizeof(int));
  binValSum = malloc(nBins * sizeof(double));
  for (i=0; i<nBins; i++){
    binValCnt[i] = 0;
    binValSum[i] = 0;
  }
  
  *outMatrix = malloc(nRows * sizeof(int*));
  for (j=0; j<nRows; j++){ outMatrix[0][j] = malloc(nCols * sizeof(int)); }

  *lims = malloc(nRows * sizeof(double*));
  for (j=0; j<nRows; j++){ lims[0][j] = malloc(3 * sizeof(double)); }
  
  for (j=0; j<nRows; j++){
    status = minmax(inMatrix[j], nCols, &min, &max);
    d = max - min;
    //printf("min = %f, max = %f, dx = %f\n", min, max, d);

    lims[0][j][0] = min;
    lims[0][j][1] = max;
    lims[0][j][2] = d;

    // Bins will take values from 0 to nBins-1
    
    //Provision for when min == max! Assign all values to the same bin (the central one)
    if (min == max){
      targetBin = nBins/2;
      for (i=0; i<nCols; i++){
	outMatrix[0][j][i] = targetBin;
      }

      if (j == nRows - 1){
	binValSum[ targetBin ] = max;
	binValCnt[ targetBin ] = 1;
      }
      
    }
    else {
    // Cast values to the appropriate bin. Because the last bin will only contain the
    // values that are exactly equal to max, do the first run for nBins+1 bins, with
    // id numbers from 0 to nBins and then change all occurences of the nBins value
    // to nBins-1, so that there are eventually only values from 0 to nBins-1.
      for (i=0; i<nCols; i++){
	outMatrix[0][j][i] = (int) (((inMatrix[j][i] - min)/d)*nBins);
	if (outMatrix[0][j][i] == nBins) {outMatrix[0][j][i] = nBins - 1;}

      	// if the current series is the highest order difference series (last j), read its
	// values to calculate the average bin values
	if (j == nRows - 1){
	  binValSum[ outMatrix[0][j][i] ] += inMatrix[j][i];
	  binValCnt[ outMatrix[0][j][i] ] += 1;
	}
      }
    }
  }

  // calculate average bin values
  for (i=0; i<nBins; i++){
    if (binValCnt[i] > 0){
      binVals[0][i] = binValSum[i] / binValCnt[i];
    }
    else{
      // FILL VALUE: -1.0E+10
      binVals[0][i] = -1.0E+10;
    }
  }

  // printf("unsmoothed: "); for (i=0; i<nBins; i++) { printf("%f, ", binVals[0][i]); } printf("\n");
  status = smooth1d(binVals[0], nBins);
  // printf("smoothed: "); for (i=0; i<nBins; i++) { printf("%f, ", binVals[0][i]); } printf("\n");
  
  return 0;
}
