/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_bonus.h                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: ztan <ztan@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/05 16:37:27 by ztan          #+#    #+#                 */
/*   Updated: 2020/08/24 18:35:10 by ztan          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif
# ifndef FD_SIZE
#  define FD_SIZE 1000
# endif

int		get_next_line(int fd, char **line);
char	*copy_line(char *s1, int chr);
size_t	ft_strlen(const char *s);
char	*line_break(const char *s, int c);
char	*ft_strjoin(char *old, char *new);

#endif
