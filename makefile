NAME  = push_swap
CC = cc
FLAG =  -fsanitize=address -Wall -Wextra -Werror -I .

SRCS = operations.c pile.c test_ope.c parsing.c test_parsing.c algo.c test_algo.c

OBJ = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	cc $(FLAG) -o $(NAME) $(OBJ)	

%.o: %.c push_swap.h
	cc $(FLAG) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
