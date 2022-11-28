#ifndef OBSERVATEUR_H_INCLUDED
#define OBSERVATEUR_H_INCLUDED
#include <stdlib.h>
    
typedef struct {
    int  cin;
    char nom[20];
    char prenom[20];
    char nationalite[20];
    char appartenance[20];
    char sexe[20];
} observateur;


extern int ajoute(observateur entity);
extern int supprimer(int cin);
extern int modifier(observateur object);
extern observateur rechercher(int cin);
extern int nbobserver();
#endif