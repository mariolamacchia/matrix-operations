#include <stdio.h>
#include "funzioni.h"

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
        int i,j;
        lista_di_elementi lista_temp;
        elemento_lista * elemento;
        lista_lista * lista;

        if (righe <=0 || colonne <=0) return 5;
        scrivi_righe(matrix, righe);
        scrivi_colonne(matrix, colonne);
        matrix->valori = NULL;          //Inizializza lista di liste
        for (i=0; i< righe; i++)
        {
            lista_temp = NULL;     //Inizializza lista di elementi temporale
            for (j=0;j<colonne;j++)
            {
                //Inserisci colonne elementi
                  elemento= malloc(sizeof(elemento_lista)) ;
                  elemento->prossimo=lista_temp;
                  lista_temp=elemento;
            }
            //Inserisci nodo alla lista di liste contenente la lista di elementi appena creata
            lista = malloc(sizeof(lista_lista));
            lista->prossimo = matrix->valori;
            lista->info= lista_temp;
            matrix->valori = lista;
        }

        return 0;
}

//SCRIVERE E LEGGERE VALORI MATRICE
int scrivi_matrice (matrice *matrix, int riga, int colonna, float valore)
{
     int i;
     lista_di_elementi punt_colonna;
     lista_di_liste punt_riga;

     if (riga >= leggi_righe(*matrix) || colonna >= leggi_colonne(*matrix)
         || riga < 0 || colonna < 0) return 7;

     punt_riga=matrix->valori;
     for (i=0;i<riga;i++)
     {
         punt_riga=punt_riga->prossimo;
     }
     punt_colonna = punt_riga->info;
     for (i=0;i<colonna;i++)
     {
         punt_colonna = punt_colonna->prossimo;
     }

     punt_colonna->info = valore;
     return 0;
}

int leggi_matrice (matrice matrix, int riga, int colonna, float * valore)
{
     int i;
     lista_di_elementi punt_colonna;
     lista_di_liste punt_riga;

     if (riga >= leggi_righe(matrix) || colonna >= leggi_colonne(matrix)
         || riga < 0 || colonna < 0) return 6;

     punt_riga=matrix.valori;
     for (i=0;i<riga;i++)
     {
         punt_riga=punt_riga->prossimo;
     }
     punt_colonna = punt_riga->info;
     for (i=0;i<colonna;i++)
     {
         punt_colonna = punt_colonna->prossimo;
     }

     *valore = punt_colonna->info;
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
     while (rows<=0);
     do
     {
     printf("Inserire numero colonne: ");
     scanf("%d",&cols);
     }
     while (cols<=0);

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
      matrice temp;
      int i, j, errore_fine_file = 0;
      float valore;

      if ((fp = fopen(file,"rb"))!=NULL)
      {
          /*
          Per raggiungere la matrice da leggere bisogna passare in rassegna di tutte
          le precedenti, in quanto non si � a conoscenza della loro grandezza
          */
          for (i=0; i<matrice_da_leggere; i++)
          {
              fread(&temp,1,sizeof(matrice),fp);
              /*
              Una volta letta una matrice, si pu� determinare quante celle di memoria saltare
              in base alla sua dimensione
              */
              fseek(fp, leggi_colonne(temp)*leggi_righe(temp)*sizeof(float),SEEK_CUR);
          }
          //Se si � alla fine del file, la matrice non esiste
          if (feof(fp))
          {
             fclose(fp);
             return 3;
          }
          else
          {
              fread(&temp, 1, sizeof(matrice), fp);
              //Reinizializzo la matrice
              if (!inizializza_matrice(matrix, leggi_righe(temp), leggi_colonne(temp)))
              {
                    //Leggo i valori
                    for (i=0; i<leggi_righe(*matrix) && !errore_fine_file; i++)
                        for (j=0; j<leggi_colonne(*matrix) && !errore_fine_file; j++)
                        {
                            if (fread(&valore,1,sizeof(float), fp)!=sizeof(float)) errore_fine_file = 1;
                            scrivi_matrice(matrix,i,j,valore);
                        }
                    //Se � stato riscontrato un errore durante la lettura dei valori do esito negativo
                    if (errore_fine_file) return 4;
                        else return 0;
              }
              else return 5;
          }
      }
      else return 1;
}

int scrivi_su_file_bin (matrice * matrix, char * file)
{
      FILE * fp;
      int i,j;
      float valore;

      if ((fp = fopen(file,"ab"))!=NULL)
      {
          //Si scrive innanzitutto la struttura della matrice
          fwrite(matrix,sizeof(matrice),1,fp);
          //Poi si scrivono i valori
          for(i=0; i< leggi_righe(*matrix); i++)
            for (j=0; j<leggi_colonne(*matrix); j++)
          {
              leggi_matrice(*matrix, i, j, &valore);
              fwrite(&valore, 1, sizeof(float),fp);
          }

          fclose(fp);
          return 0;
      }
      else return 1;
}

/*
      I file txt contenenti matrici hanno una matrice per rigo. Ogni rigo
      � composto da due interi che definiscono righe e colonne e da righe*colonne float
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

               //Si controlla se si � raggiunta la fine del file
               if (errore_fine_file)
               {
                   return 4;
               }
               else
               {
                   /*
                   Se non si � raggiunta la fine del file si controlla comunque
                   il carattere successivo all'ultimo dato letto. Se non � un newline
                   o se non finisce il file prima di trovarne uno, c'� un errore
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
