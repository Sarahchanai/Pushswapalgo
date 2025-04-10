#include "push_swap.h"

// Fonction qui créer un new élément
t_noeud *nouveau_element(int valeur)
{
    t_noeud *element = malloc(sizeof(t_noeud));
    if (!element)
        return (NULL);
    element->valeur = valeur;
    element->suivant = NULL;
    return (element);
}

void ajouter_sommet(t_pile *pile, int valeur)
{
    t_noeud *tmp; 
    t_noeud *nouveau = malloc(sizeof(t_noeud));
    if (!nouveau)
        return;

    nouveau->valeur = valeur;
    nouveau->suivant = NULL; //dernier 
    tmp = pile->sommet; // on commence au debut
    if (pile->sommet)
    {
        while (tmp->suivant != NULL) // on cherche dernier element
        {
            tmp = tmp->suivant;
        }
        tmp->suivant = nouveau; // on ajoute le new noeud a la fin donc
    }
    else
        pile->sommet = nouveau;
    pile->taille++;
}

// Fonction qui affiche la pile
void afficher_pile(t_pile *pile)
{
    printf("Pile (taille : %d) : ", pile->taille);
    t_noeud *actuel = pile->sommet;
    while (actuel)
    {
        printf("%d ", actuel->valeur); 
        actuel = actuel->suivant;
    }
    printf("\n");
}
