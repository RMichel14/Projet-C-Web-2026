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
}

void initialiserTrajectoirePlanetes(planete *listePlanetes) {
    for (int i = 0; i < NB_PLANETES; i++)
        initialiserTrajectoirePlanete(&listePlanetes[i]);
}

vector calculerAcceleration(vector position) {
    vector acceleration;

    double distance = norme(&position);

    // Sécurité : éviter une division par zéro
    if (distance == 0.0) {
        acceleration.x = 0.0;
        acceleration.y = 0.0;
        acceleration.z = 0.0;

        return acceleration;
    }

    /**
     * Formule mathématiques : (-G x MASSE_SOLEIL) /
     *                  (distance * distance * distance)
     */
    double coefficient =
                (-G * MASSE_SOLEIL) /
        (distance * distance * distance);

    acceleration.x = coefficient * position.x;
    acceleration.y = coefficient * position.y;
    acceleration.z = coefficient * position.z;

    return acceleration;
}

point calculerPointSuivantEuler(point courant, double deltaT) {
    point suivant;

    // accélération au temps n
    vector acceleration = calculerAcceleration(courant.r);

    // position au temps n+1
    suivant.r.x = courant.r.x + courant.v.x * deltaT;
    suivant.r.y = courant.r.y + courant.v.y * deltaT;
    suivant.r.z = courant.r.z + courant.v.z * deltaT;

    // vitesse au temps n+1
    suivant.v.x = courant.v.x + acceleration.x * deltaT;
    suivant.v.y = courant.v.y + acceleration.y * deltaT;
    suivant.v.z = courant.v.z + acceleration.z * deltaT;

    // temps
    suivant.temps = courant.temps + 1;

    return suivant;
}
/**********************************************
 ******************* Tests ********************
 **********************************************/

void planeteTest(planete *listePlanetes) {
    // lectureDonneesInitialesPlanetes("data/donnees_initiales_planetes.txt", listePlanetes);

    // Test affichage
    for (int i = 0; i < NB_PLANETES; i++)
        if (listePlanetes[i].nom != NULL)
            printf("%s :\nMasse : %le\nPérihélie : %le\nVitesse initiale : %le\n\n", listePlanetes[i].nom, listePlanetes[i].masse, listePlanetes[i].perihelie, listePlanetes[i].vitesseInitiale);

    // Test acceleration de la Terre
    planete terre = listePlanetes[0];
    vector *vect = nouveauVecteur(terre.perihelie, 0, 0);
    vector acceleration = calculerAcceleration(*vect);

    printf("Accélération :\n");
    printf("%e\n", acceleration.x);
    printf("%e\n", acceleration.y);
    printf("%e\n", acceleration.z);
    free(vect);

    // Test calcul du prochain point selon la méthode d'Euler
    // planete terre = listePlanetes[0]; // déjà fait dans l'accélération

    terre.trajectoire.tabPoint[0] = terre.trajectoire.point;
    // printf("test: %e", terre.trajectoire.point.v.z);

    /**
     * on démarre i = 1 car on calcul le point suivant en se servant du point i-1 (et donc égal à 0) pour le calcul
     */
    for(int i = 1; i < NB_POINTS; i++)
        terre.trajectoire.tabPoint[i] = calculerPointSuivantEuler(terre.trajectoire.tabPoint[i - 1], DELTA_T);
    
    // affichage de tous les points
    for (int i = 0; i < 20; i++)
        printf("[%d]:\nPosition: [%e, %e, %e]\nVitesse:  [%e, %e, %e]\nTemps:    %d\n\n", i, terre.trajectoire.tabPoint[i].r.x, terre.trajectoire.tabPoint[i].r.y, terre.trajectoire.tabPoint[i].r.z, terre.trajectoire.tabPoint[i].v.x, terre.trajectoire.tabPoint[i].v.y, terre.trajectoire.tabPoint[i].v.z, terre.trajectoire.tabPoint[i].temps);
    
    // libération de la mémoire
    // for (int i = 0; i < NB_PLANETES; i++)
    //     free(listePlanetes[i].nom);
}