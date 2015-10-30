#include <stdio.h>
#include <stdlib.h>


int readFile(char filename[], double **data, int *length) {

  FILE *fid = fopen(filename, "r");
  double x;
  char ch;
  int i;

  if (fid == NULL ) {
      perror("Error while opening the file.\n");
      return -1;
  }

  length[0] = 0;
  while ( !feof(fid) ) {
      ch = fgetc(fid);
      if(ch == '\n')
      {
          length[0]++;
      }
  }

  //  printf("(in)Number of lines: %d\n", length[0]);

  rewind(fid);

  *data = (double *) malloc(length[0]);

  for (i=0; i < length[0]; i++) {
    fscanf(fid, "%lf\n", &data[0][i]);
   }

  fclose(fid);
  //  printf("(in) Complete!\n");
  return 0;
}
