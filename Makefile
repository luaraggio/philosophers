NAME = philos
CC = cc
CFLAGS = -g -Wall -Wextra -Werror -lpthread

# Colors
RESET=\033[0m
PURPLE = \033[35m
GREEN=\033[32m
PINK=\033[35m
RED=\033[31m
BLUE=\033[34m

SRCS =	./philo/srcs/main.c \
		./philo/srcs/check_input.c \
		./philo/srcs/clear.c \
		./philo/srcs/init_structs.c \
		./philo/srcs/libft_utils.c \
		./philo/srcs/mutex.c \
		./philo/srcs/print_msgs.c \
		./philo/srcs/philo_routines.c \
		./philo/srcs/time.c \
		./philo/srcs/status.c \

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

val: re
	valgrind  --leak-check=full --show-leak-kinds=all --track-fds=yes ./$(NAME)

