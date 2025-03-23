SRC = init.c  manage_threads.c  monitor.c  parse.c \
	philo.c  philo_routine.c tools.c  utility.c  tools2.c \

OBJS = $(SRC:.c=.o)

NAME = philo
CC = cc
CFLAG = -Wall -Wextra -Werror
RM = rm -rf

all: $(NAME)

$(NAME): $(OBJS)
		$(CC) $(CFLAG) $^ -o $@

%.o: %.c  philo.h
		$(CC) $(CFLAG) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: clean
