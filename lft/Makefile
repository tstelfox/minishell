# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: ztan <ztan@student.codam.nl>                 +#+                      #
#                                                    +#+                       #
#    Created: 2019/11/06 18:10:05 by ztan          #+#    #+#                  #
#    Updated: 2021/05/17 09:27:33 by ztan          ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

FLAGS = -Wall -Wextra -Werror
SRC = ft_atoi.c \
	ft_bzero.c \
	ft_calloc.c \
	ft_isalnum.c \
	ft_isalpha.c \
	ft_isascii.c \
	ft_isdigit.c \
	ft_isprint.c \
	ft_memccpy.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_memcpy.c \
	ft_memmove.c \
	ft_memset.c \
	ft_strchr.c \
	ft_strdup.c \
	ft_strlcat.c \
	ft_strlcpy.c \
	ft_strlen.c \
	ft_strcmp.c \
	ft_strncmp.c \
	ft_strnstr.c \
	ft_strrchr.c \
	ft_tolower.c \
	ft_toupper.c \
	ft_substr.c \
	ft_strjoin.c \
	ft_strtrim.c \
	ft_putchar_fd.c \
	ft_putstr_fd.c \
	ft_putnbr_fd.c \
	ft_putendl_fd.c \
	ft_itoa.c \
	ft_strmapi.c \
	ft_split.c

BONUS = ft_lstnew_bonus.c \
	ft_lstadd_front_bonus.c \
	ft_lstsize_bonus.c \
	ft_lstlast_bonus.c \
	ft_lstadd_back_bonus.c \
	ft_lstdelone_bonus.c \
	ft_lstclear_bonus.c \
	ft_lstiter_bonus.c \
	ft_lstmap_bonus.c

BONUS2 = ft_dlist_addback_bonus.c \
	ft_dlist_addfront_bonus.c \
	ft_dlist_clear_bonus.c \
	ft_dlist_delone_bonus.c \
	ft_dlist_last_bonus.c \
	ft_dlist_new_bonus.c \
	ft_dlist_size_bonus.c \

OBJ = $(SRC:%.c=%.o)

OBJ2 = $(BONUS:%.c=%.o)

OBJ3 = $(BONUS2:%.c=%.o)

INCL = libft.h

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $?

%.o: %.c
	gcc $(FLAGS) -c $<

bonus: $(NAME) $(OBJ2) $(OBJ3)
	ar rcs $(NAME) $?

clean:
	/bin/rm -f $(OBJ) $(OBJ2) $(OBJ3)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
