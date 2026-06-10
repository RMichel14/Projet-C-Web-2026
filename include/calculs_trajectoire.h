#ifndef CALCUL_TRAJECTOIRE
#define CALCUL_TRAJECTOIRE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vecteurs.h"

#define NB_PLANETES 8


/**********************************************
 ***************** Structures *****************
 **********************************************/

// Structure point
typedef struct _point {
    vector r;  // position
    vector v;  // vitesse
    int temps;
} point;

// Structure trajectoire
typedef struct _trajectoire {
    point point;
    struct _trajectoire *nextpoint;
} trajectoire;

// Structure planète
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
 * Initialisation trajectoire d'une planète.
 * @param pl pointeur vers une planète.
 */
void initialiserTrajectoirePlanete(planete *pl);


#endif