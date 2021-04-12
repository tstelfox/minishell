/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ztan <ztan@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/12 12:13:03 by ztan          #+#    #+#                 */
/*   Updated: 2021/04/12 19:11:51 by ztan          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ghostshell.h"

int 	valid_val(char *str)
{
	int i;

	i = 1;
	if (!ft_isalpha(str[0]))
		return (0);
	while (str[i] != '=')
	{
		if (!ft_isalnum(str[i]) || str[i] == '_')
			return (0);
		i++;
	}
	if (str[i + 1])
		return (2);
	return (1);
}

int		valid_word(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) || str[i] == '_')
			return (0);
		i++;
	}
	return (1);
}

int		valid_env(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

char	*is_env(t_shell **ghost, t_dlist *node)
{
	int i;
	bool 

	i = 0;
	while (node->content[i])
	{
		if (node->content[i] == '$')
			check
	}
}

t_dlist	*split_env(char *str)
{
	t_dlist	*new;
	int 	i;
	int 	start;
	char	*data;

	new = NULL;
	i = 0;
	while (str[i] != '=')
		i++;
	i++;
	start = i;
	data = ft_substr(str, 0, i);
	if (!data)
		return (NULL);
	ft_dlstadd_back(&new,ft_dlstnew(ft_strdup(data)));
	free(data);
	data = NULL;
	while (str[i])
		i++;
	data = ft_substr(str, start, i);
	if (!data)
		return (NULL);
	ft_dlstadd_back(&new,ft_dlstnew(data));
	return (new);
}