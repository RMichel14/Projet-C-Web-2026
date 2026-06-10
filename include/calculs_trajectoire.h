#ifndef CALCUL_TRAJECTOIRE
#define CALCUL_TRAJECTOIRE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NB_PLANETES 8


/**********************************************
 ***************** Structures *****************
 **********************************************/

// Structure vecteur
typedef struct _vector {
    double x;
    double y;
    double z;
} vector;

// Structure point
typedef struct _point {
    vector r; // position
    vector v; // vitesse
    int p;    // point (temps)
} point;

// Structure planète
typedef struct _planete {
    char *nom;
    double masse;
    double trajectoire;
    double perihelie;   // distance minimale planète/soleil
} planete;



/**********************************************
 ** Fonctions mathématiques sur les vecteurs **
 **********************************************/

// addition de deux vecteurs
// soustraction de deux vecteurs
// multiplication d'un vecteur par un scalaire
// calcul de la norme d'un vecteur

/**
 * Fonction de test sur les vecteurs
 * Objectifs : Créez des vecteurs, les additionnez, les multipliez par un scalaire. Cette fonction doit afficher les résultats en console.
 *             Ces fonctions seront appelées dans la fonction main puis commentées une fois les tests validés.
 */
void vectorTest();


/**********************************************
 ********* Fonctions sur les planètes *********
 **********************************************/

/**
 * Fonctions de tests unitaires sur les planètes
 * @param listePlanetes pointeur vers le tableau de la liste des planètes
 */
void planeteTest(planete *listePlanetes);

#endif