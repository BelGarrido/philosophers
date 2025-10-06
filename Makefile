CC = gcc -pthread
CFLAGS = -Wall -Werror -Wextra -g #-fsanitize=thread

NAME = philo

SRC= philo.c \
	utils.c \
	actions.c \
	routine.c \
	check_args.c \
	finalization_checks.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
