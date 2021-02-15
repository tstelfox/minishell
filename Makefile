# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: tmullan <tmullan@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2021/02/15 13:01:13 by tmullan       #+#    #+#                  #
#    Updated: 2021/02/15 20:16:03 by zenotan       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = ghostshell

SRC = main.c

OBJ = $(SRC:%.c=%.o)

LIBS = lft/libft.a \
		gnl/gnl.a

FLAGS = -Wall -Wextra -Werror

CC = gcc

all: $(NAME)

$(NAME): $(OBJ)
		make -C gnl/
		make -C lft/
		$(CC) -o $(NAME) $(LIBS) $(OBJ)

%.o: %.c
		$(CC) $(FLAGS) -c $< -o $@

clean:
		make clean -C gnl/
		make clean -C lft/
		rm -f $(OBJ)

fclean: clean
		make fclean -C gnl/
		make fclean -C lft/
		rm -f $(NAME)

re: fclean all