/********************************************
            OPERAZIONI TRA MATRICI
********************************************/
#include "operations.h"
#include <math.h>
#include <stdio.h>

int sum(Matrix matrix1, Matrix matrix2, Matrix * result)
{
    int i,j;
    float matrixValue1, matrixValue2;

    if ((readRows(matrix1)==readRows(matrix2))&&(readColumns(matrix1)==readColumns(matrix2)))
    {
    initMatrix(result,readRows(matrix1),readColumns(matrix2));
        for(i=0; i<readRows(*result); i++)
            for(j=0; j<readColumns(*result); j++)
            {
                readMatrix(matrix1, i, j, &matrixValue1);
                readMatrix(matrix2, i, j, &matrixValue2);
                writeMatrix(result,i,j,matrixValue1+matrixValue2);
            }
    return 0;
    }
    else return 2;
}

int difference(Matrix matrix1, Matrix matrix2, Matrix * result)
{
    int i,j;
    float matrixValue1, matrixValue2;

    if ((readRows(matrix1)==readRows(matrix2))&&(readColumns(matrix1)==readColumns(matrix2)))
    {
    scalarProduct(matrix2,-1,&matrix2);
    initMatrix(result,readRows(matrix1),readColumns(matrix2));
        for(i=0; i<readRows(*result); i++)
            for(j=0; j<readColumns(*result); j++)
            {
                readMatrix(matrix1, i, j, &matrixValue1);
                readMatrix(matrix2, i, j, &matrixValue2);
                writeMatrix(result,i,j,matrixValue1+matrixValue2);
            }
    return 0;
    }

    else return 2;
}

int scalarProduct(Matrix matrix, float value, Matrix * result)
{
        int i,j;
        float matrixValue;

        initMatrix(result, readRows(matrix), readColumns(matrix));
        for(i=0; i<readRows(*result); i++)
            for(j=0; j<readColumns(*result); j++)
            {
                readMatrix(matrix, i, j, &matrixValue);
                writeMatrix(result, i, j, matrixValue * value);
            }
        return 0;
}

int transposed(Matrix matrix, Matrix * result)
{
        int i,j;
        float matrixValue;

        initMatrix(result,readColumns(matrix),readRows(matrix));
        for(i=0; i<readRows(*result); i++)
            for(j=0; j<readColumns(*result); j++)
            {
                readMatrix(matrix, j, i, &matrixValue);
                writeMatrix(result, i, j, matrixValue);
            }
        return 0;
}

int vectorialProduct(Matrix matrix1, Matrix matrix2, Matrix * result)
{
        int i,j,h;
        float value, matrixValue1, matrixValue2;

        if (readColumns(matrix1)==readRows(matrix2))
        {
            initMatrix(result, readRows(matrix1), readColumns(matrix2));

            for(i=0; i<readRows(*result); i++)
                for(j=0; j<readColumns(*result); j++)
                {
                    value=0;
                    for(h=0; h<readColumns(matrix1); h++)
                    {
                        readMatrix(matrix1, i, h, &matrixValue1);
                        readMatrix(matrix2, h, j, &matrixValue2);
                        value += matrixValue1 * matrixValue2;
                    }
                    writeMatrix(result, i, j, value);
                }
            return 0;
        }
        else return 2;
}

void printError(int error)
{
     /*
       0: OK
       1: File inesistente
       2: Grandezze matrici inadatte all'operazione
       3: Raggiungimento eof prima del previsto
       4: Errore durante la lettura della matrix dal file
     */
     switch(error)
     {

            case 1:
                 puts("Errore durante la lettura del file: file inesistente!");
                 break;
            case 2:
                 puts("Errore durante il calcolo: le matrici non hanno le dimensioni adatte per eseguire l'operaizone!");
                 break;
            case 3:
                 puts("Errore durante la lettura del file: il file e' troppo corto. Si controlli che la matrix esista nel file.");
                 break;
            case 4:
                 puts("Errore durante la lettura del file: la matrix indicata non e' readbile! Controllare che il file non sia danneggiato.");
                 break;
            case 5:
                 puts("Errore durante la scrittura della matrix: il numero di rows e cols dev'essere maggiore di zero!");
                 break;
            case 6:
                 puts("Errore durante la lettura della matrix: la row o la col richiesta non esistono!");
                 break;
            case 7:
                 puts("Errore durante la scrittura della matrix: la row o la col richiesta non esistono!");
     }
}
