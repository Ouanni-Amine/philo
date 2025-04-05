SRC = init_bonus.c  management_bonus.c parse_bonus.c \
	philo_bonus.c  philo_routine_bonus.c tools_bonus.c  utility_bonus.c  tools2_bonus.c \

OBJS = $(SRC:.c=.o)

NAME = philo_bonus
CC = cc
CFLAG = -Wall -Wextra -Werror
RM = rm -rf

all: $(NAME)

$(NAME): $(OBJS)
		$(CC) $(CFLAG) $^ -o $@

%.o: %.c  philo_bonus.h
		$(CC) $(CFLAG) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: clean
