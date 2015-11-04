#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int i, nonNaN, status;
double *rel_diff, max_rel_diff, limit, *prev, avg, buff;
int *change_status;

int smooth1d(double *vec, int length) {

  // set change_status vector (1 for true => value to be smoothed, or 0 otherwise)
  nonNaN = 0;
  change_status = malloc(length * sizeof(int));
  for (i=0; i<length; i++){
    if (vec[i] > -0.9E+10){
      change_status[i] = 0;
      nonNaN += 1;
    }
    else {
      change_status[i] = 1;
    }
  }

  // proceed only if there is at least one value to be changed
  if (nonNaN > 0) {
    // buffer for relative differences (prev vs current vector)
    rel_diff = malloc(length * sizeof(double));

    // calculate the average of non-NaN values, to be used as initial condition
    avg = 0;
    for (i=0; i<length; i++){
      rel_diff[i] = 0;
      avg += vec[i]*(1 - change_status[i]);
    }
    avg = avg / nonNaN;
    printf("Avg of nonNaN vals = %f\n", avg);
    
    // set prev vector to current values. Prev vector will have two extra values, one
    // at the beginning and one at the end, set to 0 (boundary conditions of the
    // laplacian smoothing operation)
    prev = malloc((length+2) * sizeof(double));
    for (i=1; i<length+1; i++){
      prev[i] = vec[i-1];
      if (prev[i] < -0.9E+10) { prev[i] = avg; }
    }
    prev[0] = 0;
    prev[length+1] = 0;
    
    limit = fabs(avg * 0.001);
    max_rel_diff = 2*limit; // random initial value just to start the process
    while (max_rel_diff > limit){
      
      for (i=0; i<length; i++) {
	if (change_status[i] == 1){
	  vec[i] = 0.5*(prev[i] + prev[i+2]);
	  rel_diff[i] = fabs(vec[i] - prev[i+1]);
	  printf("%f, ", rel_diff[i]);
	}
      }

      status = minmax(rel_diff, length, &buff, &max_rel_diff);
      printf("max diff = %f\n", max_rel_diff);

      for (i=1; i<length+1; i++){ prev[i] = vec[i-1]; }
    }

    free(prev);
    free(rel_diff);
  }
  return 0;
}
