# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: tmullan <tmullan@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2021/02/15 13:01:13 by tmullan       #+#    #+#                  #
#    Updated: 2021/05/24 18:59:21 by tmullan       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = ghostshell

OBJ_DIR = ./obj

ERR = error/error.o \
		error/err_msg.o \
		error/norm_made_us_do_it.o

UTIL = struct_utils.o \
		del_utils.o \
		env_utils.o \
		parser_utils.o \
		lst_utils.o \
		history_utils.o \
		handle_utils.o \
		miscellaneous_utils.o

PAR = parser.o \
		handle_funcs.o \
		handle_env.o \
		read_input.o \
		lexer.o

SHEL = shell_exec.o \
		prog_launch.o \
		redirect.o \
		pipe_exec.o \

BUILT = export.o \
		exit.o \
		unset.o \
		cd.o \
		echo.o \
		env.o \
		pwd.o

PAR_PREFIX = $(addprefix parser/, $(PAR))

UTIL_PREFIX = $(addprefix utils/, $(UTIL))

SHELL_PREFIX = $(addprefix shell_exec/, $(SHEL))

BUILT_PREFIX = $(addprefix built-ins/, $(BUILT))

SRC = main.o \
		$(ERR) \
		$(LEX_PREFIX) \
		$(PAR_PREFIX) \
		$(UTIL_PREFIX) \
		$(SHELL_PREFIX) \
		$(BUILT_PREFIX) \
		signal/signals.o

OBJ = $(SRC)

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

%.o: %.c
		@mkdir -p $(OBJ_DIR)
		$(CC) $(FLAGS) $(INCLUDES) $(REINS) $(LIBFT) -g -c $< -o $@

clean:
		@make clean -C reins/
		@make clean -C lft/
		rm -rf $(OBJ)

fclean: clean
		@make fclean -C reins/
		@make fclean -C lft/
		rm -f $(NAME)

re: fclean all
