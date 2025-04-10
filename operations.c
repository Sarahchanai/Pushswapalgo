#include "push_swap.h"

// Échange les deux premiers éléments de la pile
void swap(t_pile *pile)
{
    if (!pile || pile->taille < 2)
        return;

    t_noeud *premier = pile->sommet;
    t_noeud *deuxieme = premier->suivant;

    // swap des deux premiers éléments
    premier->suivant = deuxieme->suivant;
    deuxieme->suivant = premier;
    pile->sommet = deuxieme;
}

// Applique swap sur la pile A
void sa(t_pile *a)
{
    swap(a);
    printf("sa\n");
}

// Applique swap sur la pile B
void sb(t_pile *b)
{
    swap(b);
    printf("sb\n");
}

// Applique swap sur les deux piles
void ss(t_pile *a, t_pile *b)
{
    swap(a);
    swap(b);
    printf("ss\n");
}
// Déplace le sommet de la pile B vers A
void pa(t_pile *a, t_pile *b)
{
    if (!b || !b->sommet)
        return;

    t_noeud *temp = b->sommet;  // On récupère le sommet de B
    b->sommet = b->sommet->suivant;  // B perd son sommet
    temp->suivant = a->sommet;  // On met cet élément en haut de A
    a->sommet = temp;  // Le sommet de A devient cet élément (ancien sommet de b donc)
    a->taille++; // A recoit un element
    b->taille--; // B en perd un 


    printf("pa\n"); 
}


// Déplace le sommet de la pile A vers B
void pb(t_pile *a, t_pile *b)
{
    if (!a || !a->sommet)
        return;

    t_noeud *temp = a->sommet;  // On récupère le sommet de A
    a->sommet = a->sommet->suivant;  // A perd son sommet
    temp->suivant = b->sommet;  // On met cet élément en haut de B
    b->sommet = temp;  // Le sommet de B devient cet élément
    a->taille--;
    b->taille++;
    printf("pb\n");
}
// Décale tous les éléments de la pile vers le haut
void rotate(t_pile *pile)
{
    if (!pile || pile->taille < 2)
        return;

    t_noeud *temp = pile->sommet;  // On récupère l'ancien sommet
    pile->sommet = pile->sommet->suivant;  // Le deuxième devient le prems

    t_noeud *dernier = pile->sommet;
    while (dernier->suivant)  // go jusqu'au dernier élément
        dernier = dernier->suivant;
    
    dernier->suivant = temp;  // On met l'ancien sommet à la fin
    temp->suivant = NULL;
}

// Applique rotate sur la pile A
void ra(t_pile *a)
{
    rotate(a);
    printf("ra\n");
}

// Applique rotate sur la pile B
void rb(t_pile *b)
{
    rotate(b);
    printf("rb\n");
}

// Applique rotate sur les deux piles
void rr(t_pile *a, t_pile *b)
{
    rotate(a);
    rotate(b);
    printf("rr\n");
}

// Décale tous les éléments de la pile vers le bas
void reverse_rotate(t_pile *pile)
{
    if (!pile || pile->taille < 2)
        return;

    t_noeud *avant_dernier = NULL;
    t_noeud *dernier = pile->sommet;

    while (dernier->suivant)  // go jusqu'au dernier élément
    {
        avant_dernier = dernier;
        dernier = dernier->suivant;
    }

    avant_dernier->suivant = NULL;  // L'avant-dernier devient le dernier
    dernier->suivant = pile->sommet;  // Le dernier devient le premier
    pile->sommet = dernier;
}

// Applique reverse rotate sur la pile A
void rra(t_pile *a)
{
    reverse_rotate(a);
    printf("rra\n");
}

// Applique reverse rotate sur la pile B
void rrb(t_pile *b)
{
    reverse_rotate(b);
    printf("rrb\n");
}

// Applique reverse rotate sur les deux piles
void rrr(t_pile *a, t_pile *b)
{
    reverse_rotate(a);
    reverse_rotate(b);
    printf("rrr\n");
}
