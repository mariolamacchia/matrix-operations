/********************************************
      FUNZIONI PER MATRICE A DUE INDICI
********************************************/

#define DIM_X 100
#define DIM_Y 100
//DIM è la dimensione massima che ogni riga e colonna della matrice può assumere
#define FILE_INPUT "input.txt"
#define FILE_OUTPUT "output"
//FILE_INPUT E FILE_OUTPUT sono i file dove vengono salvate le matrici

typedef struct {
        int righe;
        int colonne;
        float valori[DIM_X*DIM_Y];
        } matrice;

//INIZIALIZZAZIONE
int inizializza_matrice (matrice*,int righe, int colonne);

//SCRIVERE E LEGGERE GRANDEZZE
int scrivi_righe (matrice*, int);
int scrivi_colonne (matrice*, int);
int leggi_righe (matrice);
int leggi_colonne (matrice);

//SCRIVERE E LEGGERE VALORI
int scrivi_matrice (matrice*, int riga, int colonna, float valore);
int leggi_matrice (matrice, int riga, int colonna, float * valore);

//FUNZIONI SU FILE
int leggi_da_file_bin (matrice*, int matrice_da_leggere, char * file);
int leggi_da_file_txt (matrice*, int matrice_da_leggere, char * file);
    /* matrice_da_leggere (in leggi_da_file_XXX) indica l'indice della matrice da leggere da file
       l'indice va da 0 a n-1 */
int scrivi_su_file_bin (matrice*, char * file);
int scrivi_su_file_txt (matrice*, char * file);
int svuota_file (char * file);

//INTERFACCIA UTENTE
//funzioni necessarie all'utente in fase di esecuzione
int stampa (matrice);
int leggi (matrice*);
