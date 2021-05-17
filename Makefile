# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: tmullan <tmullan@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2021/02/15 13:01:13 by tmullan       #+#    #+#                  #
#    Updated: 2021/05/17 12:41:37 by ztan          ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = ghostshell

ERR = error/error.c \
		error/err_msg.c

UTIL = struct_utils.c \
		del_utils.c \
		env_utils.c \
		parser_utils.c \
		lst_utils.c \
		history_utils.c \
		miscellaneous_utils.c

PAR = parser.c \
		handle_funcs.c \
		handle_env.c \
		read_input.c \
		lexer.c

SHEL = shell_exec.c \
		prog_launch.c \
		redirect.c \
		pipe_exec.c

TEST = test.c

PAR_PREFIX = $(addprefix parser/, $(PAR))

UTIL_PREFIX = $(addprefix utils/, $(UTIL))

SHELL_PREFIX = $(addprefix shell_exec/, $(SHEL))

SRC = main.c \
		$(GNL) \
		$(ERR) \
		$(LEX_PREFIX) \
		$(PAR_PREFIX) \
		$(UTIL_PREFIX) \
		$(SHELL_PREFIX) \
		debug/printlists.c \

OBJ = $(SRC:.c=.o)

FLAGS = -Wall -Wextra -Werror

CC = gcc

INCLUDES = -Iincludes

REINS = -Ireins_termcap/incl -Ireins_termcap/lib/vector/incl

LIBFT = -Ilft/

# GNL = -Ignl/

# GNL_TAIL = -lgnl -Lgnl

LEAKS = -fsanitize=leak

TAIL	=	-lreins -Lreins_termcap -Lreins_termcap/lib/vector/ -lvector -ltermcap

all: $(NAME)

$(NAME): $(OBJ)
		@make -C reins_termcap/
		@make bonus -C lft/
		@$(CC) $(FLAGS) $(OBJ) $(INCLUDES) $(REINS) $(LIBFT) -lft -Llft $(TAIL) -g -o $(NAME)

%.o: %.c
		$(CC) $(FLAGS) $(INCLUDES) $(REINS) $(LIBFT) -g -c $< -o $@

clean:
		@make clean -C reins_termcap/
		@make clean -C lft/
		rm -f $(OBJ)

fclean: clean
		@make fclean -C reins_termcap/
		@make fclean -C lft/
		rm -f $(NAME)

re: fclean all
