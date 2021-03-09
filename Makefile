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

LFT = ft_putstr_fd.c \
		ft_putnbr_fd.c \
		ft_putchar_fd.c \
		ft_strlen.c \
		ft_split.c \
		ft_memcpy.c \
		ft_strchr.c \
		ft_strdup.c \
		ft_strlcpy.c \
		ft_substr.c \
		ft_strjoin.c \
		ft_strnstr.c \
		ft_strcmp.c \
		ft_lstadd_back_bonus.c \
		ft_lstclear_bonus.c \
		ft_lstdelone_bonus.c \
		ft_lstiter_bonus.c \
		ft_lstnew_bonus.c \
		ft_lstsize_bonus.c \
		ft_lstadd_front_bonus.c

ERR = error/error.c

LEX = read_input.c \
		lexer.c

PAR = parser.c

PAR_PREFIX = $(addprefix parser/, $(PAR))

LFT_PREFIX = $(addprefix lft_utils/, $(LFT))

LEX_PREFIX = $(addprefix lexer/, $(LEX))

SRC = main.c shell_exec.c \
		prog_launch.c \
		$(GNL) \
		$(LFT_PREFIX) \
		$(ERR) \
		$(LEX_PREFIX) \
		$(PAR_PREFIX) \
		debug/printlists.c

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