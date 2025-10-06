CC = gcc
SAN ?= tsan
CBASE = -Wall -Werror -Wextra -g -O0 -fno-omit-frame-pointer -pthread
ifeq ($(SAN),tsan)
	CFLAGS = $(CBASE) -fsanitize=thread
	LDFLAGS = -fsanitize=thread -pthread
else
	CFLAGS = $(CBASE)
	LDFLAGS = -pthread
endif

NAME = philo

SRC= philo.c \
	utils.c \
	actions.c \
	routine.c \
	check_args.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@echo "[LINK] $(CC) $(OBJ) $(LDFLAGS) -o $(NAME)"
	$(CC) $(OBJ) $(LDFLAGS) -o $(NAME)

%.o: %.c
	@echo "[CC] $<"
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

show:
	@echo CC=$(CC)
	@echo CFLAGS=$(CFLAGS)
	@echo LDFLAGS=$(LDFLAGS)
	@echo SRC=$(SRC)
	@echo OBJ=$(OBJ)

helgrind: SAN=none
helgrind: re
	@echo "Run under Helgrind: valgrind --tool=helgrind ./$(NAME) <args>"

.PHONY: all clean fclean re
