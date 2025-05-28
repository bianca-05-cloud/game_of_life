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

// t3

struct coordonate // structura prin intermediul careia vreau sa salvez coordonatele pe care le modifica jocul
                  // acestea sunt coordonatele pe care le salvez in lista/liste care se salveaza in nodurile arborelui
{
    int l;
    int c;
};

typedef struct coordonate coordonate;

struct lista // structura definita ptr a fi salvata in nodurile arborelui pe care dorim sa-l creeam
{
    coordonate x;
    struct lista *next;
};

typedef struct lista lista;

struct tree
{
    lista *val;
    struct tree *left;
    struct tree *right;
};

typedef struct tree node;

void adaugare_la_inceput_t3(lista **cap_matrice, int i, int j);
void adaugare_la_final_t3(lista **cap_matrice, int i, int j);
lista *matrice_devine_lista_t3(char **veche, char **noua, int N, int M);
int vecinii_t3(char **m, int N, int M, int i, int j);
void actualizare_matrice_dreapta_t3(char **m, char **q, int N, int M);
void actualizare_matrice_stanga_t3(char **m, char **p, int N, int M);
void creeare_arbore_t3(node *root, lista **capete_dreapta, lista **capete_stanga, int nivel, int max_k);
void trecere_din_lista_in_matrice_t3(lista *cap, char **m, int N, int M);
void copie_matrice(char **sursa, char **dest, int N, int M);
void preordine_t3(node *root, char **m, int N, int M, FILE *out, int nivel);

// task4


typedef struct {
    int linie;
    int coloana;
} Celula;

typedef struct {
    int n; // număr de celule vii
    Celula *celule; // vector de celule vii
    int **adj; // matrice de adiacență
} Graf;

void extrage_celule_vii(char **m, int N, int M, Celula **celule, int *nr_celule);
int **construieste_matrice_adiacenta(Celula *celule, int nr_celule);
void gaseste_componente_conexe(int **adj, Celula *celule, int nr_celule, int *componenta, int *nr_componente);
int compara_lanturi(Celula* celule, int* drum1, int* drum2, int lungime);
void backtrack(int** adj, Celula* celule, int* noduri, int dim, int poz, int* vizitat, int* drum_curent, int lungime,int* drum_max, int* lungime_max);
void cauta_lanturi_hamiltoniene(int** adj, Celula* celule, int* componenta, int nr_celule, int* nr_componente, FILE* out);
void afiseaza_lant(FILE *out, Celula *celule, int *drum, int lungime);
void preordine_task4(node *root, char **matrice_generatie, int N, int M, FILE *out, int nivel);
void afisare_lista_t3(lista *cap);
void afisare_node_t3(node *n);
void afisare_matrice_t3(char **m, int N, int M);