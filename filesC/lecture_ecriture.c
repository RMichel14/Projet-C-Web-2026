#include "lecture_ecriture.h"

void lectureDonneesInitialesPlanetes(char *nomDuFichier, planete *listePlanetes) {
    FILE * monFichier = fopen(nomDuFichier, "r");   // creation d'un pointeur FILE pour le fichier & ouverture

    if (monFichier == NULL) {                       // si l'ouverture du fichier ne se passe pas bien
        fprintf(stderr, "Cannot open file\n");      // stderr est la sortie d'erreur standard
        return;                                     // arrêt de la fonction
    }

    char * line = NULL;                             // buffer de lecture
    size_t len = 0;                                 // taille du buffer
    int count = 0;                                  // compteur du nombre de planètes pour parcourir et ne pas dépasser la taille du tableau

    // si le compteur de planètes dépasse le nombre de planète accepté dans le tableau ou si la ligne est vide (résultat de getline(...) => -1) -> la boucle s'arrête
    while (count < NB_PLANETES && getline(&line, &len, monFichier) != -1) {

        // Stockage temporaire des informations d'une planète
        char name[100]         = {0};
        double masse           = 0;
        double perihelie       = 0;
        double vitesseInitiale = 0;

        if (sscanf(line, "%99s %le %le %le", name, &masse, &perihelie, &vitesseInitiale) == 4) {  // l'utilisation de %99s est pour éviter un dépassement dans le tableau 'name' de 100 caractères
            listePlanetes[count].nom = malloc(strlen(name) + 1);

            if (listePlanetes[count].nom != NULL) {
                strcpy(listePlanetes[count].nom, name); // copie du tableau du nom de la planète dans la structure planete

                listePlanetes[count].masse           = masse;
                listePlanetes[count].perihelie       = perihelie;
                listePlanetes[count].vitesseInitiale = vitesseInitiale;

                count++;
            }
        }
    }

    free(line);
    fclose(monFichier);                             // le fichier doit être fermé
}