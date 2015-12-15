// function definitions file

int readFile(char filename[], double **data, int *length);

int diff(double *data, int length, double **diff);

int baseVector(int length, int base, int **multipliers);

int stateMatrix(double **inMatrix, int nRows, int nCols, int nBins, int ***outMatrix, double **binVals, double ***lims);

int transitionMatrix(int **stateMatrix, int nRows, int nCols, int nBins, int *baseVec, int ***transMatrix);

int smooth2d(int **transMatrix, int nRows, int nBins, int nStates);

int probabilityMatrix(int **transMatrix, int nStates, int nBins, double ***probMatrix);

double **prediction(double **probMatrix, int nStates, int nRows, int nBins, double *binVals, int N, int noScen, double *initVec, int *baseVec, double **lims, double ***predMatrix);

int binVal(double val, double min, double max, double d, int nBins);

int minmax(double *data, int length, double *min, double *max);

int smooth1d(double *vec, int length);

int stateId(int *vector, int *baseVector, int length);

