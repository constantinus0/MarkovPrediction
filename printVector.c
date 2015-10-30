#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int i;
double dbase; // the base in double type
double buff;
long int* multipliers;

long int* baseVector(int length, int base){
  state = 0; // initial value
  dbase = (double) base;
  multipliers = (long int *) malloc(length);
  for(i=0; i<length; i++){
    buff = pow(dbase, ((double) i));
    multipliers[i] = (long) buff;
  }
 
  return multipliers;
}
