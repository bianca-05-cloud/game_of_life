#include "header.h"

int main(int argc, char *argv[])
{
    int T, N, M, K;

    FILE *in;
    FILE *out;
    in = fopen(argv[1], "rt");
    // printf("Fisierul de in este: %s\n", argv[1]);

    if (in == NULL)
    {
        puts("Fisierul nu poate fi deschis");
        exit(1);
    }

    out = fopen(argv[2], "wt");

    if (out == NULL)
    {
        puts("Fisierul nu poate fi deschis");
        exit(1);
    }
    int i, j, k;

    fscanf(in, "%d", &T);
    fscanf(in, "%d %d", &N, &M);
    fscanf(in, "%d", &K);

    // Alocăm memorie pentru matricea principală (m)
    char **m = (char **)malloc(N * sizeof(char *));
    for (i = 0; i < N; i++)
    {
        m[i] = (char *)malloc(M * sizeof(char));
    }

    citire_matrice(m, in, N, M); // citim matricea inițială
    fclose(in);

    if (T == 1)
    {

        // Alocăm memorie pentru matricea auxiliară (q)

        char **q = (char **)malloc(N * sizeof(char *));

        for (i = 0; i < N; i++)
        {
            q[i] = (char *)malloc(M * sizeof(char));
        }

        // citire_matrice(m, in, N, M);  // citim matricea inițială
        // fclose(in);

        // Rulez jocul pentru K generații
        for (k = 0; k <= K; k++)
        {

            // Scriem rezultatul pentru generația curentă în fișierul de ieșire
            for (i = 0; i < N; i++)
            {
                for (j = 0; j < M; j++)
                {
                    fprintf(out, "%c", m[i][j]); // scriem în fișier
                }
                fprintf(out, "\n");
            }

            // Dacă nu este ultima generație, adăugăm o linie goală
            fprintf(out, "\n");

            actualizare_matrice(m, q, N, M);
        }

        fclose(out);

        // Eliberăm memoria alocată
        for (i = 0; i < N; i++)
        {
            // free(m[i]);
            free(q[i]);
        }

        // free(m);
        free(q);
    }

    else if (T == 2)
    {

        // voi creea stiva care stocheaza generatiile si elementele care se schimba

        generatie *stiva = NULL;
        // int k;
        // rulez ptr K generatii
        for (k = 1; k <= K; k++)
        {
            char **nou = copie_t2(m, N, M);
            celula *mode = NULL; // pointer catre inceputul unei liste de tip celula
                                 // aceasta lista va contine toate celulele care s au modificat intr o anumita generatie
                                 //=lista modificari pentru generatia curenta
            for (i = 0; i < N; i++)
            {
                for (j = 0; j < M; j++)
                {
                    int vecini = vecinii(m, N, M, i, j); // calc vecinii

                    if ((m[i][j] == 'X' && (vecini < 2 || vecini > 3)) || (m[i][j] == '+' && vecini == 3)) // aplic regulile din GOL
                    {
                        nou[i][j] = (m[i][j] == 'X') ? '+' : 'X'; // transf GOL
                        adaugare_t2(&mode, i, j);                 // creeaza un nod nou cu coord i, j si adauga acel nod in lista
                        // printf("Modificare: (%d, %d)\n", i, j); // DEBUG
                    }
                }
            }

            if (mode != NULL)

            {
                push_t2(&stiva, k, mode); // adauga o noua generatie in varful stivei
                // printf("Push: generatie %d, modificari detectate.\n", k);
            }

            else

            {
                // printf("Stop la gen %d: fara modificari.\n", k);
                eliberare_matrice_t2(nou, N);
                break;
            }
            eliberare_matrice_t2(m, N);
            m = nou;
        }

        // printf("Afisez generatiile in fisier...\n");

        afisare_t2(stiva, out);

        fclose(out);
        eliberare_matrice_t2(m, N);
    }

    else if (T == 3)
    {
        char **matrice_goala = (char **)malloc(N * sizeof(char *));
        for (int i = 0; i < N; i++)
        {
            matrice_goala[i] = (char *)malloc(M * sizeof(char));
            for (int j = 0; j < M; j++)
            {
                matrice_goala[i][j] = m[i][j];
            }
        }

        // conversie initiala in lista
        lista *cap_matrice = matrice_devine_lista_t3(m, matrice_goala, N, M);

        // alocare matrici auxiliare
        char **q1 = (char **)malloc(N * sizeof(char *)); // GOL normal
        char **p1 = (char **)malloc(N * sizeof(char *)); // GOL modificat
        for (int i = 0; i < N; i++)
        {
            q1[i] = (char *)malloc(M * sizeof(char));
            p1[i] = (char *)malloc(M * sizeof(char));
        }

        // vectorii de liste pentru capete
        lista **capete_dreapta = (lista **)malloc(K * sizeof(lista *));
        lista **capete_stanga = (lista **)malloc(K * sizeof(lista *));
        int k1;

        char **copie_dreapta = (char **)malloc(N * sizeof(char *));
        char **copie_stanga = (char **)malloc(N * sizeof(char *));

        for (i = 0; i < N; i++)
        {
            copie_dreapta[i] = (char *)malloc(M * sizeof(char));
            copie_stanga[i] = (char *)malloc(M * sizeof(char));

            for (j = 0; j < M; j++)
            {
                copie_dreapta[i][j] = m[i][j];
                copie_stanga[i][j] = m[i][j];
            }
        }

                for (k1 = 0; k1 < K; k1++)
                {
                    // Actualizare Game of Life normal (dreapta)
                    actualizare_matrice_dreapta_t3(copie_dreapta, q1, N, M);
                    capete_dreapta[k1] = matrice_devine_lista_t3(copie_dreapta, q1, N, M);
                    copie_matrice(q1, copie_dreapta, N, M);

                    // Actualizare Game of Life modificat (stanga)
                    actualizare_matrice_stanga_t3(copie_stanga, p1, N, M);
                    capete_stanga[k1] = matrice_devine_lista_t3(copie_stanga, p1, N, M);
                    copie_matrice(p1, copie_stanga, N, M);
                }
            
        

        // radacina arbore
        node *root = (node *)malloc(sizeof(node));
        root->left = root->right = NULL;
        root->val = cap_matrice;

        creeare_arbore_t3(root, capete_dreapta, capete_stanga, 0, K);

        // matrice temporara pt reconstructie
        char **matrice_output = (char **)malloc(N * sizeof(char *));
        for (i = 0; i < N; i++)
            matrice_output[i] = (char *)malloc(M * sizeof(char));
        copie_matrice(m, matrice_output, N, M);
        preordine_t3(root, matrice_output, N, M, out, 0);
        
        fclose(out);

        for (i = 0; i < N; i++)
        {

            free(q1[i]);
            free(p1[i]);
            free(matrice_output[i]);
        }

        free(q1);
        free(p1);
        free(matrice_output);
        for (int i = 0; i < N; i++)
            free(matrice_goala[i]);
        free(matrice_goala);
    }

    else if (T == 4)
    {       char **matrice_goala = (char **)malloc(N * sizeof(char *));
            for (int i = 0; i < N; i++)
            {
                matrice_goala[i] = (char *)malloc(M * sizeof(char));
                for (int j = 0; j < M; j++)
                {
                    matrice_goala[i][j] = '+'; // toți morți
                }
            }

            // conversie initiala in lista
            lista *cap_matrice = matrice_devine_lista_t3(matrice_goala, m, N, M);

            // alocare matrici auxiliare
            char **q1 = (char **)malloc(N * sizeof(char *)); // GOL normal
            char **p1 = (char **)malloc(N * sizeof(char *)); // GOL modificat
            for (int i = 0; i < N; i++)
            {
                q1[i] = (char *)malloc(M * sizeof(char));
                p1[i] = (char *)malloc(M * sizeof(char));
            }

            // vectorii de liste pentru capete
            lista **capete_dreapta = (lista **)malloc(K * sizeof(lista *));
            lista **capete_stanga = (lista **)malloc(K * sizeof(lista *));
            int k1;

            char **copie_dreapta = (char **)malloc(N * sizeof(char *));
            char **copie_stanga = (char **)malloc(N * sizeof(char *));

            for (i = 0; i < N; i++)
            {
                copie_dreapta[i] = (char *)malloc(M * sizeof(char));
                copie_stanga[i] = (char *)malloc(M * sizeof(char));

                for (j = 0; j < M; j++)
                {
                    copie_dreapta[i][j] = m[i][j];
                    copie_stanga[i][j] = m[i][j];
                }
            }

            for (k1 = 0; k1 < K; k1++)
            {
                // Actualizare Game of Life normal (dreapta)
                actualizare_matrice_dreapta_t3(copie_dreapta, q1, N, M);
                capete_dreapta[k1] = matrice_devine_lista_t3(copie_dreapta, q1, N, M);

                for (i = 0; i < N; i++)
                    for (j = 0; j < M; j++)
                        copie_dreapta[i][j] = q1[i][j];

                // Actualizare Game of Life modificat (stanga)
                actualizare_matrice_stanga_t3(copie_stanga, p1, N, M);
                capete_stanga[k1] = matrice_devine_lista_t3(copie_stanga, p1, N, M);

                for (i = 0; i < N; i++)
                    for (j = 0; j < M; j++)
                        copie_stanga[i][j] = p1[i][j];
            }

        node *root = (node *)malloc(sizeof(node));
            root->left = root->right = NULL;
            root->val = cap_matrice;

            creeare_arbore_t3(root, capete_dreapta, capete_stanga, 0, K);

        char **matrice_generatie = (char **)malloc(N * sizeof(char *));
        for (int i = 0; i < N; i++)
            matrice_generatie[i] = (char *)malloc(M * sizeof(char));

        preordine_task4(root, matrice_generatie, N, M, out, 0);

        for (int i = 0; i < N; i++)
            free(matrice_generatie[i]);
        free(matrice_generatie);
        fclose(out);
    }

    for (i = 0; i < N; i++)
    {
        free(m[i]);
    }

    free(m);

    return 0;
}