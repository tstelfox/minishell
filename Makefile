# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: tmullan <tmullan@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2021/02/15 13:01:13 by tmullan       #+#    #+#                  #
#    Updated: 2021/05/31 15:58:04 by zenotan       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = ghostshell

OBJ_DIR = ./obj

ERR = error/error.c \
		error/err_msg.c \
		error/norm_made_us_do_it.c

UTIL = struct_utils.c \
		del_utils.c \
		env_utils.c \
		parser_utils.c \
		lst_utils.c \
		history_utils.c \
		handle_utils.c \
		miscellaneous_utils.c

PAR = parser.c \
		handle_funcs.c \
		handle_env.c \
		read_input.c \
		lexer.c

SHEL = shell_exec.c \
		prog_launch.c \
		redirect.c \
		pipe_exec.c \
		pipe_utils.c

BUILT = export.c \
		exit.c \
		unset.c \
		cd.c \
		echo.c \
		env.c \
		pwd.c

PAR_PREFIX = $(addprefix parser/, $(PAR))

UTIL_PREFIX = $(addprefix utils/, $(UTIL))

SHELL_PREFIX = $(addprefix shell_exec/, $(SHEL))

BUILT_PREFIX = $(addprefix built-ins/, $(BUILT))

SRC = main.c \
		$(ERR) \
		$(LEX_PREFIX) \
		$(PAR_PREFIX) \
		$(UTIL_PREFIX) \
		$(SHELL_PREFIX) \
		$(BUILT_PREFIX) \
		signal/signals.c

OBJ := $(SRC:%.c=$(OBJ_DIR)/%.o)

FLAGS = -Wall -Wextra -Werror

CC = gcc

INCLUDES = -Iincludes

REINS = -Ireins/incl -Ireins/lib/vector/incl

LIBFT = -Ilft/

TAIL = -lreins -Lreins -Lreins/lib/vector/ -lvector -ltermcap

all: $(NAME)

$(NAME): $(OBJ)
		@make -C reins/
		@make bonus -C lft/
		@$(CC) $(FLAGS) $(OBJ) $(INCLUDES) $(REINS) $(LIBFT) -lft -Llft $(TAIL) -g -o $(NAME)

$(OBJ_DIR)/%.o: %.c
		@mkdir -p $(@D)
		$(CC) $(FLAGS) $(INCLUDES) $(REINS) $(LIBFT) -g -c $< -o $@

clean:
		@make clean -C reins/
		@make clean -C lft/
		rm -rf $(OBJ_DIR)

fclean: clean
		@make fclean -C reins/
		@make fclean -C lft/
		rm -f $(NAME)

re: fclean all
