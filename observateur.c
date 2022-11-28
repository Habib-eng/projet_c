
#include <stdio.h>
#include <stdlib.h>
#include "./observateur.h"

int ajoute(observateur entity)
{
    FILE *db = fopen("./observateurs.txt", "a+");
    if (db != NULL)
    {
        fprintf(db, "%d %s %s %s %s %s \n", entity.cin, entity.nom, entity.prenom, entity.nationalite, entity.appartenance, entity.sexe);
        fclose(db);
        return 0;
    }
    return 1;
}

int modifier(observateur entity)
{
    FILE *db = fopen("./observateurs.txt", "r");
    FILE *f_tmp;
    f_tmp = fopen("./tmp_observateurs.txt", "a");
    if (rechercher(entity.cin).cin != 0)
    {
        if (f_tmp != NULL)
        {
            observateur obj;
            do
            {
                fscanf(db, "%d %s %s %s %s %s \n", &obj.cin, obj.nom, obj.prenom, obj.appartenance, obj.sexe, obj.nationalite);
                if (obj.cin == entity.cin)
                {
                    fprintf(f_tmp, "%d %s %s %s %s %s \n", entity.cin, entity.nom, entity.prenom, entity.appartenance, entity.sexe, entity.nationalite);
                }
                else
                {
                    fprintf(f_tmp, "%d %s %s %s %s %s \n", obj.cin, obj.nom, obj.prenom, obj.appartenance, obj.sexe, obj.nationalite);
                }
            } while (!feof(db));
        }
        fclose(f_tmp);
        fclose(db);
        remove("observateurs.txt");
        rename("tmp_observateurs.txt", "observateurs.txt");
        return 1;
    }
    else
    {
        return 0;
    }

}

observateur rechercher(int cin)
{
    FILE *db = fopen("./observateurs.txt", "r");
    observateur obj;
    if (db != NULL)
    {
        while (fscanf(db, "%d %s %s %s %s %s \n", &obj.cin, obj.nom, obj.prenom, obj.appartenance, obj.sexe, obj.nationalite) != EOF)
        {
            if (obj.cin == cin)
            {
                fclose(db);
                return obj;
            }
        }
    }
    obj.cin = 0;
    return obj;
}

int supprimer(int cin)
{
    FILE *db = fopen("./observateurs.txt", "r");
    FILE *f_tmp;
    f_tmp = fopen("./tmp_observateurs.txt", "a");
    if (f_tmp != NULL)
    {
        observateur obj;
        do
        {
            fscanf(db, "%d %s %s %s %s %s \n", &obj.cin, obj.nom, obj.prenom, obj.appartenance, obj.sexe, obj.nationalite);
            if (obj.cin != cin)
            {
                fprintf(f_tmp, "%d %s %s %s %s %s \n", obj.cin, obj.nom, obj.prenom, obj.appartenance, obj.sexe, obj.nationalite);
            }
        } while (!feof(db));
    }
    fclose(f_tmp);
    fclose(db);
    remove("observateurs.txt");
    rename("tmp_observateurs.txt", "observateurs.txt");
    return 1;
}

// Fonction statistique
int nbobserver()
{
    FILE *db = fopen("./observateurs.txt", "r");
    observateur obj;
    int i = 0;
    if (db != NULL)
    {
        while (fscanf(db, "%d %s %s %s %s %s \n", &obj.cin, obj.nom, obj.prenom, obj.appartenance, obj.sexe, obj.nationalite) != EOF)
        {
            i++;
        }
    }
    return i;
}