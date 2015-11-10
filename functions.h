// function definitions file

int readFile(char filename[], double **data, int *length);
int diff(double *data, int length, double **diff);
int minmax(double *data, int length, double *min, double *max);
int baseVector(int length, int base, int **multipliers);
int stateId(int *vector, int *baseVector, int length);
int stateMatrix(double **inMatrix, int nRows, int nCols, int nBins, int ***outMatrix, double *binVals);
int smooth1d(double *vec, int length);
int transitionMatrix(int **stateMatrix, int nRows, int nCols, int nBins, int ***transMatrix);
int probabilityMatrix(int **transMatrix, int nStates, int nBins, double ***probMatrix);

