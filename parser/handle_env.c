/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_env.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: zenotan <zenotan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/24 15:14:27 by zenotan       #+#    #+#                 */
/*   Updated: 2021/03/29 16:58:11 by ztan          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ghostshell.h"

char	*get_env(t_shell **ghost, char *name)
{
	char **list;
	int i;
	int j;

	if ((*ghost)->env)
		list = (*ghost)->env;
	i = 0;
	while (list[i])
	{
		j = 0;
		while (name[j] == list[i][j])
			j++;
		if (list[i][j] == '=')
			return (ft_substr(list[i], j + 1, ft_strlen(list[i])));
		i++;
	}
	return (NULL);
}

void	handle_env(t_shell **ghost, char **content)
{
	free(*content);
	*content = get_env(ghost, *content);
	if (!*content)
		error_handler(ghost, INVALID_ENV,  "Failed to recognize env", *content);
}