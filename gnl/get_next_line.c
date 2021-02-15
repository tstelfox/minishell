/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: ztan <ztan@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/16 18:23:37 by ztan          #+#    #+#                 */
/*   Updated: 2020/09/08 14:21:36 by zenotan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	save_line(char **temp, char **tail, int fd)
{
	int		i;
	char	*tmp;

	i = 0;
	(*temp) = copy_line(tail[fd], '\n');
	while (tail[fd][i] != '\n' && tail[fd][i] != '\0')
		i++;
	if (tail[fd][i] == '\0')
	{
		free(tail[fd]);
		tail[fd] = NULL;
		return ;
	}
	tmp = copy_line(tail[fd] + i + 1, '\0');
	free(tail[fd]);
	tail[fd] = tmp;
}

int		get_line(char **temp, char **tail, int fd)
{
	char		*buffer;
	char		*tmp;
	int			bytes_read;

	while (!line_break(tail[fd], '\n'))
	{
		buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
		if (!buffer)
			return (-1);
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buffer);
			return (-1);
		}
		buffer[bytes_read] = '\0';
		tmp = tail[fd];
		tail[fd] = gnl_strjoin(tail[fd], buffer);
		free(tmp);
		free(buffer);
		if (bytes_read < 1)
			break ;
	}
	save_line(temp, tail, fd);
	return (0);
}

int		get_next_line(int fd, char **line)
{
	static char	*tail[FD_SIZE];
	char		*temp;
	int			flag;

	temp = NULL;
	if (!line || fd < 0 || read(fd, 0, 0) == -1)
		return (-1);
	flag = get_line(&temp, tail, fd);
	if (flag == -1)
		return (-1);
	if (tail[fd] != NULL)
		flag = 1;
	else
		flag = 0;
	(*line) = temp;
	return (flag);
}
