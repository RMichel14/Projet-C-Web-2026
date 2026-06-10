#ifndef CALCUL_TRAJECTOIRE
#define CALCUL_TRAJECTOIRE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define NB_PLANETES 8
#define CARRE(x) ((x)*(x))


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
    double vitesseInitiale;
} planete;



/**********************************************
 ****************** Vecteurs ******************
 **********************************************/

/**
 * Permet de créer un nouveau vecteur
 * @param x type : double
 * @param y type : double
 * @param z type : double
 * @return pointeur vers un nouveau vecteur
 */
vector *nouveauVecteur(double x, double y, double z);

/**
 * Afficher vecteur
 * @param vect vecteur | type : pointeur struct vector
 */
void afficherVecteur(vector *vect);

/**
 * Fonction de test sur les vecteurs
 * Objectifs : Créez des vecteurs, les additionnez, les multipliez par un scalaire. Cette fonction doit afficher les résultats en console.
 *             Ces fonctions seront appelées dans la fonction main puis commentées une fois les tests validés.
 */
void vectorTest();


/**********************************************
 ** Fonctions mathématiques sur les vecteurs **
 **********************************************/

/**
 * Addition de deux vecteurs
 * @param vect1 premier vecteur | type : pointeur struct vector
 * @param vect2 second vecteur | type : pointeur struct vector
 * @return vector
 */
vector *addition(vector *vect1, vector *vect2);

/**
 * Soustraction de deux vecteurs
 * @param vect1 premier vecteur | type : pointeur struct vector
 * @param vect2 second vecteur | type : pointeur struct vector
 * @return vector
 */
vector *soustraction(vector *vect1, vector *vect2);

/**
 * Multiplication d'un vecteur par un scalaire
 * @param vect vecteur | type : pointeur struct vector
 * @param number scalaire | type : int
 * @return vector
 */
vector *multiplication(vector *vect, int number);

/**
 * Calcul de la norme d'un vecteur
 * @param vect vecteur | type : pointeur struct vector
 * @return double
 */
double norme(vector *vect);


/**********************************************
 ********* Fonctions sur les planètes *********
 **********************************************/

/**
 * Fonctions de tests unitaires sur les planètes
 * @param listePlanetes pointeur vers le tableau de la liste des planètes
 */
void planeteTest(planete *listePlanetes);

#endif