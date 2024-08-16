# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: omartela <omartela@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/07 16:41:30 by omartela          #+#    #+#              #
#    Updated: 2024/08/16 14:32:39 by omartela         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
CC = cc
NAME = philo
SRC = src/main.c \
	  src/utilities.c \
	  src/cleanup.c \
	  src/parseinput.c \
	  src/routine.c \
	  src/simulation.c \
	  src/init.c

OBJS = $(SRC:.c=.o)

INCLUDES = includes/
CFLAGS = -g -Wall -Werror -Wextra

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean:
	$(RM) $(OBJS)
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
