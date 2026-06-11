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

/**
 * Fonction récursive qui appelle calculerPointSuivantEuler() autant de fois que le nombre de points
 * @param trajDepart pointeur vers la trajectoire depuis laquelle on fait les calculs | type : trajectoire *
 * @param stop compteur pour s'arrêter au nombre de point voulu | type : double
 */
void calculerTousLesPointsEulerPlanete(trajectoire *trajDepart, int stop) {
    // cas de base
    if (stop >= NB_POINTS) {
        trajDepart->nextpoint = NULL;
        return;
    }

    // allocation d'une zone mémoire pour la prochaine trajectoire
    trajDepart->nextpoint = malloc(sizeof(trajectoire));

    // en cas d'erreur d'allocation mémoire
    if (trajDepart->nextpoint == NULL) {
        fprintf(stderr, "Erreur allocation mémoire\n");
        exit(EXIT_FAILURE);
    }

    // définition du prochain point au sein de la structure trajectoire suivante
    trajDepart->nextpoint->point = calculerPointSuivantEuler(trajDepart->point, DELTA_T);

    calculerTousLesPointsEulerPlanete(trajDepart->nextpoint, stop + 1);
}

void calculerTousLesPointsEuler(planete *listePlanetes) {
    for (int i = 0; i < NB_PLANETES; i++)
        calculerTousLesPointsEulerPlanete(&listePlanetes[i].trajectoire, 1);
}

void affichageDesPointsEulerCode(trajectoire *trajDepart, int stop) {
    // cas de base
    if (trajDepart == NULL || stop >= NB_POINTS)
        return;

    printf("[%d]:\nPosition: [%e, %e, %e]\nVitesse:  [%e, %e, %e]\nTemps:    %d\n\n",
        stop,
        trajDepart->point.r.x, trajDepart->point.r.y, trajDepart->point.r.z,
        trajDepart->point.v.x, trajDepart->point.v.y, trajDepart->point.v.z,
        trajDepart->point.temps
    );
    affichageDesPointsEulerCode(trajDepart->nextpoint, stop + 1);
}

void affichageDesPointsEuler(planete *pl) {
    affichageDesPointsEulerCode(&pl->trajectoire, 0);
}


/**********************************************
 ******************* Tests ********************
 **********************************************/

void planeteTest(planete *listePlanetes) {
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

    // Test calcul des points selon la méthode d'Euler
    calculerTousLesPointsEuler(listePlanetes);


    // affichage de tous les points
    affichageDesPointsEuler(&(listePlanetes[0])); // Affichage pour la planète Terre
}