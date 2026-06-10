#include "vecteurs.h"

/**********************************************
 ****************** Vecteurs ******************
 **********************************************/

vector *nouveauVecteur(double x, double y, double z) {
    vector *vecteur = malloc(sizeof(vector));

    vecteur->x = x;
    vecteur->y = y;
    vecteur->z = z;

    return vecteur;
}

void afficherVecteur(vector *vect) {
    printf("x: %lf\ny: %lf\n z: %lf\n", vect->x, vect->y, vect->z);
}


/**********************************************
 ** Fonctions mathématiques sur les vecteurs **
 **********************************************/

vector *addition(vector *vect1, vector *vect2) {
    return nouveauVecteur((vect1->x + vect2->x), (vect1->y + vect2->y), (vect1->z + vect2->z));
}

vector *soustraction(vector *vect1, vector *vect2) {
    return nouveauVecteur((vect1->x - vect2->x), (vect1->y - vect2->y), (vect1->z - vect2->z));
}

vector *multiplication(vector *vect, int number) {
    return nouveauVecteur((vect->x * number), (vect->y * number), (vect->z * number));
}

double norme(vector *vect) {
    return sqrt((CARRE(vect->x)) + (CARRE(vect->y)) + (CARRE(vect->z)));
}


/**********************************************
 ******************* Tests ********************
 **********************************************/

void vectorTest() {
    /*********************************************
     ** Séquence de tests sur les mathématiques **
     *********************************************/

    vector *vecteur1 = nouveauVecteur(2, 2, 0);
    vector *vecteur2 = nouveauVecteur(4, 4, 0);

    // Test addition
    vector *add = addition(vecteur1, vecteur2);
    printf("Vecteur addition\n");
    afficherVecteur(add);

    // Test soustraction
    vector *sous = soustraction(vecteur1, vecteur2);
    printf("Vecteur soustraction\n");
    afficherVecteur(sous);

    // Test multiplication
    vector *multipli = multiplication(vecteur1, 3);
    printf("Multiplication par un scalaire\n");
    afficherVecteur(multipli);

    // Test norme
    double normeVect = norme(vecteur1);
    printf("Norme d'un vecteur : %lf\n", normeVect);

    // libération de la mémoire
    free(vecteur1);
    free(vecteur2);
    free(add);
    free(sous);
    free(multipli);
}