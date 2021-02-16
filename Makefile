# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: tmullan <tmullan@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2021/02/15 13:01:13 by tmullan       #+#    #+#                  #
#    Updated: 2021/02/16 01:10:56 by zenotan       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = ghostshell

SRC = main.c \
		gnl/get_next_line.c \
		gnl/get_next_line_utils.c \
		$(UTILS)

UTILS = lft_utils/*.c

OBJ = $(SRC:.c=.o)

LIBS = gnl/gnl.a

FLAGS = -Wall -Wextra -Werror

CC = gcc

INCLUDES = -Iincludes

all: $(NAME)

$(NAME): $(OBJ)
		@gcc $(FLAGS) $(OBJ) $(INCLUDES) -g -o $(NAME)

# %.o: %.c
# 		$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

clean:
		rm -f $(OBJ)

fclean: clean
		rm -f $(NAME)

re: fclean all