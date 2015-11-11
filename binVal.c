#include <stdio.h>
#include <stdlib.h>

int i, targetBin;
double min, max, d, *binValSum;

int binVal(double val, double min, double max, double d, int nBins){

  if (min == max){
      targetBin = nBins/2;
  }
  else{
    targetBin = (int) (((val - min)/d)*nBins);
  }

  // if targetBin is out of bounds, assign to the closest valid bin (first or last)
  if (targetBin < 0) { targetBin = 0; }
  else if (targetBin >= nBins) { targetBin = nBins - 1; }
  
  return targetBin;
}
