# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: zenotan <zenotan@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2020/07/14 14:14:59 by zenotan       #+#    #+#                  #
#    Updated: 2020/09/09 13:13:55 by zenotan       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = gnl.a

FLAGS = -Wall -Wextra -Werror
SRC = get_next_line.c \
		get_next_line_utils.c
OBJ = $(SRC:%.c=%.o)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $?

%.o: %.c
	gcc $(FLAGS) -c $<

clean:
	/bin/rm -rf $(OBJ)

fclean: clean
	/bin/rm -rf $(NAME)

re: fclean all