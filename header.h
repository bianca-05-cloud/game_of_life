#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// t1

void citire_matrice(char **m, FILE *in, int N, int M);
void afisare_matrice(char **m, int N, int M);
int vecinii(char **m, int N, int M, int i, int j);
void actualizare_matrice(char **m, char **q, int N, int M);

// t2

// lista din care e alcatuita stiva
struct celula
{
    int l;
    int c;
    struct celula *next;
};

typedef struct celula celula;

// stiva propriu-zisa, prin care reprezentam cate un element corespunzator unei generatii

struct generatie
{
    int k;                  // numarul generatiei
    celula *x;              // lista de celule modificate din aceasta generatie
    struct generatie *next; // pointer catre urmatoarea generatie din stiva
};

typedef struct generatie generatie;

void push_t2(generatie **stiva, int k, celula *x);
int vecinii_t2(char **m, int N, int M, int i, int j);
void adaugare_t2(celula **head, int l, int c);
char **copie_t2(char **m, int N, int M);
void eliberare_matrice_t2(char **m, int N);
void afisare_t2(generatie *stiva, FILE *out);

void eliberare_lista_celule(celula *head);
void eliberare_stiva_generatii(generatie *stiva);

// Structura pentru nodul arborelui binar
struct nod_arbore {
    celula *modificari;         // lista de celule modificate față de părinte
    struct nod_arbore *stanga;  // regula B
    struct nod_arbore *dreapta; // reguli standard
};
typedef struct nod_arbore nod_arbore;

// Funcții pentru Task 3
void aplicare_regula_B(char **m, char **nou, int N, int M, celula **modificari);
void construire_arbore(nod_arbore *nod_curent, char **matrice_curenta, int nivel_curent, int K, int N, int M);
void parcurgere_preordine(nod_arbore *nod, char **matrice_curenta, int N, int M, FILE *out);
void reconstituire_matrice(char **matrice, celula *modificari, int N, int M);
nod_arbore* creare_nod();
void eliberare_arbore(nod_arbore *nod);
char **copiere_matrice(char **m, int N, int M);

// // Structură pentru reprezentarea unui nod din graf
// struct nod_graf {
//     int linie;
//     int coloana;
//     int index;  // index în graf (0, 1, 2, ...)
// };
// typedef struct nod_graf nod_graf;

// // Funcții pentru Task 4
// int sunt_vecine(int l1, int c1, int l2, int c2);
// void construire_graf(char **matrice, int N, int M, nod_graf **noduri, int *nr_noduri, int **matrice_adiacenta);
// void gaseste_lant_hamiltonian(int **matrice_adiacenta, int nr_noduri, int *lant_maxim, int *lungime_maxima, nod_graf *noduri);
// void backtrack_hamiltonian(int **matrice_adiacenta, int nr_noduri, int *lant_curent, int *vizitat, int pozitie, int *lant_maxim, int *lungime_maxima, nod_graf *noduri);
// int compara_lanturi(int *lant1, int *lant2, int lungime, nod_graf *noduri);
// void procesare_arbore_task4(nod_arbore *nod, char **matrice_curenta, int N, int M, FILE *out, int nivel);
// void eliberare_matrice_int(int **matrice, int n);
