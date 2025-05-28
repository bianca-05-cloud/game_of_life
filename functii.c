#include "header.h"

// task1

// Functie pentru citire matrice
void citire_matrice(char **m, FILE *in, int N, int M)
{
    int i, j;
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < M; j++)
        {
            fscanf(in, " %c", &m[i][j]);
        }
    }
}

// // Functie pentru afisare matrice
// void afisare_matrice(char **m, int N, int M)
// {
//     int i, j;
//     for (i = 0; i < N; i++)
//     {
//         for (j = 0; j < M; j++)
//         {
//             printf("%c", m[i][j]);
//         }
//         printf("\n");
//     }
// }

// Functie pentru numararea vecinilor vii ai unei celule
int vecinii(char **m, int N, int M, int i, int j)
{
    const int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    const int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};

    int vecini = 0;
    for (int d = 0; d < 8; d++)
    {
        int ni = i + dx[d];
        int nj = j + dy[d];
        if (ni >= 0 && ni < N && nj >= 0 && nj < M && m[ni][nj] == 'X')
            vecini++;
    }
    return vecini;
}

// functie de actualizare a matricei originale
void actualizare_matrice(char **m, char **q, int N, int M)
{
    int i, j, vecinii_vii;

    // Calculăm noile stări în matricea auxiliară q
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < M; j++)
        {
            vecinii_vii = vecinii(m, N, M, i, j);

            if (m[i][j] == 'X' && (vecinii_vii < 2 || vecinii_vii > 3))
            {
                q[i][j] = '+'; // celula moare
            }
            else if (m[i][j] == '+' && vecinii_vii == 3)
            {
                q[i][j] = 'X'; // celula devine vie
            }
            else
            {
                q[i][j] = m[i][j]; // celula rămâne neschimbată
            }
        }
    }

    // Copiem noile stări din matricea auxiliară în matricea principală
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < M; j++)
        {
            m[i][j] = q[i][j]; // actualizăm matricea principală
        }
    }
}

// task2

// Adaugă un element în vârful stivei
void push_t2(generatie **stiva, int k, celula *x)
{
    generatie *newNode = (generatie *)malloc(sizeof(generatie));
    newNode->k = k;
    newNode->x = x;
    newNode->next = *stiva;
    *stiva = newNode;
}

// adauga o celula in lista modificarilor, mentine ordinea dupa linie si coloana
void adaugare_t2(celula **head, int l, int c)
{
    celula *new = (celula *)malloc(sizeof(celula)); // aloca memorie pentru noua celula
    new->l = l;
    new->c = c;
    new->next = NULL;

    if (*head == NULL || l < (*head)->l || (l == (*head)->l && c < (*head)->c))

    {
        new->next = *head; // leaga vechiul head dupa noul nod
        *head = new;       // actualizeaza head
        return;
    }

    celula *curent = *head;
    while (curent->next && (curent->next->l < l || (curent->next->l == l && curent->next->c < c)))
    // avansam prin lista atata timp cat urm element este "<" (l,c)
    {
        curent = curent->next;
    }
    new->next = curent->next; // leg noul nod dupa curent
    curent->next = new;       // leg vechiul next dupa new
}

// copiere matrice caracter cu caracter

char **copie_t2(char **m, int N, int M)
{
    int i, j;
    char **aux = (char **)malloc(N * sizeof(char *));
    for (i = 0; i < N; i++)
    {
        aux[i] = (char *)malloc(M * sizeof(char));
        for (j = 0; j < M; j++)
        {
            aux[i][j] = m[i][j];
        }
    }
    return aux;
}

void eliberare_matrice_t2(char **m, int N)
{
    int i;
    for (i = 0; i < N; i++)
    {
        free(m[i]);
    }
    free(m);
}

// afisarea in ordine a stivei cu coordonatele celulelor modificate de la 1 la K

void afisare_t2(generatie *stiva, FILE *out)
{
    if (stiva == NULL)
        return;

    afisare_t2(stiva->next, out);

    fprintf(out, "%d ", stiva->k);
    celula *curent = stiva->x;
    while (curent)
    {
        fprintf(out, "%d %d", curent->l, curent->c);
        if (curent->next)
            fprintf(out, " ");
        curent = curent->next;
    }
    fprintf(out, "\n");
}

void eliberare_lista_celule(celula *head)
{
    while (head)
    {
        celula *temp = head;
        head = head->next;
        free(temp);
    }
}

void eliberare_stiva_generatii(generatie *stiva)
{
    while (stiva)
    {
        generatie *temp = stiva;
        stiva = stiva->next;
        eliberare_lista_celule(temp->x); // eliberează lista de modificări
        free(temp);                      // eliberează nodul stivă
    }
}

// Funcție pentru aplicarea regulii B (celulă cu exact 2 vecini vii devine vie)
void aplicare_regula_B(char **m, char **nou, int N, int M, celula **modificari)
{
    int i, j;

    // Copiez matricea originală
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < M; j++)
        {
            nou[i][j] = m[i][j];
        }
    }

    // Aplic regula B
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < M; j++)
        {
            int vecini = vecinii(m, N, M, i, j);

            // Regula B: orice celulă cu exact 2 vecini vii devine vie
            if (vecini == 2 && m[i][j] == '+')
            {
                nou[i][j] = 'X';
                adaugare_t2(modificari, i, j);
            }
        }
    }
}

// Creare nod nou pentru arbore
nod_arbore *creare_nod()
{
    nod_arbore *nod = (nod_arbore *)malloc(sizeof(nod_arbore));
    nod->modificari = NULL;
    nod->stanga = NULL;
    nod->dreapta = NULL;
    return nod;
}

// Copiere matrice (similar cu copie_t2 dar cu nume diferit pentru claritate)
char **copiere_matrice(char **m, int N, int M)
{
    int i, j;
    char **aux = (char **)malloc(N * sizeof(char *));
    for (i = 0; i < N; i++)
    {
        aux[i] = (char *)malloc(M * sizeof(char));
        for (j = 0; j < M; j++)
        {
            aux[i][j] = m[i][j];
        }
    }
    return aux;
}

// Construire arbore recursiv
void construire_arbore(nod_arbore *nod_curent, char **matrice_curenta, int nivel_curent, int K, int N, int M)
{
    if (nivel_curent >= K)
    {
        return; // Am ajuns la nivelul K, nu mai creăm noduri
    }

    // Creez matrici auxiliare pentru cele două ramuri
    char **matrice_stanga = copiere_matrice(matrice_curenta, N, M);
    char **matrice_dreapta = copiere_matrice(matrice_curenta, N, M);
    char **temp_stanga = copiere_matrice(matrice_curenta, N, M);
    char **temp_dreapta = copiere_matrice(matrice_curenta, N, M);

    // Creez nodurile pentru stânga și dreapta
    nod_curent->stanga = creare_nod();
    nod_curent->dreapta = creare_nod();

    // Aplic regula B pentru ramura stângă
    aplicare_regula_B(matrice_curenta, matrice_stanga, N, M, &(nod_curent->stanga->modificari));

    // Aplic regulile standard pentru ramura dreaptă
    celula *modificari_dreapta = NULL;
    int i, j;
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < M; j++)
        {
            int vecini = vecinii(matrice_curenta, N, M, i, j);

            if (matrice_curenta[i][j] == 'X')
            {
                // Celulă vie
                if (vecini < 2 || vecini > 3)
                {
                    matrice_dreapta[i][j] = '+';
                    adaugare_t2(&modificari_dreapta, i, j);
                }
            }
            else
            {
                // Celulă moartă
                if (vecini == 3)
                {
                    matrice_dreapta[i][j] = 'X';
                    adaugare_t2(&modificari_dreapta, i, j);
                }
            }
        }
    }
    nod_curent->dreapta->modificari = modificari_dreapta;

    // Continuă recursiv pentru ambele ramuri
    construire_arbore(nod_curent->stanga, matrice_stanga, nivel_curent + 1, K, N, M);
    construire_arbore(nod_curent->dreapta, matrice_dreapta, nivel_curent + 1, K, N, M);

    // Eliberez memoria pentru matricile temporare
    eliberare_matrice_t2(matrice_stanga, N);
    eliberare_matrice_t2(matrice_dreapta, N);
    eliberare_matrice_t2(temp_stanga, N);
    eliberare_matrice_t2(temp_dreapta, N);
}

// Reconstituire matrice pe baza modificărilor
void reconstituire_matrice(char **matrice, celula *modificari, int N, int M)
{
    celula *curent = modificari;
    while (curent != NULL)
    {
        int l = curent->l;
        int c = curent->c;
        // Inversez starea celulei
        matrice[l][c] = (matrice[l][c] == 'X') ? '+' : 'X';
        curent = curent->next;
    }
}

// Parcurgere în preordine și afișare matrici
void parcurgere_preordine(nod_arbore *nod, char **matrice_curenta, int N, int M, FILE *out)
{
    if (nod == NULL)
    {
        return;
    }

    // Aplic modificările pentru a obține matricea curentă
    char **matrice_afisare = copiere_matrice(matrice_curenta, N, M);
    reconstituire_matrice(matrice_afisare, nod->modificari, N, M);

    // Afișez matricea curentă
    int i, j;
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < M; j++)
        {
            fprintf(out, "%c", matrice_afisare[i][j]);
        }
        fprintf(out, "\n");
    }
    fprintf(out, "\n");

    // Parcurg recursiv în preordine
    if (nod->stanga != NULL)
    {
        parcurgere_preordine(nod->stanga, matrice_afisare, N, M, out);
    }
    if (nod->dreapta != NULL)
    {
        parcurgere_preordine(nod->dreapta, matrice_afisare, N, M, out);
    }

    eliberare_matrice_t2(matrice_afisare, N);
}

// Eliberare arbore
void eliberare_arbore(nod_arbore *nod)
{
    if (nod == NULL)
    {
        return;
    }

    eliberare_arbore(nod->stanga);
    eliberare_arbore(nod->dreapta);
    eliberare_lista_celule(nod->modificari);
    free(nod);
}


//Functii task 4
// // Verifică dacă două celule sunt vecine (8-vecini)
// int sunt_vecine(int l1, int c1, int l2, int c2)
// {
//     int dl = abs(l1 - l2);
//     int dc = abs(c1 - c2);
//     return (dl <= 1 && dc <= 1 && !(dl == 0 && dc == 0));
// }

// // Construiește graful din celulele vii
// void construire_graf(char **matrice, int N, int M, nod_graf **noduri, int *nr_noduri, int **matrice_adiacenta)
// {
//     *nr_noduri = 0;

//     // Numără celulele vii și creează nodurile
//     int i, j;
//     for (i = 0; i < N; i++)
//     {
//         for (j = 0; j < M; j++)
//         {
//             if (matrice[i][j] == 'X')
//             {
//                 (*nr_noduri)++;
//             }
//         }
//     }

//     if (*nr_noduri == 0)
//     {
//         *noduri = NULL;
//         return;
//     }

//     // Alocă memorie pentru noduri
//     *noduri = (nod_graf *)malloc((*nr_noduri) * sizeof(nod_graf));

//     // Populează array-ul de noduri
//     int index = 0;
//     for (i = 0; i < N; i++)
//     {
//         for (j = 0; j < M; j++)
//         {
//             if (matrice[i][j] == 'X')
//             {
//                 (*noduri)[index].linie = i;
//                 (*noduri)[index].coloana = j;
//                 (*noduri)[index].index = index;
//                 index++;
//             }
//         }
//     }

//     // Alocă și inițializează matricea de adiacență
//     for (i = 0; i < *nr_noduri; i++)
//     {
//         matrice_adiacenta[i] = (int *)calloc(*nr_noduri, sizeof(int));
//     }

//     // Construiește matricea de adiacență
//     for (i = 0; i < *nr_noduri; i++)
//     {
//         for (j = i + 1; j < *nr_noduri; j++)
//         {
//             if (sunt_vecine((*noduri)[i].linie, (*noduri)[i].coloana,
//                             (*noduri)[j].linie, (*noduri)[j].coloana))
//             {
//                 matrice_adiacenta[i][j] = 1;
//                 matrice_adiacenta[j][i] = 1;
//             }
//         }
//     }
// }

// // Returnează -1 dacă lant1 e mai bun, 1 dacă lant2 e mai bun, 0 dacă sunt identice
// int compara_lanturi(int *lant1, int *lant2, int lungime, nod_graf *noduri)
// {
//     int i;
//     for (i = 0; i <= lungime; i++)
//     {
//         int l1 = noduri[lant1[i]].linie;
//         int c1 = noduri[lant1[i]].coloana;
//         int l2 = noduri[lant2[i]].linie;
//         int c2 = noduri[lant2[i]].coloana;

//         // Compară mai întâi linia
//         if (l1 < l2)
//             return -1; // lant1 e mai bun
//         if (l1 > l2)
//             return 1; // lant2 e mai bun

//         // Dacă liniile sunt egale, compară coloana
//         if (c1 < c2)
//             return -1; // lant1 e mai bun
//         if (c1 > c2)
//             return 1; // lant2 e mai bun
//     }
//     return 0; // identice
// }

// void optimizeaza_lant(int *lant, int lungime, nod_graf *noduri) {
//     if (lungime < 1) return;
    
//     // Găsește poziția nodului minim în lanț
//     int min_pos = 0;
//     int i;
//     for (i = 1; i <= lungime; i++) {
//         if (noduri[lant[i]].linie < noduri[lant[min_pos]].linie ||
//             (noduri[lant[i]].linie == noduri[lant[min_pos]].linie &&
//              noduri[lant[i]].coloana < noduri[lant[min_pos]].coloana)) {
//             min_pos = i;
//         }
//     }
    
//     // Dacă minimul nu e la început, rotește lanțul
//     if (min_pos > 0) {
//         int *temp = (int *)malloc((lungime + 1) * sizeof(int));
        
//         // Verifică direcția optimă
//         int next = (min_pos + 1) % (lungime + 1);
//         int prev = (min_pos - 1 + lungime + 1) % (lungime + 1);
        
//         int forward = 1;
//         if (noduri[lant[prev]].linie < noduri[lant[next]].linie ||
//             (noduri[lant[prev]].linie == noduri[lant[next]].linie &&
//              noduri[lant[prev]].coloana < noduri[lant[next]].coloana)) {
//             forward = 0;
//         }
        
//         // Rotește în direcția corectă
//         if (forward) {
//             for (i = 0; i <= lungime; i++) {
//                 temp[i] = lant[(min_pos + i) % (lungime + 1)];
//             }
//         } else {
//             for (i = 0; i <= lungime; i++) {
//                 temp[i] = lant[(min_pos - i + lungime + 1) % (lungime + 1)];
//             }
//         }
        
//         memcpy(lant, temp, (lungime + 1) * sizeof(int));
//         free(temp);
//     }
// }

// static int backtrack_calls = 0;
// static const int MAX_BACKTRACK_CALLS = 100000; // Limită pentru numărul de apeluri

// // Backtracking pentru găsirea lanțului Hamiltonian
// void backtrack_hamiltonian(int **matrice_adiacenta, int nr_noduri, int *lant_curent,
//                            int *vizitat, int pozitie, int *lant_maxim, int *lungime_maxima,
//                            nod_graf *noduri)
// {
//     // Verifică limita de apeluri
//     if (++backtrack_calls > MAX_BACKTRACK_CALLS)
//     {
//         return;
//     }

//     // Verifică dacă am găsit un lanț mai lung
//     if (pozitie > *lungime_maxima)
//     {
//         *lungime_maxima = pozitie;
//         int i;
//         for (i = 0; i <= pozitie; i++)
//         {
//             lant_maxim[i] = lant_curent[i];
//         }
//     }
//     else if (pozitie == *lungime_maxima && pozitie > 0)
//     {
//         // Verifică dacă noul lanț este mai bun conform regulilor
//         if (compara_lanturi(lant_curent, lant_maxim, pozitie, noduri) < 0)
//         {
//             int i;
//             for (i = 0; i <= pozitie; i++)
//             {
//                 lant_maxim[i] = lant_curent[i];
//             }
//         }
//     }

//     // Optimizare: dacă am găsit deja un lanț Hamiltonian complet, nu mai căutăm
//     if (*lungime_maxima == nr_noduri - 1)
//     {
//         return;
//     }

//     // Creează un array de noduri nevizitate sortate după coordonate
//     int *candidati = (int *)malloc(nr_noduri * sizeof(int));
//     int nr_candidati = 0;

//     int i;
//     for (i = 0; i < nr_noduri; i++)
//     {
//         if (!vizitat[i] && (pozitie == 0 || matrice_adiacenta[lant_curent[pozitie]][i]))
//         {
//             candidati[nr_candidati++] = i;
//         }
//     }

//     // Sortează candidații după coordonate
//     int j;
//     for (i = 0; i < nr_candidati - 1; i++)
//     {
//         for (j = i + 1; j < nr_candidati; j++)
//         {
//             if (noduri[candidati[i]].linie > noduri[candidati[j]].linie ||
//                 (noduri[candidati[i]].linie == noduri[candidati[j]].linie &&
//                  noduri[candidati[i]].coloana > noduri[candidati[j]].coloana))
//             {
//                 int temp = candidati[i];
//                 candidati[i] = candidati[j];
//                 candidati[j] = temp;
//             }
//         }
//     }

//     // Încearcă candidații în ordinea sortată
//     for (i = 0; i < nr_candidati; i++)
//     {
//         int next_node = candidati[i];
//         vizitat[next_node] = 1;
//         lant_curent[pozitie + 1] = next_node;
//         backtrack_hamiltonian(matrice_adiacenta, nr_noduri, lant_curent, vizitat,
//                               pozitie + 1, lant_maxim, lungime_maxima, noduri);
//         vizitat[next_node] = 0;
//     }

//     free(candidati);
// }

// // Găsește cel mai lung lanț Hamiltonian
// void gaseste_lant_hamiltonian(int **matrice_adiacenta, int nr_noduri, int *lant_maxim,
//                               int *lungime_maxima, nod_graf *noduri)
// {
//     if (nr_noduri == 0)
//     {
//         *lungime_maxima = -1;
//         return;
//     }

//     *lungime_maxima = -1;
//     int *lant_curent = (int *)malloc((nr_noduri + 1) * sizeof(int));
//     int *vizitat = (int *)calloc(nr_noduri, sizeof(int));

//     // Resetează contorul pentru fiecare căutare nouă
//     backtrack_calls = 0;

//     // Creează un array de indici sortați după coordonate (linie, apoi coloană)
//     int *indici_sortati = (int *)malloc(nr_noduri * sizeof(int));
//     int i, j;
//     for (i = 0; i < nr_noduri; i++)
//     {
//         indici_sortati[i] = i;
//     }

//     // Sortează indicii după coordonatele nodurilor
//     for (i = 0; i < nr_noduri - 1; i++)
//     {
//         for (j = i + 1; j < nr_noduri; j++)
//         {
//             if (noduri[indici_sortati[i]].linie > noduri[indici_sortati[j]].linie ||
//                 (noduri[indici_sortati[i]].linie == noduri[indici_sortati[j]].linie &&
//                  noduri[indici_sortati[i]].coloana > noduri[indici_sortati[j]].coloana))
//             {
//                 int temp = indici_sortati[i];
//                 indici_sortati[i] = indici_sortati[j];
//                 indici_sortati[j] = temp;
//             }
//         }
//     }

//     // Încearcă să pornească din fiecare nod în ordinea sortată
//     for (i = 0; i < nr_noduri; i++)
//     {
//         int start_node = indici_sortati[i];
//         vizitat[start_node] = 1;
//         lant_curent[0] = start_node;
//         backtrack_hamiltonian(matrice_adiacenta, nr_noduri, lant_curent, vizitat,
//                               0, lant_maxim, lungime_maxima, noduri);
//         vizitat[start_node] = 0;

//         // Dacă am depășit limita de apeluri, ieșim
//         if (backtrack_calls > MAX_BACKTRACK_CALLS)
//         {
//             break;
//         }

//         // Dacă am găsit un lanț Hamiltonian complet, nu mai căutăm
//         if (*lungime_maxima == nr_noduri - 1)
//         {
//             break;
//         }
//     }

//     free(lant_curent);
//     free(vizitat);
//     free(indici_sortati);
// }

// // Procesarea arborelui pentru Task 4
// void procesare_arbore_task4(nod_arbore *nod, char **matrice_curenta, int N, int M, FILE *out, int nivel)
// {
//     if (nod == NULL)
//     {
//         return;
//     }

//     // Reconstituie matricea pentru nodul curent
//     char **matrice_nod = copiere_matrice(matrice_curenta, N, M);
//     reconstituire_matrice(matrice_nod, nod->modificari, N, M);

//     // Construiește graful
//     nod_graf *noduri_graf = NULL;
//     int nr_noduri = 0;

//     // Alocăm matrice de adiacență pentru cel mult N*M noduri
//     int **matrice_adiacenta = (int **)malloc(N * M * sizeof(int *));

//     construire_graf(matrice_nod, N, M, &noduri_graf, &nr_noduri, matrice_adiacenta);

//     // Găsește cel mai lung lanț Hamiltonian
//     int *lant_maxim = (int *)malloc((nr_noduri + 1) * sizeof(int));
//     int lungime_maxima = -1;

//     if (nr_noduri > 0 && nr_noduri <= 50)
//     { // Limitez la 50 de noduri pentru performanță
//         gaseste_lant_hamiltonian(matrice_adiacenta, nr_noduri, lant_maxim, &lungime_maxima, noduri_graf);

//         if (lungime_maxima >= 0) {
//             optimizeaza_lant(lant_maxim, lungime_maxima, noduri_graf);
//         }
//     }
//     else if (nr_noduri > 50)
//     {
//         // Pentru grafuri foarte mari, returnez -1
//         lungime_maxima = -1;
//     }

//     // Afișează rezultatul
//     fprintf(out, "%d\n", lungime_maxima);
//     if (lungime_maxima >= 0)
//     {
//         int i;
//         for (i = 0; i <= lungime_maxima; i++)
//         {
//             fprintf(out, "(%d,%d)", noduri_graf[lant_maxim[i]].linie,
//                     noduri_graf[lant_maxim[i]].coloana);
//             if (i < lungime_maxima)
//             {
//                 fprintf(out, " ");
//             }
//         }
//         fprintf(out, "\n");
//     }

//     // Eliberează memoria pentru graf
//     if (noduri_graf)
//     {
//         free(noduri_graf);
//     }
//     free(lant_maxim);
//     eliberare_matrice_int(matrice_adiacenta, nr_noduri > 0 ? nr_noduri : N * M);

//     // Procesează recursiv copiii
//     if (nod->stanga)
//     {
//         procesare_arbore_task4(nod->stanga, matrice_nod, N, M, out, nivel + 1);
//     }
//     if (nod->dreapta)
//     {
//         procesare_arbore_task4(nod->dreapta, matrice_nod, N, M, out, nivel + 1);
//     }

//     eliberare_matrice_t2(matrice_nod, N);
// }

// void eliberare_matrice_int(int **matrice, int n)
// {
//     if (matrice == NULL)
//         return;
//     int i;
//     for (i = 0; i < n; i++)
//     {
//         if (matrice[i] != NULL)
//         {
//             free(matrice[i]);
//         }
//     }
//     free(matrice);
// }
