#ifndef PUSH_SWAP_H
#define PUSH_SWAP_H


#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

typedef struct s_noeud  // Un élément de la pile
{
    int valeur;
    struct s_noeud *suivant;
} t_noeud;

typedef struct s_pile  // La pile complète
{
    t_noeud *sommet;
    int taille;
} t_pile;

typedef struct s_cost 
{
    int element;
    int cost_a;
    int cost_b;
    int total;
} t_cost;



// fonctions gestion pile
t_noeud *nouveau_element(int valeur);
void ajouter_sommet(t_pile *pile, int valeur);
void afficher_pile(t_pile *pile);
void afficher_result(t_pile *a, t_pile *b, char *message);
t_pile *init_pile(int *valeurs, int taille);




// Instructions
void swap(t_pile *pile);
void sa(t_pile *a);
void sb(t_pile *b);
void ss(t_pile *a, t_pile *b);
void pa(t_pile *a, t_pile *b);
void pb(t_pile *a, t_pile *b);
void rotate(t_pile *pile);
void ra(t_pile *a);
void rb(t_pile *b);
void rr(t_pile *a, t_pile *b);
void reverse_rotate(t_pile *pile);
void rra(t_pile *a);
void rrb(t_pile *b);
void rrr(t_pile *a, t_pile *b);


// Fonctions parsing
size_t  ft_strlcpy(char *dest, const char *src, size_t size_d);
int		ft_strlen(char *str);
size_t  count_tokens(char const *s, char delimeter);
int	    safe_malloc(char **tokens_tab, int position, size_t buffer);
int	    fill(char **tokens_tab, char const *s, char delimeter);
char    **ft_split(char const *s, char c);
void	free_split(char **split);
int     is_number(char *str);
long	ft_atol_overflow(char *str, int *overflow);
int     is_duplicate(int *stack, int index, int num);
int     parse_single_arg(char **av, int **stack_a);
int     parse_multiple_args(int ac, char **av, int **stack_a);
int	    parse_arguments(int ac, char **av, int **stack_a);




// Fonctions algo

void    ft_swap(int *a, int *b);
int     *remplir_tableau(t_pile *pile);
void    sort_int_tab(int *tab, unsigned int size);
int     est_triee(t_pile *pile);
int     trouve_min(t_pile *pile);
int     trouve_max(t_pile *pile);
int     trouve_position(t_pile *pile, int valeur);
int     trouver_position_min(t_pile *pile);
void    trier_2_elements(t_pile *pile_a);
void    trier_3_elements(t_pile *pile_a);
void    trier_4_elements(t_pile *pile_a);
void    trier_5_elements(t_pile *pile_a);
int     determiner_nombre_chunks(int taille);
int     get_pivot(int *tab, int taille, int chunk_idx, int total_chunks);
void    transferer_elements(t_pile *pile_a, t_pile *pile_b, int pivot, int *count);
void    phase_1_chunks(t_pile *pile_a, t_pile *pile_b);
void    deplacer_au_sommet(t_pile *pile, int pos);
void    phase_2_optimisee(t_pile *pile_a, t_pile *pile_b);
void    ajuster_final(t_pile *pile_a);
void    trier_piles(t_pile *pile_a, t_pile *pile_b);
void    free_pile(t_pile *pile);


#endif
