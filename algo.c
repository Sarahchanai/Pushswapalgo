#include "push_swap.h"


                        // Fonctions utiles 

void    ft_swap(int *a, int *b)
{
    int temp;
    
    temp = *a;
    *a = *b;
    *b = temp;
}

int     *remplir_tableau(t_pile *pile)
{
    int     *tab;
    int     i;
    t_noeud *actuel;

    tab = malloc(sizeof(int) * pile->taille);
    if (!tab)
        return (NULL);
    actuel = pile->sommet;
    i = 0;
    while (actuel)
    {
        tab[i] = actuel->valeur;
        actuel = actuel->suivant;
        i++;
    }
    return (tab);
}
// peut etre a optimiser ? 
void    sort_int_tab(int *tab, unsigned int size)
{
    unsigned int    i;
    int             check;

    check = 1;
    while (check == 1)
    {
        i = 0;
        check = 0;
        while (i < size - 1)
        {
            if (tab[i] > tab[i + 1])
            {
                ft_swap(&tab[i], &tab[i + 1]);
                check = 1;
            }
            i++;
        }
    }
}


        // la pile est peut être deja triée ? (son but)
int     est_triee(t_pile *pile)
{
    t_noeud *actuel;

    if (!pile || pile->taille <= 1)
        return (1);

    actuel = pile->sommet;
    while (actuel && actuel->suivant)
    {
        if (actuel->valeur > actuel->suivant->valeur)
            return (0);
        actuel = actuel->suivant;
    }
    return (1);
}


int     trouve_min(t_pile *pile)
{
    t_noeud *actuel;
    int     min_val;

    if (!pile || !pile->sommet)
        return (0);
    
    actuel = pile->sommet;
    min_val = actuel->valeur;
    
    while (actuel)
    {
        if (actuel->valeur < min_val)
            min_val = actuel->valeur;
        actuel = actuel->suivant;
    }
    return (min_val);
}

int     trouve_max(t_pile *pile)
{
    t_noeud *actuel;
    int     max_val;

    if (!pile || !pile->sommet)
        return (0);
    
    actuel = pile->sommet;
    max_val = actuel->valeur;
    
    while (actuel)
    {
        if (actuel->valeur > max_val)
            max_val = actuel->valeur;
        actuel = actuel->suivant;
    }
    return (max_val);
}

int     trouve_position(t_pile *pile, int valeur)
{
    t_noeud *actuel;
    int     pos;

    if (!pile || !pile->sommet)
        return (-1);
    
    actuel = pile->sommet;
    pos = 0;
    
    while (actuel)
    {
        if (actuel->valeur == valeur)
            return (pos);
        actuel = actuel->suivant;
        pos++;
    }
    return (-1);
}

int     trouver_position_min(t_pile *pile)
{
    int min_val;
    
    min_val = trouve_min(pile);
    return (trouve_position(pile, min_val));
}
int     determiner_nombre_chunks(int taille)
{
    if (taille <= 20)
        return (2);
    else if (taille <= 100)
        return (5);
    else
        return (11);
}
int     get_pivot(int *tab, int taille, int chunk_idx, int total_chunks)
{
    int pivot_idx = ((chunk_idx + 1) * taille) / total_chunks;
    if (pivot_idx >= taille)
        pivot_idx = taille - 1;
    return tab[pivot_idx];
}

void    transferer_elements(t_pile *pile_a, t_pile *pile_b, int pivot, int *count)
{
    while (*count > 0)
    {
        if (pile_a->sommet->valeur <= pivot)
        {
            pb(pile_a, pile_b);
            // Pré-tri dans B
            if (pile_b->taille > 1 && pile_b->sommet->valeur < pile_b->sommet->suivant->valeur)
                rb(pile_b);
            (*count)--;
        }
        else
            ra(pile_a);  // Si l'élément est > pivot, il tourne dans A
    }
}
void    phase_1_chunks(t_pile *pile_a, t_pile *pile_b)
{
    int *tab;
    int taille;
    int total_chunks;
    int chunk_idx = 0;
    int pivot;
    int count;
    t_noeud *curr;

    taille = pile_a->taille;
    tab = remplir_tableau(pile_a);
    if (!tab)
        return;
    sort_int_tab(tab, taille);
    total_chunks = determiner_nombre_chunks(taille);
    while (chunk_idx < total_chunks)
    {
        pivot = get_pivot(tab, taille, chunk_idx, total_chunks);
        count = 0;
        curr = pile_a->sommet;
        while (curr)
        {
            if (curr->valeur <= pivot)
                count++;
            curr = curr->suivant;
        }
        transferer_elements(pile_a, pile_b, pivot, &count);
        chunk_idx++;
    }
    free(tab);
}

void    deplacer_au_sommet(t_pile *pile, int pos)
{
    if (pos <= pile->taille / 2)
    {
        while (pos-- > 0)
            ra(pile);
    }
    else
    {
        while (pos++ < pile->taille)
            rra(pile);
    }
}
// Mtn que B est trié je repasse ses elements ds A
void    phase_2_optimisee(t_pile *pile_a, t_pile *pile_b)
{
    int max_val;
    int pos_b; // Posi° de la valeur max ds B
    
    while (pile_b->taille > 0)
    {
        max_val = trouve_max(pile_b);
        pos_b = trouve_position(pile_b, max_val);

        // Déplacer la valeur max au sommet de B
        deplacer_au_sommet(pile_b, pos_b);
        
        // Transfert de l'élément de B vers A
        pa(pile_a, pile_b);
    }
}


// mettre + petit element de A en haut
void    ajuster_final(t_pile *pile_a)
{
    int min_pos;
    
    min_pos = trouver_position_min(pile_a);

    if (min_pos == 0)
        return;
// Si l'élément min est ds la 1e moitié de la pile
    if (min_pos <= pile_a->taille / 2)
    {
        while (min_pos-- > 0) // on le fait monter
            ra(pile_a);
    }
    else // inverse (2e moitie)
    {
        while (min_pos++ < pile_a->taille) // on le fait descendre
            rra(pile_a);
    }
}
void    trier_2_elements(t_pile *pile_a)
{
    if (pile_a->sommet->valeur > pile_a->sommet->suivant->valeur)
        sa(pile_a);
}
void    trier_3_elements(t_pile *pile_a)
{
    int a = pile_a->sommet->valeur;
    int b = pile_a->sommet->suivant->valeur;
    int c = pile_a->sommet->suivant->suivant->valeur;

    if (a > b && b < c && a < c)
        sa(pile_a);
    else if (a > b && b > c)
    {
        sa(pile_a);
        rra(pile_a);
    }
    else if (a > b && b < c && a > c)
        ra(pile_a);
    else if (a < b && b > c && a < c)
    {
        sa(pile_a);
        ra(pile_a);
    }
    else if (a < b && b > c && a > c)
        rra(pile_a);
}
void    trier_4_elements(t_pile *pile_a)
{
    int min_val = trouve_min(pile_a);
    int pos = trouve_position(pile_a, min_val);
    t_pile *pile_b;

    pile_b = malloc(sizeof(t_pile));

    if (!pile_b)
        return;
    pile_b->sommet = NULL;
    pile_b->taille = 0;

    deplacer_au_sommet(pile_a, pos);
    pb(pile_a, pile_b); 
    trier_3_elements(pile_a);
    pa(pile_a, pile_b);
    free (pile_b);
}
void    trier_5_elements(t_pile *pile_a)
{
    int min_val = trouve_min(pile_a);
    int pos = trouve_position(pile_a, min_val);
    t_pile *pile_b;

    pile_b = malloc(sizeof(t_pile));

    if (!pile_b)
        return;
    pile_b->sommet = NULL;
    pile_b->taille = 0;

    deplacer_au_sommet(pile_a, pos);
    pb(pile_a, pile_b);
    trier_4_elements(pile_a);

    pa(pile_a, pile_b);
    free(pile_b);
}

                        // Fonction principale 
void    trier_piles(t_pile *pile_a, t_pile *pile_b)
{
    if (!pile_a || !pile_b || est_triee(pile_a))
        return;
    
    if (pile_a->taille == 2)
    {
        trier_2_elements(pile_a);
        return;
    }
    else if (pile_a->taille == 3)
    {
        trier_3_elements(pile_a);
        return;
    }
    else if(pile_a->taille == 4)
    {
        trier_4_elements(pile_a);
        return;
    }
    else if (pile_a->taille == 5)
    {
        trier_5_elements(pile_a);
        return;
    }
    
    phase_1_chunks(pile_a, pile_b);
    phase_2_optimisee(pile_a, pile_b);
    ajuster_final(pile_a);
}
