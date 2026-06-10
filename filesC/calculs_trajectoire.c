#include "calculs_trajectoire.h"
#include "lecture_ecriture.h"

void initialiserTrajectoirePlanete(planete *pl) {

    // Premier point de la trajectoire
    pl->trajectoire.point.r.x = pl->perihelie;
    pl->trajectoire.point.r.y = 0.0;
    pl->trajectoire.point.r.z = 0.0;

    // Vitesse perpendiculaire au rayon
    pl->trajectoire.point.v.x = 0.0;
    pl->trajectoire.point.v.y = pl->vitesseInitiale;
    pl->trajectoire.point.v.z = 0.0;

    // Temps initial
    pl->trajectoire.point.temps = 0;

    // Pas encore de point suivant
    pl->trajectoire.nextpoint = NULL;
};


/**********************************************
 ******************* Tests ********************
 **********************************************/

void planeteTest(planete *listePlanetes) {
    lectureDonneesInitialesPlanetes("data/donnees_initiales_planetes.txt", listePlanetes);

    for (int i = 0; i < NB_PLANETES; i++)
        if (listePlanetes[i].nom != NULL)
            printf("%s :\nMasse : %le\nPérihélie : %le\nVitesse initiale : %le\n\n", listePlanetes[i].nom, listePlanetes[i].masse, listePlanetes[i].perihelie, listePlanetes[i].vitesseInitiale);

    // libération de la mémoire
    for (int i = 0; i < NB_PLANETES; i++)
        free(listePlanetes[i].nom);
}