#include <stdio.h>
#include "functions.h"

//SCRIVERE E LEGGERE GRANDEZZE
int scrivi_righe (matrice * matrix, int righe)
{
    if (righe <= 0) return 5;
    matrix->righe=righe;
    return 0;
}

int scrivi_colonne (matrice *matrix, int colonne)
{
     if (colonne <=0) return 5;
     matrix->colonne=colonne;
     return 0;
}

int leggi_righe (matrice matrix)
{
    return matrix.righe;
}

int leggi_colonne (matrice matrix)
{
    return matrix.colonne;
}

//INIZIALIZZAZIONE
int inizializza_matrice (matrice *matrix,int righe, int colonne)
{
        if (righe <= 0 || colonne <= 0) return 5;
        scrivi_righe(matrix, righe);
        scrivi_colonne(matrix, colonne);
        return 0;
}

//SCRIVERE E LEGGERE VALORI MATRICE
int scrivi_matrice (matrice *matrix, int riga, int colonna, float valore)
{
     if (riga < 0 || riga >= leggi_righe(*matrix) || colonna < 0 || colonna >= leggi_colonne(*matrix) )
        return 7;
     matrix->valori[riga][colonna]=valore;
     return 0;
}

int leggi_matrice (matrice matrix, int riga, int colonna, float * valore)
{
     if (riga < 0 || riga >= leggi_righe(matrix) || colonna < 0 || colonna >= leggi_colonne(matrix) )
        return 6;
     *valore = matrix.valori[riga][colonna];
     return 0;
}

//INTERFACCIA UTENTE
int stampa (matrice matrix)
{
     int i,j;
     float valore_matrice;

     puts("--------");
     for (i=0; i<leggi_righe(matrix); i++)
     {
         for (j=0; j<leggi_colonne(matrix); j++)
         {
             leggi_matrice(matrix, i, j, &valore_matrice);
             printf("%f ", valore_matrice);
         }
     printf("\n");
     }
     puts("--------");
     return 0;
}

int leggi (matrice *matrix)
{
     int i,j,rows,cols;
     float valore;

     do
     {
     printf("Inserire numero righe: ");
     scanf("%d",&rows);
     }
     while ((rows<=0)||(rows>DIM_X));
     do
     {
     printf("Inserire numero colonne: ");
     scanf("%d",&cols);
     }
     while ((cols<=0)||(cols>DIM_Y));

     inizializza_matrice (matrix, rows, cols);

     for (i=0; i<leggi_righe(*matrix); i++)
         for (j=0; j<leggi_colonne(*matrix); j++)
         {
             printf("Inserisci valore (%d,%d): ", i, j);
             scanf("%f",&valore);
             scrivi_matrice(matrix, i, j, valore);
         }

     return 0;
}

//FUNZIONI SU FILE
int leggi_da_file_bin (matrice * matrix, int matrice_da_leggere, char * file)
{
      FILE * fp;

      if ((fp = fopen(file,"rb"))!=NULL)
      {
          //Si raggiunge la matrice da leggere
          fseek(fp,matrice_da_leggere*sizeof(matrice),SEEK_CUR);
          //Se si è alla fine del file, la matrice non esiste
          if (feof(fp))
          {
             fclose(fp);
             return 3;
          }
          else
          {
              //Si legge la matrice e si controlla quanti byte sono stati letti
              if (fread(matrix,1,sizeof(matrice),fp) == sizeof(matrice))
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

int scrivi_su_file_bin (matrice * matrix, char * file)
{
      FILE * fp;

      if ((fp = fopen(file,"ab"))!=NULL)
      {
          fwrite(matrix,sizeof(matrice),1,fp);
          fclose(fp);
          return 0;
      }
      else return 1;
}

/*
      I file txt contenenti matrici hanno una matrice per rigo. Ogni rigo
      è composto da due interi che definiscono righe e colonne e da righe*colonne float
      che definiscono i valori
*/
int leggi_da_file_txt (matrice * matrix, int matrice_da_leggere, char * file)
{
    FILE * fp;
    int i,j, righe, colonne, errore_fine_file=0,
        errore_inizializzazione=0;
    char c;
    float valore;

    if ((fp=fopen(file, "r"))!=NULL)
    {
       i=0;
       while (i< matrice_da_leggere && !(feof(fp)) )
       {
             if ((c=getc(fp))=='\n') i++;
                /* Cerca il simbolo new line tante volte quante sono le matrici
                   da scorrere prima di incontrare quella desiderata */
       }
       if (!feof(fp))
       {
           fscanf(fp,"%d%d",&righe,&colonne);
           if (!(errore_inizializzazione=inizializza_matrice(matrix,righe,colonne)))
           {
               for (i=0;i<righe && !errore_fine_file;i++)
                   for (j=0; j<colonne && !errore_fine_file; j++)
                   {
                        if (feof(fp)) errore_fine_file=1;
                        fscanf(fp,"%f",&valore);
                        scrivi_matrice(matrix,i,j,valore);
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
                       while (c==' ' &&!feof(fp));
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

int scrivi_su_file_txt (matrice * matrix, char * file)
{
      FILE * fp;
      int i,j;
      float valore_matrice;

      if ((fp = fopen(file,"a"))!=NULL)
      {
          fprintf(fp,"\n%d %d ", leggi_righe(*matrix), leggi_colonne(*matrix));
          for (i=0; i<leggi_righe(*matrix);i++)
              for (j=0; j<leggi_colonne(*matrix);j++)
              {
                  leggi_matrice(*matrix, i, j, &valore_matrice);
                  fprintf(fp,"%f ",valore_matrice);
              }
          fprintf(fp,"\n");

          fclose(fp);
          return 0;
      }
      else return 1;
}

int svuota_file (char * file)
{
    FILE * fp;

    if ((fp=fopen(file, "w"))==NULL) return 1;
    fclose(fp);
    return 0;
}
