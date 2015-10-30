#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int i;
double dbase; // the base in double type
double buff;

int baseVector(int length, int base, long int **multipliers){
  dbase = (double) base;
  *multipliers = (long int *) malloc(length);
  for(i=0; i<length; i++){
    buff = pow(dbase, ((double) i));
    multipliers[0][i] = (long int) buff;
  }
 
  return 0;
}
