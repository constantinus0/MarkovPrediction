#include <stdio.h>
#include <stdlib.h>


int readFile(char filename[], double **data, int *length) {

  FILE *fid = fopen(filename, "r");
  double x;
  char ch, *buffer;
  int i;

  int MAX_N = 1000;

  if (fid == NULL ) {
      perror("Error while opening the file.\n");
      return -1;
  }

  buffer = (char *) malloc(MAX_N);

  length[0] = 0;
  while (fgets(buffer, MAX_N, fid) != NULL ) {
    length[0]++;
  }

  //  printf("(in)Number of lines: %d\n", length[0]);

  rewind(fid);

  *data = malloc(length[0] * sizeof(double));

  for (i=0; i < length[0]; i++) {
    fscanf(fid, "%lf", &data[0][i]);
   }

  fclose(fid);
  free(buffer);
  return 0;
}
