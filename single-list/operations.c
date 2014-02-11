/********************************************
            OPERAZIONI TRA MATRICI
********************************************/
#include "operations.h"
#include <math.h>
#include <stdio.h>

int somma (matrice matrix1, matrice matrix2, matrice * risultato)
{
    int i,j;
    float valore_matrice1, valore_matrice2;

    if ((leggi_righe(matrix1)==leggi_righe(matrix2))&&(leggi_colonne(matrix1)==leggi_colonne(matrix2)))
    {
    inizializza_matrice(risultato,leggi_righe(matrix1),leggi_colonne(matrix2));
        for (i=0; i<leggi_righe(*risultato); i++)
            for (j=0; j<leggi_colonne(*risultato); j++)
            {
                leggi_matrice(matrix1, i, j, &valore_matrice1);
                leggi_matrice(matrix2, i, j, &valore_matrice2);
                scrivi_matrice(risultato,i,j,valore_matrice1+valore_matrice2);
            }
    return 0;
    }
    else return 2;
}

int differenza (matrice matrix1, matrice matrix2, matrice * risultato)
{
    int i,j;
    float valore_matrice1, valore_matrice2;

    if ((leggi_righe(matrix1)==leggi_righe(matrix2))&&(leggi_colonne(matrix1)==leggi_colonne(matrix2)))
    {
    prodotto_scalare(matrix2,-1,&matrix2);
    inizializza_matrice(risultato,leggi_righe(matrix1),leggi_colonne(matrix2));
        for (i=0; i<leggi_righe(*risultato); i++)
            for (j=0; j<leggi_colonne(*risultato); j++)
            {
                leggi_matrice(matrix1, i, j, &valore_matrice1);
                leggi_matrice(matrix2, i, j, &valore_matrice2);
                scrivi_matrice(risultato,i,j,valore_matrice1+valore_matrice2);
            }
    return 0;
    }

    else return 2;
}

int prodotto_scalare (matrice matrix, float valore, matrice * risultato)
{
        int i,j;
        float valore_matrice;

        inizializza_matrice(risultato, leggi_righe(matrix), leggi_colonne(matrix));
        for (i=0; i<leggi_righe(*risultato); i++)
            for (j=0; j<leggi_colonne(*risultato); j++)
            {
                leggi_matrice(matrix, i, j, &valore_matrice);
                scrivi_matrice (risultato, i, j, valore_matrice * valore);
            }
        return 0;
}

int trasposta (matrice matrix, matrice * risultato)
{
        int i,j;
        float valore_matrice;

        inizializza_matrice(risultato,leggi_colonne(matrix),leggi_righe(matrix));
        for (i=0; i<leggi_righe(*risultato); i++)
            for (j=0; j<leggi_colonne(*risultato); j++)
            {
                leggi_matrice(matrix, j, i, &valore_matrice);
                scrivi_matrice(risultato, i, j, valore_matrice);
            }
        return 0;
}

int prodotto (matrice matrix1, matrice matrix2, matrice * risultato)
{
        int i,j,h;
        float valore, valore_matrice1, valore_matrice2;

        if (leggi_colonne(matrix1)==leggi_righe(matrix2))
        {
            inizializza_matrice (risultato, leggi_righe(matrix1), leggi_colonne(matrix2));

            for (i=0; i<leggi_righe(*risultato); i++)
                for (j=0; j<leggi_colonne(*risultato); j++)
                {
                    valore=0;
                    for (h=0; h<leggi_colonne(matrix1); h++)
                    {
                        leggi_matrice(matrix1, i, h, &valore_matrice1);
                        leggi_matrice(matrix2, h, j, &valore_matrice2);
                        valore += valore_matrice1 * valore_matrice2;
                    }
                    scrivi_matrice(risultato, i, j, valore);
                }
            return 0;
        }
        else return 2;
}

void stampa_errore(int error)
{
     /*
       0: OK
       1: File inesistente
       2: Grandezze matrici inadatte all'operazione
       3: Raggiungimento eof prima del previsto
       4: Errore durante la lettura della matrice dal file
     */
     switch (error)
     {

            case 1:
                 puts("Errore durante la lettura del file: file inesistente!");
                 break;
            case 2:
                 puts("Errore durante il calcolo: le matrici non hanno le dimensioni adatte per eseguire l'operaizone!");
                 break;
            case 3:
                 puts("Errore durante la lettura del file: il file e' troppo corto. Si controlli che la matrice esista nel file.");
                 break;
            case 4:
                 puts("Errore durante la lettura del file: la matrice indicata non e' leggibile! Controllare che il file non sia danneggiato.");
                 break;
            case 5:
                 puts("Errore durante la scrittura della matrice: il numero di righe e colonne dev'essere maggiore di zero!");
                 break;
            case 6:
                 puts("Errore durante la lettura della matrice: la riga o la colonna richiesta non esistono!");
                 break;
            case 7:
                 puts("Errore durante la scrittura della matrice: la riga o la colonna richiesta non esistono!");
     }
}
