NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -lpthread

SRCS =	./philo/functions.c \
		./philo/main.c \
		./philo/utils.c \
		./philo/initializations.c

all: $(NAME)

$(NAME):	$(SRCS)
			$(CC) $(CFLAGS) $(SRCS) -o $(NAME)