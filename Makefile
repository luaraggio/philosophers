NAME = philo.a
CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS =	./philo/functions.c\
		./philo/philo.c\

OBJS = ${SRCS:.c=.o}

all: $(NAME)

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) $(OBJS) -o $(NAME) 

clean: 
		rm -rf $(NAME)

fclean: clean

re:	fclean all

val:
	valgrind --leak-check=full --show-leak-kinds=all ./$(NAME)