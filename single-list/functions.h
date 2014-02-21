/********************************************
      FUNZIONI PER MATRICE A DUE INDICI
********************************************/

#define INPUT_FILE "input.txt"
#define OUTPUT_FILE "output"
//INPUT_FILE E OUTPUT_FILE sono i file dove vengono salvate le matrici

typedef struct elemlist
        {
        float info;
        struct elemlist * prossimo;
        } elemento_lista;
typedef elemento_lista * lista_di_elementi;

typedef struct {
        int rows;
        int cols;
        lista_di_elementi values;
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

// GUI
//funzioni necessarie all'utente in fase di esecuzione
int print(Matrix);
int read(Matrix*);

// IO functions
int readFromBinFile(Matrix*, int matrixToBeRead, char * file);
int readFromTxtFile(Matrix*, int matrixToBeRead, char * file);
    /* matrixToBeRead(in read_da_file_XXX) indica l'indice della matrix da leggere da file
       l'indice va da 0 a n-1 */
int writeToBinFile(Matrix*, char * file);
int writeToTxtFile(Matrix*, char * file);
int emptyFile(char * file);

