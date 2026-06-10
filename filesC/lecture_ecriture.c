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

    while (getline(&line, &len, monFichier) != -1) {
        if (count >= NB_PLANETES) break;            // si le compteur de planètes dépasse le nombre de planète accepté dans le tableau -> stop

        // Stockage temporaire des informations d'une planète
        char name[100];
        double masse;
        double perihelie;

        if (sscanf(line, "%99s %lf %lf", name, &masse, &perihelie) == 3) {  // l'utilisation de %99s est pour éviter un dépassement dans le tableau 'name' de 100 caractères
            listePlanetes[count].nom = malloc(strlen(name) + 1);

            if (listePlanetes[count].nom != NULL) {
                strcpy(listePlanetes[count].nom, name);

                listePlanetes[count].masse = masse;
                listePlanetes[count].perihelie = perihelie;

                count++;
            }
        }
    }

    free(line);
    fclose(monFichier);                             // le fichier doit être fermé
}