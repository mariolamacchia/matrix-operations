#include <stdio.h>
#include <stdlib.h>
#include "operations.h"


int main(int argc, char *argv[])
{
    matrice matrix1, matrix2, matrix3;
    float valore_prod_scalare = 15.4;
    int i;

    i=0;
    puts("STAMPA INPUT");
    while (!leggi_da_file_txt(&matrix1,i++,FILE_INPUT))
    {
        stampa(matrix1);
    }
    system("pause");

    i=0;
    puts("STAMPA OUTPUT");
    while (!leggi_da_file_bin(&matrix1,i++,FILE_OUTPUT))
    {
        stampa(matrix1);
    }
    system("pause");

    svuota_file(FILE_OUTPUT);
    i=0;
    puts("COPIA MATRICI DA INPUT A OUTPUT");
    while (!leggi_da_file_txt(&matrix1,i,FILE_INPUT))
    {
        stampa_errore(scrivi_su_file_bin(&matrix1,FILE_OUTPUT));
        stampa_errore(leggi_da_file_bin(&matrix2,i++,FILE_OUTPUT));
        stampa(matrix2);
    }
    system("pause");
    svuota_file(FILE_OUTPUT);

    //SOMMA
    puts("\n\OPERAZIONI\nSOMMA matrice 0 + matrice 1");
    stampa_errore(leggi_da_file_txt(&matrix1,0,FILE_INPUT));
    stampa_errore(leggi_da_file_txt(&matrix2,1,FILE_INPUT));
    stampa_errore(somma(matrix1,matrix2,&matrix3));
    stampa_errore(scrivi_su_file_bin(&matrix3,FILE_OUTPUT));
    stampa_errore(leggi_da_file_bin(&matrix3,0,FILE_OUTPUT));
    stampa(matrix3);

    //DIFFERENZA
    puts("DIFFERENZA matrice 2 - matrice 3");
    stampa_errore(leggi_da_file_txt(&matrix1,2,FILE_INPUT));
    stampa_errore(leggi_da_file_txt(&matrix2,3,FILE_INPUT));
    stampa_errore(differenza(matrix1,matrix2,&matrix3));
    stampa_errore(scrivi_su_file_bin(&matrix3,FILE_OUTPUT));
    stampa_errore(leggi_da_file_bin(&matrix3,1,FILE_OUTPUT));
    stampa(matrix3);

    //PRODOTTO
    puts("PRODOTTO matrice 4 X matrice 5");
    stampa_errore(leggi_da_file_txt(&matrix1,4,FILE_INPUT));
    stampa_errore(leggi_da_file_txt(&matrix2,5,FILE_INPUT));
    stampa_errore(prodotto(matrix1,matrix2,&matrix3));
    stampa_errore(scrivi_su_file_bin(&matrix3,FILE_OUTPUT));
    stampa_errore(leggi_da_file_bin(&matrix3,2,FILE_OUTPUT));
    stampa(matrix3);

    //TRASPOSTA
    puts("TRASPOSTA matrice 6");
    stampa_errore(leggi_da_file_txt(&matrix1,6,FILE_INPUT));
    stampa_errore(trasposta(matrix1,&matrix3));
    stampa_errore(scrivi_su_file_bin(&matrix3,FILE_OUTPUT));
    stampa_errore(leggi_da_file_bin(&matrix3,3,FILE_OUTPUT));
    stampa(matrix3);

    //PRODOTTO SCALARE
    puts("PRODOTTO SCALARE matrice 7 * 15.4");
    stampa_errore(leggi_da_file_txt(&matrix1,7,FILE_INPUT));
    stampa_errore(prodotto_scalare(matrix1,valore_prod_scalare,&matrix3));
    stampa_errore(scrivi_su_file_bin(&matrix3,FILE_OUTPUT));
    stampa_errore(leggi_da_file_bin(&matrix3,4,FILE_OUTPUT));
    stampa(matrix3);


    system("pause");
    return 0;
}
