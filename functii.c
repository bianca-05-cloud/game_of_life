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

// Functie pentru afisare matrice
void afisare_matrice(char **m, int N, int M)
{
    int i, j;
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < M; j++)
        {
            printf("%c", m[i][j]);
        }
        printf("\n");
    }
}

// Functie pentru numararea vecinilor vii ai unei celule
int vecinii(char **m, int N, int M, int i, int j)
{
    int x[] = {-1, -1, -1, 0, 0, 1, 1, 1}; // deplasare pe linie
    int y[] = {-1, 0, 1, -1, 1, -1, 0, 1}; // deplasare pe coloana

    int d;
    int aux = 0; // contor pentru vecinii vii

    // parcurg fiecare din cei 8 vecini posibili ai unei celule
    for (d = 0; d < 8; d++)
    {
        int ni = i + x[d]; // calculez linia vecinului
        int nj = j + y[d]; // calculez coloana vecinului

        // verific daca vecinul este in interiorul matricei
        if (ni >= 0 && ni < N && nj >= 0 && nj < M)
        {
            // verific daca vecinul este viu
            if (m[ni][nj] == 'X')
            {
                aux++;
            }
        }
    }

    return aux; // returnez nr total de vecini vii
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
    {
        return;
    }

    afisare_t2(stiva->next, out);

    fprintf(out, "%d ", stiva->k);
    celula *curent = stiva->x;

    while (curent)
    {
        if (curent->next != NULL)
            fprintf(out, "%d %d ", curent->l, curent->c);
        else if (curent->next == NULL)
            fprintf(out, "%d %d", curent->l, curent->c);

        curent = curent->next;
    }

    fprintf(out, "\n");
}

// task 3

void adaugare_la_inceput_t3(lista **cap_matrice, int i, int j)
{
    lista *nou = (lista *)malloc(sizeof(lista));
    nou->x.l = i;
    nou->x.c = j;
    nou->next = *cap_matrice;
    *cap_matrice = nou;
}

void adaugare_la_final_t3(lista **cap_matrice, int i, int j)
{
    if (*cap_matrice == NULL)
    {
        adaugare_la_inceput_t3(cap_matrice, i, j);
        return;
    }

    lista *aux = *cap_matrice;
    lista *nou = (lista *)malloc(sizeof(lista));
    nou->x.l = i;
    nou->x.c = j;
    nou->next = NULL;

    while (aux->next != NULL)
        aux = aux->next;
    aux->next = nou;
}

lista *matrice_devine_lista_t3(char **veche, char **noua, int N, int M)
{
    lista *cap_matrice = NULL;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            if (veche[i][j] != noua[i][j])
            {
                adaugare_la_final_t3(&cap_matrice, i, j);
            }
        }
    }
    return cap_matrice;
}

void actualizare_matrice_dreapta_t3(char **m, char **q, int N, int M)
{
    int i, j, vecinii_vii;

    for (i = 0; i < N; i++)
    {
        for (j = 0; j < M; j++)
        {
            vecinii_vii = vecinii(m, N, M, i, j);

            if (m[i][j] == 'X' && (vecinii_vii < 2 || vecinii_vii > 3))
                q[i][j] = '+';
            else if (m[i][j] == '+' && vecinii_vii == 3)
                q[i][j] = 'X';
            else
                q[i][j] = m[i][j];
        }
    }
}

void actualizare_matrice_stanga_t3(char **m, char **p, int N, int M)
{
    int i, j, vecinii_vii;

    for (i = 0; i < N; i++)
    {
        for (j = 0; j < M; j++)
        {
            vecinii_vii = vecinii(m, N, M, i, j);

            if (vecinii_vii == 2)
                p[i][j] = 'X';
            else
                p[i][j] = m[i][j];
        }
    }
}

void afisare_lista_t3(lista *cap) {
    printf("Lista modificari: ");
    while (cap) {
        printf("(%d,%d) ", cap->x.l, cap->x.c);
        cap = cap->next;
    }
    printf("\n");
}

void afisare_node_t3(node *n) {
    if (!n) {
        printf("Nod NULL\n");
        return;
    }
    printf("Nod cu lista: ");
    afisare_lista_t3(n->val);
}

void afisare_matrice_t3(char **m, int N, int M) {
    printf("Matrice:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++)
            printf("%c", m[i][j]);
        printf("\n");
    }
}

void creeare_arbore_t3(node *root, lista **capete_dreapta, lista **capete_stanga, int nivel, int max_k)
{
    if (nivel == max_k)
        return;

    root->left = (node *)malloc(sizeof(node));
    root->left->val = capete_stanga[nivel];
    root->left->left = root->left->right = NULL;
    afisare_node_t3(root->left);

    root->right = (node *)malloc(sizeof(node));
    root->right->val = capete_dreapta[nivel];
    root->right->left = root->right->right = NULL;
    afisare_node_t3(root->right);

    creeare_arbore_t3(root->left, capete_dreapta, capete_stanga, nivel + 1, max_k);
    creeare_arbore_t3(root->right, capete_dreapta, capete_stanga, nivel + 1, max_k);
}

void trecere_din_lista_in_matrice_t3(lista *cap, char **m, int N, int M)
{
    // Alocăm matrice pentru a marca coordonatele deja modificate
    int **vizitat = (int **)malloc(N * sizeof(int *));
    for (int i = 0; i < N; i++)
    {
        vizitat[i] = (int *)calloc(M, sizeof(int));
    }

    while (cap != NULL)
    {
        int l = cap->x.l;
        int c = cap->x.c;

        if (!vizitat[l][c])
        {
            m[l][c] = (m[l][c] == 'X') ? '+' : 'X';
            vizitat[l][c] = 1;
        }

        cap = cap->next;
    }

    // Eliberăm matricea auxiliară
    for (int i = 0; i < N; i++)
        free(vizitat[i]);
    free(vizitat);
}

void copie_matrice(char **sursa, char **dest, int N, int M)
{
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            dest[i][j] = sursa[i][j];
}

void preordine_t3(node *root, char **m, int N, int M, FILE *out, int nivel)
{
    if (root == NULL)
        return;

    char **matrice_temp = (char **)malloc(N * sizeof(char *));
    for (int i = 0; i < N; i++)
        matrice_temp[i] = (char *)malloc(M * sizeof(char));

    copie_matrice(m, matrice_temp, N, M);

    if (nivel > 0)
        trecere_din_lista_in_matrice_t3(root->val, matrice_temp, N, M);

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
            fprintf(out, "%c", matrice_temp[i][j]);
        fprintf(out, "\n");
    }
    fprintf(out, "\n");

    preordine_t3(root->left, m, N, M, out, nivel + 1);


    copie_matrice(matrice_temp, m, N, M);


    preordine_t3(root->right, m, N, M, out, nivel + 1);

    //copie_matrice(matrice_temp, m, N, M);

    for (int i = 0; i < N; i++)
        free(matrice_temp[i]);
    free(matrice_temp);
}

// task 4

void extrage_celule_vii(char **m, int N, int M, Celula **celule, int *nr_celule)
{
    int i, j, contor = 0;

    // Număr celulele vii
    for (i = 0; i < N; i++)
        for (j = 0; j < M; j++)
            if (m[i][j] == 'X')
                contor++;

    // Aloc vectorul de celule (vii)
    *celule = (Celula *)malloc(contor * sizeof(Celula));
    if (*celule == NULL && contor > 0)
    {
        *nr_celule = 0;
        return;
    }

    //  Salvez coordonatele celulelor vii
    int k = 0;
    for (i = 0; i < N; i++)
        for (j = 0; j < M; j++)
            if (m[i][j] == 'X')
            {
                (*celule)[k].linie = i;
                (*celule)[k].coloana = j;
                k++;
            }

    //  Setez numărul de celule vii
    *nr_celule = contor;
}

int **construieste_matrice_adiacenta(Celula *celule, int nr_celule)
{
    int **adj = (int **)malloc(nr_celule * sizeof(int *));
    for (int i = 0; i < nr_celule; i++)
    {
        adj[i] = (int *)calloc(nr_celule, sizeof(int));
    }

    for (int i = 0; i < nr_celule; i++)
    {
        for (int j = i + 1; j < nr_celule; j++)
        {
            int dl = abs(celule[i].linie - celule[j].linie);
            int dc = abs(celule[i].coloana - celule[j].coloana);
            //verific diferența de drum între pozițiile a 2 celule 
            if ((dl <= 1 && dc <= 1) && !(dl == 0 && dc == 0))
            {
                adj[i][j] = adj[j][i] = 1;
            }
        }
    }
    return adj;
}

void gaseste_componente_conexe(int **adj, Celula *celule, int nr_celule, int *componenta, int *nr_componente)
{
    int *vizitat = calloc(nr_celule, sizeof(int));
    int *queue = malloc(nr_celule * sizeof(int));
    int comp = 0;

    for (int i = 0; i < nr_celule; i++)
    {
        if (!vizitat[i])
        {
            // BFS
            int front = 0, rear = 0;
            queue[rear++] = i;
            vizitat[i] = 1;
            componenta[i] = comp;

            while (front < rear)
            {
                int nod = queue[front++];
                for (int j = 0; j < nr_celule; j++)
                {
                    if (adj[nod][j] && !vizitat[j])
                    {
                        queue[rear++] = j;
                        vizitat[j] = 1;
                        componenta[j] = comp;
                    }
                }
            }
            comp++;
        }
    }
    *nr_componente = comp;
    free(vizitat);
    free(queue);
}

// Funcție auxiliară pentru compararea a doua drumuri dupa reguli (linie/coloana minim)
int compara_lanturi(Celula *celule, int *drum1, int *drum2, int lungime)
{
    for (int i = 0; i < lungime; i++)
    {
        if (celule[drum1[i]].linie != celule[drum2[i]].linie)
            return celule[drum1[i]].linie - celule[drum2[i]].linie;
        if (celule[drum1[i]].coloana != celule[drum2[i]].coloana)
            return celule[drum1[i]].coloana - celule[drum2[i]].coloana;
    }
    return 0;
}

// Backtracking pentru cel mai lung drum elementar dintr-o componenta
void backtrack(int **adj, Celula *celule, int *noduri, int dim, int poz, int *vizitat, int *drum_curent, int lungime,
               int *drum_max, int *lungime_max)
{
    vizitat[poz] = 1;
    drum_curent[lungime] = poz;

    // Daca am gasit un drum mai lung, sau la fel de lung dar cu prioritizare mai buna, il salvez
    if (lungime + 1 > *lungime_max)
    {
        for (int i = 0; i <= lungime; i++)
            drum_max[i] = drum_curent[i];
        *lungime_max = lungime + 1;
    }
    else if (lungime + 1 == *lungime_max)
    {
        if (compara_lanturi(celule, noduri, drum_curent, lungime + 1) > 0)
        {
            for (int i = 0; i <= lungime; i++)
                drum_max[i] = drum_curent[i];
        }
    }

    // Exploreaza vecinii nevizitati
    for (int i = 0; i < dim; i++)
    {
        if (!vizitat[i] && adj[noduri[poz]][noduri[i]])
        {
            backtrack(adj, celule, noduri, dim, i, vizitat, drum_curent, lungime + 1, drum_max, lungime_max);
        }
    }

    vizitat[poz] = 0;
}

// Functia principala pentru cautarea lanturilor Hamiltoniene
void cauta_lanturi_hamiltoniene(int **adj, Celula *celule, int *componenta, int nr_celule, int *nr_componente, FILE* out)
{
    int lungime_max_glob = -1;
    int *drum_max_glob = NULL;
    int comp_aleasa = -1;

    for (int comp = 0; comp < *nr_componente; comp++)
    {
        // Extrage nodurile din componenta curenta
        int *noduri = (int *)malloc(nr_celule * sizeof(int));
        int dim = 0;
        for (int i = 0; i < nr_celule; i++)
            if (componenta[i] == comp)
                noduri[dim++] = i;

        if (dim == 0 || dim>11)
        {
            free(noduri);
            continue;
        }

        int *drum_max = (int *)malloc(dim * sizeof(int));
        int *drum_curent = (int *)malloc(dim * sizeof(int));
        int *vizitat = (int *)calloc(dim, sizeof(int));
        int lungime_max = -1;

        // Pentru fiecare nod din componenta, porneste backtracking
        for (int start = 0; start < dim; start++)
        {
            for (int i = 0; i < dim; i++)
                vizitat[i] = 0;
            backtrack(adj, celule, noduri, dim, start, vizitat, drum_curent, 0, drum_max, &lungime_max);
        }

        // Daca am gasit un lant mai lung, sau la fel de lung dar cu prioritizare mai buna, il salvez global
        if (lungime_max > lungime_max_glob)
        {
            if (drum_max_glob)
                free(drum_max_glob);
            drum_max_glob = (int *)malloc(lungime_max * sizeof(int));
            for (int i = 0; i < lungime_max; i++)
                drum_max_glob[i] = noduri[drum_max[i]];
            lungime_max_glob = lungime_max;
            comp_aleasa = comp;
        }
        else if (lungime_max == lungime_max_glob && lungime_max > 0)
        {
            // Prioritizare dupa reguli
            if (compara_lanturi(celule, drum_max_glob, drum_max, lungime_max) > 0)
            {
                for (int i = 0; i < lungime_max; i++)
                    drum_max_glob[i] = noduri[drum_max[i]];
                comp_aleasa = comp;
            }
        }

        free(noduri);
        free(drum_max);
        free(drum_curent);
        free(vizitat);
    }

    // Afiseaza rezultatul
    if (lungime_max_glob < 2)
    {
        fprintf(out, "-1\n");
    }
    else
    {
        fprintf(out, "%d\n", lungime_max_glob-1);
        for (int i = 0; i < lungime_max_glob; i++)
            fprintf(out, "(%d ,%d) ", celule[drum_max_glob[i]].linie, celule[drum_max_glob[i]].coloana);
        fprintf(out, "\n");
    }
    if (drum_max_glob)
        free(drum_max_glob);
}

// void afiseaza_lant(FILE *out, Celula *celule, int *drum, int lungime)
// {
//     if (lungime < 2)
//     {
//         fprintf(out, "-1\n");
//         return;
//     }
//     fprintf(out, "%d\n", lungime);
//     for (int i = 0; i < lungime; i++)
//     {
//         fprintf(out, "(%d ,%d) ", celule[drum[i]].linie + 1, celule[drum[i]].coloana + 1);
//     }
//     fprintf(out, "\n");
// }

void preordine_task4(node *root, char **matrice_generatie, int N, int M, FILE *out, int nivel) {
    if (!root) return;

    char **matrice_temp = (char **)malloc(N * sizeof(char *));
    for (int i = 0; i < N; i++)
        matrice_temp[i] = (char *)malloc(M * sizeof(char));
    copie_matrice(matrice_generatie, matrice_temp, N, M);

    //  Reconstruiește matricea generației curente
    trecere_din_lista_in_matrice_t3(root->val, matrice_temp, N, M);

    // Extrage celulele vii din matricea corectă!
    Celula *celule = NULL;
    int nr_celule = 0;
    extrage_celule_vii(matrice_temp, N, M, &celule, &nr_celule);

    if (nr_celule == 0) {
        fprintf(out, "-1\n");
    } else {
        // Construiește matricea de adiacență
        int **adj = construieste_matrice_adiacenta(celule, nr_celule);
        int *componenta = (int *)malloc(nr_celule * sizeof(int));
        int nr_componente = 0;
        //  Găsește componentele conexe
        gaseste_componente_conexe(adj, celule, nr_celule, componenta, &nr_componente);
        //  Caută și afișează lanțul Hamiltonian maxim
        cauta_lanturi_hamiltoniene(adj, celule, componenta, nr_celule, &nr_componente, out);

        for (int i = 0; i < nr_celule; i++)
            free(adj[i]);
        free(adj);
        free(componenta);
    }
    free(celule);

    // Parcurgere recursivă pentru copii
    preordine_task4(root->left, matrice_temp, N, M, out, nivel+1);
    preordine_task4(root->right, matrice_temp, N, M, out, nivel+1);

    for (int i = 0; i < N; i++)
        free(matrice_temp[i]);
    free(matrice_temp);
}

