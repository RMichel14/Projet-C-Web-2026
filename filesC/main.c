#include "calculs_trajectoire.h"


// Corps du programme
int main() {
    planete listePlanetes[NB_PLANETES] = {0};
    
    // Tests unitaires
    printf("Hello world!\n");
    planeteTest(listePlanetes);
    vectorTest();
    
    return EXIT_SUCCESS;
}
