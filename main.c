#include "header.h"

int main(int argc, const char *argv[])
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
           
            free(q[i]);
        }

        
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
            char **nou = copie_t2(m, N, M); // Creez o copie a matricei curente pentru a calcula noua generație
            celula *mode = NULL; // pointer catre inceputul unei liste de tip celula
                                 // aceasta lista va contine toate celulele care s au modificat intr o anumita generatie
                                 //=lista modificari pentru generatia curenta
            for (i = 0; i < N; i++)
            {
                for (j = 0; j < M; j++)
                {
                    int vecini = vecinii(m, N, M, i, j); // calc vecinii

                    if ((m[i][j] == 'X' && (vecini < 2 || vecini > 3)) || (m[i][j] == '+' && vecini == 3)) // aplic regulile din GOL
                    {   // Inversez starea celulei în matricea nouă
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
        eliberare_stiva_generatii(stiva);
        eliberare_matrice_t2(m, N);
    }

    else if (T == 3)
    {
        // Creez rădăcina arborelui
        nod_arbore *radacina = creare_nod();
    
        // Pentru rădăcină, modificările sunt celulele vii din matricea inițială
        for (i = 0; i < N; i++) {
            for (j = 0; j < M; j++) {
                if (m[i][j] == 'X') {
                    adaugare_t2(&(radacina->modificari), i, j);
                }
            }
        }
        
        // Construiesc arborele până la nivelul K
        construire_arbore(radacina, m, 0, K, N, M);
        
        // Creez o matrice goală pentru început
        char **matrice_goala = (char **)malloc(N * sizeof(char *));
        for (i = 0; i < N; i++) {
            matrice_goala[i] = (char *)malloc(M * sizeof(char));
            for (j = 0; j < M; j++) {
                matrice_goala[i][j] = '+';
            }
        }
        
        // Parcurg arborele în preordine și afișez matricile
        parcurgere_preordine(radacina, matrice_goala, N, M, out);
        
        // Eliberez memoria
        eliberare_matrice_t2(matrice_goala, N);
        eliberare_arbore(radacina);
        
        fclose(out);
        
    }
    // else if (T == 4) {
    //     // Creez arborele la fel ca la Task 3
    //     nod_arbore *radacina = creare_nod();
        
    //     // Pentru rădăcină, modificările sunt celulele vii din matricea inițială
    //     for (i = 0; i < N; i++) {
    //         for (j = 0; j < M; j++) {
    //             if (m[i][j] == 'X') {
    //                 adaugare_t2(&(radacina->modificari), i, j);
    //             }
    //         }
    //     }
        
    //     // Construiesc arborele până la nivelul K
    //     construire_arbore(radacina, m, 0, K, N, M);
        
    //     // Creez o matrice goală pentru început
    //     char **matrice_goala = (char **)malloc(N * sizeof(char *));
    //     for (i = 0; i < N; i++) {
    //         matrice_goala[i] = (char *)malloc(M * sizeof(char));
    //         for (j = 0; j < M; j++) {
    //             matrice_goala[i][j] = '+';
    //         }
    //     }
        
    //     // Procesez arborele și găsesc lanțurile Hamiltoniene
    //     procesare_arbore_task4(radacina, matrice_goala, N, M, out, 0);
        
    //     // Eliberez memoria
    //     eliberare_matrice_t2(matrice_goala, N);
    //     eliberare_arbore(radacina);
        
    //     fclose(out);
    // }
    
    for (i = 0; i < N; i++)
    {
        free(m[i]);
    }

    free(m);

    return 0;
}
