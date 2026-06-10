#include "calculs_trajectoire.h"
#include "vecteurs.h"
#include "lecture_ecriture.h"


// Corps du programme
int main() {
    planete listePlanetes[NB_PLANETES] = {0};

    // lecture des données des planètes
    lectureDonneesInitialesPlanetes("data/donnees_initiales_planetes.txt", listePlanetes);
    
    for(int i = 0; i < NB_PLANETES; i++)
        initialiserTrajectoirePlanete(&listePlanetes[i]);



    // Tests unitaires
    printf("Hello world!\n");
    // planeteTest(listePlanetes);
    // vectorTest();

    // libération de la mémoire
    for (int i = 0; i < NB_PLANETES; i++)
        free(listePlanetes[i].nom);
    return EXIT_SUCCESS;
}
