#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int i;
int state;

int stateId(int *vector, int *baseVector, int length) {
  state = 0;
  
  for(i=0; i<length; i++){
    state += vector[i] * baseVector[i];
  }
 
  return state;
}
