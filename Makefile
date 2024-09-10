NAME = philosophers
CC = cc
CFLAGS = -Wall -Wextra -Werror -lpthread -g

SRCS =	./philo/philo_utils.c \
		./philo/libft_utils.c \
		./philo/main.c \
		./philo/validations.c \
		./philo/initializations.c \
		.philo/routines.c

$(NAME):	$(SRCS)
			$(CC) $(CFLAGS) $(SRCS) -o $(NAME)

all: $(NAME)

clean:
	rm -f $(NAME)
	rm -rf $(NAME).dSYM

re: clean all

