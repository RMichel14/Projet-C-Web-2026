#include "calculs_trajectoire.h"
#include "vecteurs.h"
#include "lecture_ecriture.h"


// Corps du programme
int main() {
    planete listePlanetes[NB_PLANETES] = {0};

    // lecture des données initiales des planètes
    lectureDonneesInitialesPlanetes("data/donnees_initiales_planetes.txt", listePlanetes);

    // initialisation des planetes
    initialiserTrajectoirePlanetes(listePlanetes);

    // calcul des points selon la méthode d'Euler
    calculerTousLesPointsEuler(listePlanetes);

    // exporter les données
    exporterJSON("data/data.json", listePlanetes);

    // Tests unitaires
    printf("Hello world!\n");
    // planeteTest(listePlanetes);
    // vectorTest();

    // libération de la mémoire
    for (int i = 0; i < NB_PLANETES; i++) {
        libererTrajectoire(&listePlanetes[i].trajectoire);
        free(listePlanetes[i].nom);
    }
    return EXIT_SUCCESS;
}
