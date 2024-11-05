NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -lpthread

# Colors
RESET=\033[0m
PURPLE = \033[35m
GREEN=\033[32m
PINK=\033[35m
RED=\033[31m
BLUE=\033[34m

SRCS =	srcs/main.c \
		srcs/check_input.c \
		srcs/init_structs.c \
		srcs/libft_utils.c \
		srcs/mutex.c \
		srcs/philo_routines.c \
		srcs/time.c \
		srcs/status.c \
		srcs/clean.c \
		srcs/dinner.c

OBJS = ${SRCS:.c=.o}

%.o: %.c
	@$(CC) $(FLAGS) -c $< -o $@

all: $(NAME)
	@echo "$(PINK) 📖 Philo ready to be used!$(RESET)"

$(NAME):	$(OBJS)
			@$(CC) $(CFLAGS) $(SRCS) -o $(NAME)

clean:
	@rm -f $(OBJS)
	@echo "$(BLUE) 📤 Objects deleted$(RESET)"

fclean:
		@rm -f $(NAME)
		@rm -f $(OBJS)
		@echo "$(BLUE) 🧼 All cleaned$(RESET)"

re: fclean all

t: all
	./$(NAME) 1 10 5 5
	./$(NAME) 5 800 200 200


val: re
	valgrind  --leak-check=full --show-leak-kinds=all --track-fds=yes ./$(NAME)

