#include <stdio.h>
#include <stdlib.h>
#include "operations.h"


int main(int argc, char *argv[])
{
    Matrix matrix1, matrix2, matrix3;
    float scalarProductValue = 15.4;
    int i;

    printf("%d", readFromTxtFile(&matrix1, 0, INPUT_FILE));
    stampa(matrix1);
    puts("Press enter to continue");
    getchar();
    i=0;
    puts("PRINT INPUT");
    while(!readFromTxtFile(&matrix1, i++, INPUT_FILE))
    {
        stampa(matrix1);
    }
    puts("Press enter to continue");
    getchar();

    i=0;
    puts("PRINT OUTPUT");
    while(!readFromBinFile(&matrix1, i++, OUTPUT_FILE))
    {
        stampa(matrix1);
    }
    puts("Press enter to continue");
    getchar();

    emptyFile(OUTPUT_FILE);
    i=0;
    puts("COPY INPUT MATRICES TO OUTPUT");
    while(!readFromTxtFile(&matrix1, i, INPUT_FILE))
    {
        printError(writeToBinFile(&matrix1, OUTPUT_FILE));
        printError(readFromBinFile(&matrix2, i++, OUTPUT_FILE));
        stampa(matrix2);
    }
    puts("Press enter to continue");
    getchar();
    emptyFile(OUTPUT_FILE);

    //SOMMA
    puts("\nOPERATIONS\nSUM matrix 0 + matrix 1");
    printError(readFromTxtFile(&matrix1, 0, INPUT_FILE));
    printError(readFromTxtFile(&matrix2, 1, INPUT_FILE));
    printError(sum(matrix1, matrix2, &matrix3));
    printError(writeToBinFile(&matrix3, OUTPUT_FILE));
    printError(readFromBinFile(&matrix3, 0, OUTPUT_FILE));
    stampa(matrix3);

    //DIFFERENZA
    puts("DIFFERENCE matrix 2 - matrix 3");
    printError(readFromTxtFile(&matrix1, 2, INPUT_FILE));
    printError(readFromTxtFile(&matrix2, 3, INPUT_FILE));
    printError(difference(matrix1, matrix2, &matrix3));
    printError(writeToBinFile(&matrix3, OUTPUT_FILE));
    printError(readFromBinFile(&matrix3, 1, OUTPUT_FILE));
    stampa(matrix3);

    //PRODOTTO
    puts("PRODUCT matrix 4 X matrix 5");
    printError(readFromTxtFile(&matrix1, 4, INPUT_FILE));
    printError(readFromTxtFile(&matrix2, 5, INPUT_FILE));
    printError(vectorialProduct(matrix1, matrix2, &matrix3));
    printError(writeToBinFile(&matrix3, OUTPUT_FILE));
    printError(readFromBinFile(&matrix3, 2, OUTPUT_FILE));
    stampa(matrix3);

    //TRASPOSTA
    puts("TRANSPOSED matrix 6");
    printError(readFromTxtFile(&matrix1, 6, INPUT_FILE));
    printError(transposed(matrix1, &matrix3));
    printError(writeToBinFile(&matrix3, OUTPUT_FILE));
    printError(readFromBinFile(&matrix3, 3, OUTPUT_FILE));
    stampa(matrix3);

    //PRODOTTO SCALARE
    puts("SCALAR PRODUCT matrix 7 * 15.4");
    printError(readFromTxtFile(&matrix1, 7, INPUT_FILE));
    printError(scalarProduct(matrix1, scalarProductValue, &matrix3));
    printError(writeToBinFile(&matrix3, OUTPUT_FILE));
    printError(readFromBinFile(&matrix3, 4, OUTPUT_FILE));
    stampa(matrix3);

    puts("Press enter to continue");
    getchar();
    return 0;
}
