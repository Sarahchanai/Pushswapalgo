#include "push_swap.h"

// Fonction pour afficher clairement le result des piles
void afficher_result(t_pile *a, t_pile *b, char *message)
{
    printf("\n%s\n", message);
    printf("Pile A : ");
    afficher_pile(a);
    printf("Pile B : ");
    afficher_pile(b);
}

t_pile *init_pile(int *valeurs, int taille)
{
    t_pile *pile = malloc(sizeof(t_pile));
    if (!pile)
        return (NULL);
    pile->sommet = NULL;
    pile->taille = 0;

    int i = 0;
    while (i < taille)
    {
        ajouter_sommet(pile, valeurs[i]);
        i++;
    }
    return (pile);
}

/*int main()
{
    int valeurs[] = {4, 3, 2, 1};
    t_pile *a = init_pile(valeurs, 4);
    t_pile *b = malloc(sizeof(t_pile));
    if (!b)
        return (1);
    b->sommet = NULL;
    b->taille = 0;

    afficher_result(a, b, "🍋 Piles initiales");

    sa(a);
    afficher_result(a, b, "🍋 Après sa");

    pb(a, b);
    afficher_result(a, b, "🍋 Après pb");

    pb(a, b);
    afficher_result(a, b, "🍋 Après pb");

    pa(a, b);
    afficher_result(a, b, "🍋 Après pa");

    sb(b);
    afficher_result(a, b, "🍋 Après sb");

    ss(a, b);
    afficher_result(a, b, "🍋 Après ss");

    ra(a);
    afficher_result(a, b, "🍋 Après ra");

    rb(b);
    afficher_result(a, b, "🍋 Après rb");

    rr(a, b);
    afficher_result(a, b, "🍋 Après rr");

    rra(a);
    afficher_result(a, b, "🍋 Après rra");

    rrb(b);
    afficher_result(a, b, "🍋 Après rrb");

    rrr(a, b);
    afficher_result(a, b, "🍋 Après rrr");

    return 0;
}*/
