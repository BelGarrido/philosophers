CC = cc
CFLAGS = -Wall -Werror -Wextra -pthread -g #-fsanitize=thread
INC = -I include

NAME = philo

SRC= src/philo.c \
	src/utils.c \
	src/actions.c \
	src/routine.c \
	src/check_args.c \
	src/finalization_checks.c \
	src/clean.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(INC) $(OBJ) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
