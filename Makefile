# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: tmullan <tmullan@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2021/02/15 13:01:13 by tmullan       #+#    #+#                  #
#    Updated: 2021/03/04 11:20:34 by tmullan       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = ghostshell

GNL = gnl/get_next_line.c \
		gnl/get_next_line_utils.c

LFT = lft_utils/ft_putstr_fd.c \
		lft_utils/ft_putnbr_fd.c \
		lft_utils/ft_putchar_fd.c \
		lft_utils/ft_strlen.c \
		lft_utils/ft_strcmp.c \
		lft_utils/ft_split.c \
		lft_utils/ft_memcpy.c \
		lft_utils/ft_strchr.c \
		lft_utils/ft_strdup.c \
		lft_utils/ft_strlcpy.c \
		lft_utils/ft_substr.c \
		lft_utils/ft_strjoin.c \
		lft_utils/ft_lstadd_back_bonus.c \
		lft_utils/ft_lstclear_bonus.c \
		lft_utils/ft_lstdelone_bonus.c \
		lft_utils/ft_lstiter_bonus.c \
		lft_utils/ft_lstnew_bonus.c \
		lft_utils/ft_lstsize_bonus.c \
		lft_utils/ft_lstlast_bonus.c \
		lft_utils/ft_strnstr.c \
		debug/printlists.c

ERR = error/error.c

LEX = lexer/read_input.c \
		lexer/lexer.c

SRC = main.c shell_exec.c \
		prog_launch.c \
		$(GNL) \
		$(LFT) \
		$(ERR) \
		$(LEX)

OBJ = $(SRC:.c=.o)

FLAGS = -Wall -Wextra -Werror

CC = gcc

INCLUDES = -Iincludes

all: $(NAME)

$(NAME): $(OBJ)
		@gcc $(FLAGS) $(OBJ) $(INCLUDES) -g -o $(NAME)

%.o: %.c
		$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

clean:
		rm -f $(OBJ)

fclean: clean
		rm -f $(NAME)

re: fclean all