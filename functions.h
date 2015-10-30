// function definitions file
// declerations need a ';' at the end !

int readFile(char filename[], double **data, int *length);
int diff(double *data, int length, double **diff);
int minmax(double *data, int length, double *min, double *max);
long int* baseVector(int length, int base);
long int stateId(int* vector, int length, int base);
int stateMatrix(double **inMatrix, int nRows, int nCols, int nBins, int ***outMatrix, double *binVals);
