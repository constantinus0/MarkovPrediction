#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int i;
long int state;

long int stateId(int *vector, long int *baseVector, int length) {
  state = 0;
  
  for(i=0; i<length; i++){
    state += vector[i] * baseVector[i];
  }
 
  return state;
}
