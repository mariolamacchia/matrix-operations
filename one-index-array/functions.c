#include <stdio.h>
#include "functions.h"

// Write and read sizes
int writeRows(Matrix * matrix, int rows)
{
    if (rows <= 0)
        return 5;
    matrix->rows = rows;
    return 0;
}

int writeColumns(Matrix *matrix, int cols)
{
    if (cols <=0) return 5;
    matrix->cols = cols;
    return 0;
}

int readRows(Matrix matrix)
{
    return matrix.rows;
}

int readColumns(Matrix matrix)
{
    return matrix.cols;
}

// Initialize
int initMatrix(Matrix *matrix,int rows, int cols)
{
    if (rows <= 0 || cols <= 0)
        return 5;
    writeRows(matrix, rows);
    writeColumns(matrix, cols);
    return 0;
}

// Write and read values MATRICE
int writeMatrix(Matrix *matrix, int row, int col, float value)
{
    if
        (
            row < 0 ||
            row >= readRows(*matrix) ||
            col < 0 ||
            col >= readColumns(*matrix)
        )
        return 7;
    matrix->values[col*readRows(*matrix)+ row]=value;
    return 0;
}

int readMatrix(Matrix matrix, int row, int col, float * value)
{
    if
        (
            row < 0 ||
            row >= readRows(matrix) ||
            col < 0 ||
            col >= readColumns(matrix)
        )
        return 6;

    *value = matrix.values[col*readRows(matrix)+ row];
    return 0;
}

// GUI
int stampa(Matrix matrix)
{
    int i, j;
    float matrixValue;

    puts("--------");

    for(i=0; i<readRows(matrix); i++)
    {
        for(j=0; j<readColumns(matrix); j++)
        {
            readMatrix(matrix, i, j, &matrixValue);
            printf("%f ", matrixValue);
        }
        printf("\n");
    }

    puts("--------");

    return 0;
}

int read(Matrix *matrix)
{
    int i, j, rows, cols;
    float value;

    do
    {
        printf("Inserire numero rows: ");
        scanf("%d",&rows);
    }
    while((rows<=0)||(rows>DIM_X));

    do
    {
        printf("Inserire numero cols: ");
        scanf("%d",&cols);
    }
    while((cols<=0)||(cols>DIM_Y));

    initMatrix(matrix, rows, cols);

    for(i=0; i<readRows(*matrix); i++)
    {
        for(j=0; j<readColumns(*matrix); j++)
        {
            printf("Inserisci value(%d,%d): ", i, j);
            scanf("%f",&value);
            writeMatrix(matrix, i, j, value);
        }
    }

    return 0;
}

// IO functions
int readFromBinFile(Matrix * matrix, int matrixToBeRead, char * file)
{
    FILE * fp;

    if ((fp = fopen(file,"rb"))!=NULL)
    {
        //Si raggiunge la matrix da leggere
        fseek(fp,matrixToBeRead*sizeof(matrix),SEEK_CUR);
        //Se si è alla fine del file, la matrix non esiste
        if (feof(fp))
        {
            fclose(fp);
            return 3;
        }
        else
        {
            //Si legge la matrix e si controlla quanti byte sono stati letti
            if (fread(matrix,1,sizeof(matrix),fp) == sizeof(matrix))
            {
                fclose(fp);
                return 0;
            }
            else
            {
                /*
                   Se sono stati letti un numero di byte inferiori a quanto
                   ci si aspettava, è stato riscontrato un errore nella lettura
                   */
                fclose(fp);
                return 4;
            }
        }
    }
    else return 1;
}

int writeToBinFile(Matrix * matrix, char * file)
{
    FILE * fp;

    if ((fp = fopen(file,"ab"))!=NULL)
    {
        fwrite(matrix,sizeof(matrix),1,fp);
        fclose(fp);
        return 0;
    }
    else return 1;
}

/*
   I file txt contenenti matrici hanno una matrix per rigo. Ogni rigo
   è composto da due interi che definiscono rows e cols e da rows*cols float
   che definiscono i values
   */
int readFromTxtFile(Matrix * matrix, int matrixToBeRead, char * file)
{
    FILE * fp;
    int i, j, rows, cols, errore_fine_file=0,
        errore_inizializzazione=0;
    char c;
    float value;

    if ((fp=fopen(file, "r"))!=NULL)
    {
        i=0;
        while(i< matrixToBeRead && !(feof(fp)) )
        {
            if ((c=getc(fp))=='\n') i++;
            /* Cerca il simbolo new line tante volte quante sono le matrici
               da scorrere prima di incontrare quella desiderata */
        }
        if (!feof(fp))
        {
            fscanf(fp,"%d%d",&rows,&cols);
            if (!(errore_inizializzazione=initMatrix(matrix,rows,cols)))
            {
                for(i=0;i<rows && !errore_fine_file;i++)
                    for(j=0; j<cols && !errore_fine_file; j++)
                    {
                        if (feof(fp)) errore_fine_file=1;
                        fscanf(fp,"%f",&value);
                        writeMatrix(matrix,i,j,value);
                    }

                //Si controlla se si è raggiunta la fine del file
                if (errore_fine_file)
                {
                    return 4;
                }
                else
                {
                    /*
                       Se non si è raggiunta la fine del file si controlla comunque
                       il carattere successivo all'ultimo dato letto. Se non è un newline
                       o se non finisce il file prima di trovarne uno, c'è un errore
                       */
                    do c = getc(fp);
                    while(c==' ' &&!feof(fp));
                    if (c != '\n' && !feof(fp)) return 4;
                    return 0;
                }
            }
            else
            {
                return errore_inizializzazione;
            }

        }
        else return 3;
    }
    else
    {
        return 1;
    }
}

int writeToTxtFile(Matrix * matrix, char * file)
{
    FILE * fp;
    int i,j;
    float matrixValue;

    if ((fp = fopen(file,"a"))!=NULL)
    {
        fprintf(fp,"\n%d %d ", readRows(*matrix), readColumns(*matrix));
        for(i=0; i<readRows(*matrix);i++)
            for(j=0; j<readColumns(*matrix);j++)
            {
                readMatrix(*matrix, i, j, &matrixValue);
                fprintf(fp,"%f ", matrixValue);
            }
        fprintf(fp,"\n");

        fclose(fp);
        return 0;
    }
    else return 1;
}

int emptyFile(char * file)
{
    FILE * fp;

    if ((fp=fopen(file, "w"))==NULL) return 1;
    fclose(fp);
    return 0;
}
