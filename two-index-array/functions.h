/********************************************
      FUNZIONI PER MATRICE A DUE INDICI
********************************************/

// DIM_X is the max row number of the matrix
#define DIM_X 100
// DIM_X is the max col number of the matrix
#define DIM_Y 100
// INPUT_FILE is the txt input file
#define INPUT_FILE "input.txt"
// OUTPUT_FILE is the binary output file
#define OUTPUT_FILE "output.bin"

typedef struct {
        int rows;
        int cols;
        float values[DIM_X][DIM_Y];
        } Matrix;

//Initialize
int initMatrix(Matrix*,int rows, int cols);

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
//funzioni necessarie all'utente in fase di esecuzione
int print(Matrix);
int read(Matrix*);
