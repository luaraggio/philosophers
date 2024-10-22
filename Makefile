NAME = philos
CC = cc
CFLAGS = -Wall -Wextra -Werror -lpthread -g

# Colors
RESET=\033[0m
PURPLE = \033[35m
GREEN=\033[32m
PINK=\033[35m
RED=\033[31m
BLUE=\033[34m

SRCS =	./philo/srcs/main.c \
		./philo/srcs/philo_utils.c \
		./philo/srcs/libft_utils.c \
		./philo/srcs/structs.c \
		./philo/srcs/check_input.c \
		./philo/srcs/print_error.c

OBJS = ${SRCS:.c=.o}

%.o: %.c
	@$(CC) $(FLAGS) -c $< -o $@

all: $(NAME)
	@echo "$(PINK) 📖 Philo ready to be used!$(RESET)"

$(NAME):	$(OBJS)
			@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	@rm -f $(OBJS)
	@echo "$(BLUE) 📤 Objects deleted$(RESET)"

fclean:
		@rm -f $(NAME)
		@rm -f $(OBJS)
		@echo "$(BLUE) 🧼 All cleaned$(RESET)"

re: fclean all

val: re
	valgrind  --leak-check=full --show-leak-kinds=all --track-fds=yes ./$(NAME)

