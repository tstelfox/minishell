/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: zenotan <zenotan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/20 19:23:12 by zenotan       #+#    #+#                 */
/*   Updated: 2021/05/17 09:34:03 by ztan          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ghostshell.h"

int	check_redir(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i - 1] == '\'')
			while (str[i] != '\'' && str[i])
				i++;
		if (str[i - 1] == '"')
			while (str[i] != '"' && str[i])
				i++;
		if (str[i] == ' ' || str[i] == '\n' || str[i] == '\t')
			return (1);
		i++;
	}
	return (0);
}

int	check_meta(char *str)
{
	if (!ft_strcmp(str, ">") || !ft_strcmp(str, "<") || !ft_strcmp(str, "|"))
		return (1);
	return (0);
}

int	count_quotes(char *str)
{
	int	type;
	int	check;
	int	i;

	i = 0;
	type = 0;
	check = 0;
	while (str[i])
	{
		if ((str[i] == '\"' || str[i] == '\'') && type == 0)
			type = str[i];
		if (type != 0 && str[i] == type)
			check++;
		if (!(check % 2))
			type = 0;
		i++;
	}
	return (check);
}

void	remove_quotes(t_shell **ghost, t_list **list)
{
	char	*str;
	int		qts;
	t_list	*temp;

	temp = NULL;
	if ((*ghost)->error || !list || !*list)
		return ;
	if (*list)
		temp = *list;
	while (temp)
	{
		str = temp->content;
		qts = count_quotes(str);
		if (qts)
		{
			free(temp->content);
			temp->content = handle_quotes(ghost, str, ft_strlen(str) - qts);
		}
		temp = temp->next;
	}
}
