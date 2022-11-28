#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "observateur.h"

enum
{
    NOM,
    PRENOM,
    NATIONALITE,
    APPARTENANCE,
    SEXE,
    CIN,
    COLUMNS
};

enum
{
    COL_NAME = 0,
    COL_AGE,
    NUM_COLS
};

GtkBuilder *builder;

int init(int argc, char *argv[])
{
    GError *error = NULL;
    GtkWidget *window;
    gtk_init(&argc, &argv);
    builder = gtk_builder_new();
    if (gtk_builder_add_from_file(builder, "./template.glade", &error) == 0)
    {
        g_printerr("Error Loading file");
        g_clear_error(&error);
        return EXIT_FAILURE;
    }
    window = GTK_WIDGET(gtk_builder_get_object(builder, "janela"));
    GtkTreeView *tree = gtk_builder_get_object(builder,"list_view");
    GtkCellRenderer *renderer;

    renderer = gtk_cell_renderer_text_new();
    gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(tree),
                                                -1,
                                                "Name",
                                                renderer,
                                                "text", COL_NAME,
                                                NULL);

    /* --- Column #2 --- */
    renderer = gtk_cell_renderer_text_new();
    gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(tree),
                                                -1,
                                                "Age",
                                                renderer,
                                                "text", COL_AGE,
                                                NULL);

    GtkTreeModel *model = create_and_fill_model ();

    gtk_tree_view_set_model(GTK_TREE_VIEW(tree), model);

    /* The tree view has acquired its own reference to the
     *  model, so we can drop ours. That way the model will
     *  be freed automatically when the tree view is destroyed
     */
    g_object_unref(model);
    gtk_builder_connect_signals(builder, NULL);
    gtk_widget_show_all(window);
    gtk_main();
    
    return EXIT_SUCCESS;
}

void on_reset_clicked(GtkWidget *widget, gpointer data)
{
    GtkWidget *input1, *input2, *input3, *input4, *input5, *input6;
    input1 = gtk_builder_get_object(builder, "cin_input");
    input2 = gtk_builder_get_object(builder, "name_input");
    input3 = gtk_builder_get_object(builder, "last_name_input");
    input4 = gtk_builder_get_object(builder, "appartenance_input");
    input5 = gtk_builder_get_object(builder, "nation_input");
    input6 = gtk_builder_get_object(builder, "sexe_input");
    gtk_entry_set_text(GTK_ENTRY(input1), "");
    gtk_entry_set_text(GTK_ENTRY(input2), "");
    gtk_entry_set_text(GTK_ENTRY(input3), "");
    gtk_entry_set_text(GTK_ENTRY(input4), "");
    gtk_entry_set_text(GTK_ENTRY(input5), "");
    gtk_entry_set_text(GTK_ENTRY(input6), "");
}

void on_ajoute_clicked(GtkWidget *object, gpointer data)
{
    observateur observer;
    GtkWidget *input1, *input2, *input3, *input4, *input5, *input6;
    input1 = gtk_builder_get_object(builder, "cin_input");
    input2 = gtk_builder_get_object(builder, "name_input");
    input3 = gtk_builder_get_object(builder, "last_name_input");
    input4 = gtk_builder_get_object(builder, "appartenance_input");
    input5 = gtk_builder_get_object(builder, "nation_input");
    input6 = gtk_builder_get_object(builder, "sexe_input");

    const gchar *cin = gtk_entry_get_text(GTK_ENTRY(input1));
    observer.cin = atoi(cin);
    strcpy(observer.nom, gtk_entry_get_text(GTK_ENTRY(input2)));
    strcpy(observer.prenom, gtk_entry_get_text(GTK_ENTRY(input3)));
    strcpy(observer.appartenance, gtk_entry_get_text(GTK_ENTRY(input4)));
    strcpy(observer.nationalite, gtk_entry_get_text(GTK_ENTRY(input5)));
    strcpy(observer.sexe, gtk_entry_get_text(GTK_ENTRY(input6)));
    int code = ajoute(observer);
};

static GtkTreeModel *create_and_fill_model()
{
    GtkListStore *store = gtk_list_store_new(NUM_COLS, G_TYPE_STRING, G_TYPE_UINT);
    GtkTreeIter iter;
    gtk_list_store_append(store, &iter);
    gtk_list_store_set(store, &iter, COL_NAME, "Habib", COL_AGE, 15, -1);
    return GTK_TREE_MODEL(store);
}

// int affiche()
// {
//     GtkCellRenderer *renderer;
//     GtkTreeViewColumn *column;
//     GtkTreeIter iter;
//     GtkTreeView *liste;
//     GtkListStore *store;
//     liste = GTK_TREE_VIEW (gtk_builder_get_object(builder,"list_view"));
//     g_print("a");
//     int *cin;
//     char nom[20];
//     char prenom[20];
//     char nationalite[20];
//     char appartenance[20];
//     char sexe[20];

//     store = NULL;
//     FILE *f;
//     store = GTK_LIST_STORE (gtk_tree_view_get_model(liste));
//     if (store == NULL)
//     {
//         renderer = gtk_cell_renderer_text_new();
//         column = gtk_tree_view_column_new_with_attributes("nom", renderer, "text", NOM, NULL);
//         gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

//         renderer = gtk_cell_renderer_text_new();
//         column = gtk_tree_view_column_new_with_attributes("prenom", renderer, "text", PRENOM, NULL);
//         gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

//         renderer = gtk_cell_renderer_text_new();
//         column = gtk_tree_view_column_new_with_attributes("nationalte", renderer, "text", NATIONALITE, NULL);
//         gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

//         renderer = gtk_cell_renderer_text_new();
//         column = gtk_tree_view_column_new_with_attributes("appartenance", renderer, "text", APPARTENANCE, NULL);
//         gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

//         renderer = gtk_cell_renderer_text_new();
//         column = gtk_tree_view_column_new_with_attributes("sexe", renderer, "text", SEXE, NULL);
//         gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

//         store = gtk_list_store_new(COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
//         g_print("Hello");
//     }

//     FILE *db = fopen("./observateurs.txt", "a+");
//     if (db != NULL)
//     {
//         while (fscanf(db, "%d %s %s %s %s %s \n", cin, nom, prenom, appartenance, sexe, nationalite) != EOF)
//         {
//             gtk_list_store_append(GTK_LIST_STORE(store),&iter);
//           gtk_list_store_set(store, &iter, CIN, *cin, NOM, nom, PRENOM, prenom, APPARTENANCE, appartenance, NATIONALITE, nationalite, SEXE, sexe, -1);
//         }
//         fclose(db);
//         gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
//         g_object_unref(store);
//     }
//     return 0;
// }

int main(int argc, char *argv[])
{
    int a = init(argc, argv);
    // observateur obj;
    // printf("saisir le CIN :");
    // scanf("%d",&obj.cin);
    // printf("Saisir le nom :");
    // scanf("%s", obj.nom);
    // printf("Saisir le prenom :");
    // scanf("%s", obj.prenom);
    // printf("Saisir l'appartenance :");
    // scanf("%s",obj.appartenance);
    // printf("Saisir la nationalité :");
    // scanf("%s",obj.nationalite);
    // printf("Saisir le sexe :");
    // scanf("%s",obj.sexe);
    // //Tester l'ajout
    // int code = ajoute(obj);
    // if (code == 0) {
    //     printf("Ajouté avec succès \n");
    // } else {
    //     printf("Il y a un problème avec l'ajout \n");
    // }
    // // Tester la recherche avec cin
    // printf("Saisir CIN pour chercher un observateur \n");
    // int cin;
    // scanf("%d",&cin);
    // obj = rechercher(cin);
    // if (obj.cin = 0){
    //     printf("L'observateur cherché ne se trouve pas !");
    // } else {
    //     printf("Vous chercheez %s %s \n",obj.nom,obj.prenom);
    // }

    // //Tester la suppression
    // printf("Saisir la CIN de l'observateur a supprimer \n");
    // scanf("%d",&cin);
    // if (supprimer(cin)){
    //     printf("Suppresion avec succès  \n");
    // } else {
    //     printf("Problème lors de suppression \n");
    // }
    // //Tester la fonction statistique
    // printf("Le nombre totale des observateurs est : \n %d observateurs ",nbobserver());
}