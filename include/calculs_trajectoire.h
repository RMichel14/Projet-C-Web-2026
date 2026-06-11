#ifndef CALCUL_TRAJECTOIRE
#define CALCUL_TRAJECTOIRE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vecteurs.h"

/**********************************************
 ***************** Constantes *****************
 **********************************************/

#define NB_PLANETES 8 // Nombre de planètes
#define G 6.67408e-11 // Constante gravitationnelle
#define MASSE_SOLEIL 1.9885e30

#define DELTA_T 3600.0 // temps en secondes / 1 heure = 3600 secondes
#define NB_POINTS 8760 // 365 jours x 24 heures = 8760 points


/**********************************************
 ***************** Structures *****************
 **********************************************/

typedef struct _point {
    vector r;  // position
    vector v;  // vitesse
    int temps;
} point;

typedef struct _trajectoire {
    point point;
    struct _trajectoire *nextpoint;
} trajectoire;

typedef struct _planete {
    char *nom;
    double masse;
    trajectoire trajectoire;
    double perihelie;   // distance minimale planète/soleil
    double vitesseInitiale;
} planete;


/**********************************************
 ********* Fonctions sur les planètes *********
 **********************************************/

/**
 * Fonctions de tests unitaires sur les planètes
 * @param listePlanetes pointeur vers le tableau de la liste des planètes
 */
void planeteTest(planete *listePlanetes);

/**
 * Initialisation trajectoire des planètes.
 * @param listePlanetes pointeur vers la liste des planètes.
 */
void initialiserTrajectoirePlanetes(planete *listePlanetes);

/**
 * Initialisation trajectoire d'UNE planète.
 * @param pl pointeur vers une planète.
 */
void initialiserTrajectoirePlanete(planete *pl);

/**
 * Calcul l'accélération d'une planète.
 * @param position vecteur position de la planète | type : vector
 * @return vector
 */
vector calculerAcceleration(vector position);

/**
 * Calcul du point suivant selon la méthode d'Euler
 * @param courant point actuel | type : point
 * @param deltaT équart en temps entre le point actuel (courant) et le point à calculer | type : double
 * @return structure de type point
 */
point calculerPointSuivantEuler(point courant, double deltaT);

/**
 * Permet de calculer tous les points de trajectoire des planètes selon la méthode d'Euler
 * @param listePlanetes pointeur vers la liste des planètes
 */
void calculerTousLesPointsEuler(planete *listePlanetes);

/**
 * Affichage de tous les points d'une planète selon la méthode d'Euler
 * @param listePlanete pointeur vers la liste des planètes | type : planete
 */
void affichageDesPointsEuler(planete *pl);

#endif