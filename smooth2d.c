#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int iR, iB, iS, i;
int *changeStatus;
int contFlag;
int nN, *sum, neighborState;

int smooth2d(int **transMatrix, int nRows, int nBins, int nStates){
  // allocate "sum" buffer (will keep the sum of all transition counts for all bins)
  sum = malloc(nBins * sizeof(int));

  // create boolean matrix to mark which points will have to be interpolated and which to remain constant
  changeStatus = malloc(nStates * sizeof(int));
  for (iS=0; iS<nStates; iS++){
    sum[0] = 0;
    for (iB=0; iB<nBins; iB++){
      sum[0] += transMatrix[iS][iB];
    }

    if (sum[0] > 0){
      // values exist - don't change this state
      changeStatus[iS] = 0;
    }
    else {
      changeStatus[iS] = 1;
    }
  }

  printf("Change Status Vector: \n");
  for (iS=0; iS<nStates; iS++){ printf("%d, ", changeStatus[iS]); } printf("\n");
  
  printf("Process begins...\n");
  // begin process (flag = true)
  contFlag = 10;
  while (contFlag > 0) {
    for (iS=0; iS<nStates; iS++){ 
	if (changeStatus[iS] == 1){
	  // find neighbors and caclulate their average
	  nN = 0;
	  for(i=0; i<nBins; i++) { sum[i] = 0; }
	  
	  for (iR=0; iR<nRows; iR++){
	    // for each dimension two neighbors might exist (+1 & -1)
	    // check +1 neighbor
	    neighborState = iS + (int) pow(nBins, iR);
	    printf("+1 Neighbor of %d is %d\n", iS, neighborState);
	    if ((neighborState > 0) && (neighborState < nStates)){
	      for (i=0; i<nBins; i++){
		sum[i] += transMatrix[neighborState][i];
	      }
	    }
	    else{
	      // do nothing! Essentially, it assumes 0 boundary conditions so it justs adds 0 to the current sum.
	    }
	    nN++;
	     
	    // check -1 neighbor
	    neighborState = iS - (int) pow(nBins, iR);
	    printf("-1 Neighbor of %d is %d\n", iS, neighborState);
	    if ((neighborState > 0) && (neighborState < nStates)){
	      for (i=0; i<nBins; i++){
		sum[i] += transMatrix[neighborState][i];
	      }
	    }
	    else{
	      // do nothing! Essentially, it assumes 0 boundary conditions so it justs adds 0 to the current sum.
	    }
	    nN++;
	  }

	  // assign to current grid point the average value of its neighbor points
          for (i=0; i<nBins; i++){
	    transMatrix[iS][i] = (int) round((float) sum[i]/((float) nN));
	  }
	  
	}
	printf("State: %d\n", iS);
    }
    contFlag--;
    printf("loop completed!\n");
  }

    
  return 0;
}
