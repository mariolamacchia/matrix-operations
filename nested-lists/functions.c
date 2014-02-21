#include <stdio.h>
#include "functions.h"

// Write and read sizes
int writeRows(Matrix * matrix, int rows)
{
    if (rows <= 0) return 5;
    matrix->rows=rows;
    return 0;
}

int writeColumns(Matrix *matrix, int cols)
{
     if (cols <=0) return 5;
     matrix->cols=cols;
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

//Initialize
int initMatrix(Matrix *matrix,int rows, int cols)
{
        int i,j;
        lista_di_elementi lista_temp;
        elemento_lista * elemento;
        lista_lista * lista;

        if (rows <=0 || cols <=0) return 5;
        writeRows(matrix, rows);
        writeColumns(matrix, cols);
        matrix->values = NULL;          //Inizializza lista di liste
        for(i=0; i< rows; i++)
        {
            lista_temp = NULL;     //Inizializza lista di elementi temporale
            for(j=0;j<cols;j++)
            {
                //Inserisci cols elementi
                  elemento= malloc(sizeof(elemento_lista)) ;
                  elemento->prossimo=lista_temp;
                  lista_temp=elemento;
            }
            //Inserisci nodo alla lista di liste contenente la lista di elementi appena creata
            lista = malloc(sizeof(lista_lista));
            lista->prossimo = matrix->values;
            lista->info= lista_temp;
            matrix->values = lista;
        }

        return 0;
}

// Write and read values MATRICE
int writeMatrix(Matrix *matrix, int row, int col, float value)
{
     int i;
     lista_di_elementi punt_col;
     lista_di_liste punt_row;

     if (row >= readRows(*matrix) || col >= readColumns(*matrix)
         || row < 0 || col < 0) return 7;

     punt_row=matrix->values;
     for(i=0;i<row;i++)
     {
         punt_row=punt_row->prossimo;
     }
     punt_col = punt_row->info;
     for(i=0;i<col;i++)
     {
         punt_col = punt_col->prossimo;
     }

     punt_col->info = value;
     return 0;
}

int readMatrix(Matrix matrix, int row, int col, float * value)
{
     int i;
     lista_di_elementi punt_col;
     lista_di_liste punt_row;

     if (row >= readRows(matrix) || col >= readColumns(matrix)
         || row < 0 || col < 0) return 6;

     punt_row=matrix.values;
     for(i=0;i<row;i++)
     {
         punt_row=punt_row->prossimo;
     }
     punt_col = punt_row->info;
     for(i=0;i<col;i++)
     {
         punt_col = punt_col->prossimo;
     }

     *value = punt_col->info;
     return 0;
}

// GUI
int print(Matrix matrix)
{
     int i,j;
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
     int i,j,rows,cols;
     float value;

     do
     {
     printf("Inserire numero rows: ");
     scanf("%d",&rows);
     }
     while(rows<=0);
     do
     {
     printf("Inserire numero cols: ");
     scanf("%d",&cols);
     }
     while(cols<=0);

     initMatrix(matrix, rows, cols);

     for(i=0; i<readRows(*matrix); i++)
         for(j=0; j<readColumns(*matrix); j++)
         {
             printf("Inserisci value(%d,%d): ", i, j);
             scanf("%f",&value);
             writeMatrix(matrix, i, j, value);
         }

     return 0;
}

// IO functions
int readFromBinFile(Matrix * matrix, int matrixToBeRead, char * file)
{
      FILE * fp;
      Matrix temp;
      int i, j, errore_fine_file = 0;
      float value;

      if ((fp = fopen(file,"rb"))!=NULL)
      {
          /*
          Per raggiungere la matrix da leggere bisogna passare in rassegna di tutte
          le precedenti, in quanto non si è a conoscenza della loro grandezza
          */
          for(i=0; i<matrixToBeRead; i++)
          {
              fread(&temp,1,sizeof(matrix),fp);
              /*
              Una volta letta una matrix, si può determinare quante celle di memoria saltare
              in base alla sua dimensione
              */
              fseek(fp, readColumns(temp)*readRows(temp)*sizeof(float),SEEK_CUR);
          }
          //Se si è alla fine del file, la matrix non esiste
          if (feof(fp))
          {
             fclose(fp);
             return 3;
          }
          else
          {
              fread(&temp, 1, sizeof(matrix), fp);
              //Reinizializzo la matrix
              if (!initMatrix(matrix, readRows(temp), readColumns(temp)))
              {
                    //Leggo i values
                    for(i=0; i<readRows(*matrix) && !errore_fine_file; i++)
                        for(j=0; j<readColumns(*matrix) && !errore_fine_file; j++)
                        {
                            if (fread(&value,1,sizeof(float), fp)!=sizeof(float)) errore_fine_file = 1;
                            writeMatrix(matrix,i,j,value);
                        }
                    //Se è stato riscontrato un errore durante la lettura dei values do esito negativo
                    if (errore_fine_file) return 4;
                        else return 0;
              }
              else return 5;
          }
      }
      else return 1;
}

int writeToBinFile(Matrix * matrix, char * file)
{
      FILE * fp;
      int i,j;
      float value;

      if ((fp = fopen(file,"ab"))!=NULL)
      {
          //Si scrive innanzitutto la struttura della matrix
          fwrite(matrix,sizeof(matrix),1,fp);
          //Poi si scrivono i values
          for(i=0; i< readRows(*matrix); i++)
            for(j=0; j<readColumns(*matrix); j++)
          {
              readMatrix(*matrix, i, j, &value);
              fwrite(&value, 1, sizeof(float),fp);
          }

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
    int i,j, rows, cols, errore_fine_file=0,
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
                  fprintf(fp,"%f ",matrixValue);
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
