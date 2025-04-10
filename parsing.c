#include "push_swap.h"

// SPLIT
size_t	ft_strlcpy(char *dest, const char *src, size_t size_d)
{
	size_t	i;

	i = 0;
	if (size_d > 0)
	{
		while (src[i] != '\0' && i < size_d - 1)
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	i = 0;
	while (src[i] != '\0')
		i++;
	return (i);
}

size_t	count_tokens(char const *s, char delimeter)
{
	size_t	tokens;
	int		inside_token;

	tokens = 0;
	while (*s)
	{
		inside_token = 0;
		while (*s == delimeter && *s)
			++s;
		while (*s != delimeter && *s)
		{
			if (!inside_token)
			{
				++tokens;
				inside_token = 1;
			}
			++s;
		}
	}
	return (tokens);
}

int	safe_malloc(char **tokens_tab, int position, size_t buffer)
{
	int	i;

	i = 0;
	tokens_tab[position] = malloc(buffer);
	if (NULL == tokens_tab[position])
	{
		while (i < position)
			free(tokens_tab[i++]);
		free(tokens_tab);
		return (1);
	}
	return (0);
}

int	fill(char **tokens_tab, char const *s, char delimeter)
{
	size_t	len;
	int		i;

	i = 0;
	while (*s)
	{
		len = 0;
		while (*s == delimeter && *s)
			++s;
		while (*s != delimeter && *s)
		{
			++len;
			++s;
		}
		if (len)
		{
			if (safe_malloc(tokens_tab, i, len + 1))
				return (1);
			ft_strlcpy(tokens_tab[i], s - len, len + 1);
		}
		++i;
	}
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**tokens_tab;
	size_t	tokens;

	if (s == NULL)
		return (NULL);
	tokens = count_tokens(s, c);
	tokens_tab = malloc((tokens + 1) * sizeof(char *));
	if (NULL == tokens_tab)
		return (NULL);
	tokens_tab[tokens] = NULL;
	if (fill(tokens_tab, s, c))
		return (NULL);
	return (tokens_tab);
}
void	free_split(char **split)
{
	int	i = 0;

	if (!split)
		return;
	while (split[i])
		free(split[i++]);
	free(split);
}


// FIN SPLIT





int	is_number(char *str)
{
	int	i = 0;

	if (!str || !*str)
		return (0);
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])  // Si on a juste '+' ou '-' sans chiffres
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}


 // Retourne l'int et met overflow à 1 si dépassement
 
long	ft_atol_overflow(char *str, int *overflow)
{
	long	result = 0;
	long	sign = 1;
	long 	i = 0;
	*overflow = 0;

	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i])
	{
		result = result * 10 + (str[i] - '0');

		if ((sign == 1 && result > INT_MAX) ||
			(sign == -1 && result > (long)INT_MAX + 1))
		{
			*overflow = 1;
			return (0);
		}
		i++;
	}
	return (result * sign);
}


// Vérifie si un nombre est déjà présent dans la pile jusqu'à l'index donné

int	is_duplicate(int *stack, int index, int num)
{
	int	i = 0;
	while (i < index)
	{
		if (stack[i] == num)
			return (1);
		i++;
	}
	return (0);
}
// "2 7 0 5"
int	parse_single_arg(char **av, int **stack_a)
{
	char	**args; //tab de str obtenu en coupant av[1] grace a split
	int		count; // nb d'elements trouves dans args
	int		i;
	int		*stack; //tab a remplir 
	int		overflow;// flag int min/max

	args = ft_split(av[1], ' ');
	if (!args)
		return (-1);
	count = 0;
	while (args[count]) // compte cmb elements
		count++;
	if (count == 0)
	{
		free_split(args);
		return (-1);
	}
	stack = malloc(sizeof(int) * count); 
	if (!stack)
	{
		free_split(args);
		return (-1);
	}
	i = 0;
	while (i < count) // parcourt nb 
	{
		if (!is_number(args[i]))
		{
			free(stack);
			free_split(args);
			return (-1);
		}
		stack[i] = ft_atol_overflow(args[i], &overflow); //convers° str -> int
		if (overflow || is_duplicate(stack, i, stack[i]))
		{
			free(stack);
			free_split(args);
			return (-1);
		}
		i++;
	}
	free_split(args);
	*stack_a = stack;
	return (count);
}

// 2 7 0 5
int	parse_multiple_args(int ac, char **av, int **stack_a)
{
	int	size;
	int	*stack;
	int	i;
	int	overflow;

	size = ac - 1;
	stack = malloc(sizeof(int) * size);
	if (!stack)
		return (-1);
	i = 0;
	while (i < size)
	{
		if (!is_number(av[i + 1]))
		{
			free(stack);
			return (-1);
		}
		stack[i] = ft_atol_overflow(av[i + 1], &overflow);
		if (overflow || is_duplicate(stack, i, stack[i]))
		{
			free(stack);
			return (-1);
		}
		i++;
	}
	*stack_a = stack;
	return (size);
}
 
// Fonction principale 
int	parse_arguments(int ac, char **av, int **stack_a)
{
	if (ac < 2)
		return (0);
	if (ac == 2)
		return (parse_single_arg(av, stack_a));
	else
		return (parse_multiple_args(ac, av, stack_a));
}