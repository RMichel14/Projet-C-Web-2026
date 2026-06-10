#ifndef LECTURE_ECRITURE_H
#define LECTURE_ECRITURE_H

#include "calculs_trajectoire.h"

/**
 * Fonction qui permet de lire ligne par ligne
 * @param nomDuFichier chemin vers le fichier cible
 * @param listePlanetes pointeur vers le tableau de la liste des planètes
 */
void lectureDonneesInitialesPlanetes(char *nomDuFichier, planete *listePlanetes);

#endif