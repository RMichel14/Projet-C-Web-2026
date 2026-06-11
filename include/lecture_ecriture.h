#ifndef LECTURE_ECRITURE_H
#define LECTURE_ECRITURE_H

#include "calculs_trajectoire.h"

/**
 * Fonction pour exporter les données calculées au format JSON.
 * @param nomFichier chaine de caractères contenant le nom du fichier à enregistrer | type : char *
 * @param listePlanetes pointeur vers la liste des planètes | type : planete *
 */
void exporterJSON(const char *nomFichier, planete *listePlanetes);

/**
 * Fonction qui permet de lire ligne par ligne
 * @param nomDuFichier chemin vers le fichier cible
 * @param listePlanetes pointeur vers le tableau de la liste des planètes
 */
void lectureDonneesInitialesPlanetes(char *nomDuFichier, planete *listePlanetes);

#endif