/********************************************
      FUNZIONI PER MATRICE A DUE INDICI
********************************************/

// DIM_X is the max dimension rows can have
#define DIM_X 100
// DIM_Y is the max dimension cols can have
#define DIM_Y 100
// Input file is txt file where input matrixs are stored
#define INPUT_FILE "input.txt"
// Output file is bin file where output matrixs are stored
#define OUTPUT_FILE "output.bin"

typedef struct {
        int rows;
        int cols;
        float values[DIM_X * DIM_Y];
        } Matrix;

// Initialize
int initMatrix(Matrix*, int rows, int cols);

// Write and read sizes
int writeRows(Matrix*, int);
int writeColumns(Matrix*, int);
int readRows(Matrix);
int readColumns(Matrix);

// Write and read values
int writeMatrix(Matrix*, int row, int col, float value);
int readMatrix(Matrix, int row, int col, float * value);

// IO functions
int readFromBinFile(Matrix*, int matrixToBeRead, char * file);
int readFromTxtFile(Matrix*, int matrixToBeRead, char * file);
int writeToBinFile(Matrix*, char * file);
int writeToTxtFile(Matrix*, char * file);
int emptyFile(char * file);

// GUI
int stampa(Matrix);
int read(Matrix*);
