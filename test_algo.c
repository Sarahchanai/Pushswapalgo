#include "push_swap.h"

void free_pile(t_pile *pile)
{
    t_noeud *actuel;
    t_noeud *temp;

    if (pile)
    {
        actuel = pile->sommet;
        while (actuel)
        {
            temp = actuel->suivant;
            free(actuel);  // Libérer chaque noeud
            actuel = temp;
        }
        free(pile);
    }
}

int	main(int ac, char **av)
{
	int		*valeurs;
	int		taille;
	t_pile	*pile_a;
	t_pile	*pile_b;

	taille = parse_arguments(ac, av, &valeurs);
	if (taille == 0)
		return (0);

	pile_a = init_pile(valeurs, taille);
	free(valeurs);
	if (!pile_a)
		return (1);

	pile_b = malloc(sizeof(t_pile));
	if (!pile_b)
	{
		free_pile(pile_a);
		return (1);
	}
	pile_b->sommet = NULL;
	pile_b->taille = 0;

    printf("Affichage de pile A avant le tri :\n");
	afficher_pile(pile_a); //avant tri 

	trier_piles(pile_a, pile_b);
    printf("Affichage de pile A après le tri :\n");
    afficher_pile(pile_a); // après tri

	free_pile(pile_a);
	free_pile(pile_b);
	return (0);
}
