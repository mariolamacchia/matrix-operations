/********************************************
                MATRIX OPERATIONS
********************************************/

#include "operations.h"
#include <math.h>
#include <stdio.h>

int sum(Matrix matrix1, Matrix matrix2, Matrix * result)
{
    int i, j;
    float matrixValue1, matrixValue2;

    if 
        (
         readRows(matrix1) == readRows(matrix2) &&
         readColumns(matrix1)==readColumns(matrix2)
        )
        {
            initMatrix(result, readRows(matrix1), readColumns(matrix2));
            for(i = 0; i < readRows(*result); i++)
            {
                for(j = 0; j < readColumns(*result); j++)
                {
                    readMatrix(matrix1, i, j, &matrixValue1);
                    readMatrix(matrix2, i, j, &matrixValue2);
                    writeMatrix(result, i, j, matrixValue1 + matrixValue2);
                }
            }
            return 0;
        }
    else return 2;
}

int difference(Matrix matrix1, Matrix matrix2, Matrix * result)
{
    int i, j;
    float matrixValue1, matrixValue2;

    if 
        (
         readRows(matrix1) == readRows(matrix2) &&
         readColumns(matrix1)==readColumns(matrix2)
        )
        {
            scalarProduct(matrix2, -1, &matrix2);
            initMatrix(result, readRows(matrix1), readColumns(matrix2));
            for(i = 0; i < readRows(*result); i++)
            {
                for(j = 0; j < readColumns(*result); j++)
                {
                    readMatrix(matrix1, i, j, &matrixValue1);
                    readMatrix(matrix2, i, j, &matrixValue2);
                    writeMatrix(result, i, j, matrixValue1 + matrixValue2);
                }
            }
            return 0;
        }

    else return 2;
}

int scalarProduct(Matrix matrix, float value, Matrix * result)
{
    int i, j;
    float matrixValue;

    initMatrix(result, readRows(matrix), readColumns(matrix));

    for(i = 0;  i < readRows(*result); i++)
    {
        for(j = 0; j < readColumns(*result); j++)
        {
            readMatrix(matrix, i, j, &matrixValue);
            writeMatrix(result, i, j, matrixValue * value);
        }
    }

    return 0;
}

int transposed(Matrix matrix, Matrix * result)
{
    int i, j;
    float matrixValue;

    initMatrix(result, readColumns(matrix), readRows(matrix));

    for(i = 0; i < readRows(*result); i++)
    {
        for(j = 0; j < readColumns(*result); j++)
        {
            readMatrix(matrix, j, i, &matrixValue);
            writeMatrix(result, i, j, matrixValue);
        }
    }

    return 0;
}

int vectorialProduct(Matrix matrix1, Matrix matrix2, Matrix * result)
{
    int i, j, h;
    float value, matrixValue1, matrixValue2;

    if (readColumns(matrix1) == readRows(matrix2))
    {
        initMatrix(result, readRows(matrix1), readColumns(matrix2));

        for(i = 0; i < readRows(*result); i++)
        {
            for(j = 0; j < readColumns(*result); j++)
            {
                value = 0;
                for(h = 0; h < readColumns(matrix1); h++)
                {
                    readMatrix(matrix1, i, h, &matrixValue1);
                    readMatrix(matrix2, h, j, &matrixValue2);
                    value += matrixValue1 * matrixValue2;
                }
                writeMatrix(result, i, j, value);
            }
        }
        return 0;
    }
    else return 2;
}

void printError(int error)
{
    /*
     *   0: OK
     *   1: Non-existent file
     *   2: Invalid matrices sizes
     *   3: Eof found before expecting
     *   4: Error while reading matrix from file
     */
    switch(error)
    {

        case 1:
            puts("Error while reading file: non-existent file!");
            break;
        case 2:
            puts("Error while calculating: matrices' size is not suitable for this kind of operation!");
            break;
        case 3:
            puts("Error while reading file: file is too short. Check if file contains matrix.");
            break;
        case 4:
            puts("Error while reading file: indicated matrix is not readable! File may be corrupt.");
            break;
        case 5:
            puts("Error while writing matrix: row and col's number must be non-zero!");
            break;
        case 6:
            puts("Error while reading matrix: requested row or column is non-existent!");
            break;
        case 7:
            puts("Error while writing matrix: requested row or column is non-existent!");
    }
}
