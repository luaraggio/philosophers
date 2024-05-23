NAME = philos
CC = cc
CFLAGS = -Wall -Wextra -Werror -lpthread -g

SRCS =	./philo/functions.c \
		./philo/main.c \
		./philo/utils.c \
		./philo/initializations.c

.PHONY:
all: $(NAME)

.PHONY:
clean:
	rm -f $(NAME)
	rm -rf $(NAME).dSYM

.PHONY:
re: clean all

$(NAME):	$(SRCS)
			$(CC) $(CFLAGS) $(SRCS) -o $(NAME)