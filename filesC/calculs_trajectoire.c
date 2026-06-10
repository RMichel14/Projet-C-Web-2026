#include "calculs_trajectoire.h"
#include "lecture_ecriture.h"

void planeteTest(planete *listePlanetes) {
    lectureDonneesInitialesPlanetes("data/donnees_initiales_planetes.txt", listePlanetes);

    for (int i = 0; i < NB_PLANETES; i++)
        if (listePlanetes[i].nom != NULL)
            printf("%s :\nMasse : %le\nPérihélie : %le\nVitesse initiale : %le\n\n", listePlanetes[i].nom, listePlanetes[i].masse, listePlanetes[i].perihelie, listePlanetes[i].vitesseInitiale);
}