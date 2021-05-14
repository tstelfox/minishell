/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: zenotan <zenotan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/20 19:23:12 by zenotan       #+#    #+#                 */
/*   Updated: 2021/05/15 00:24:22 by zenotan       ########   odam.nl         */
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

int	handle_seperator(t_shell **ghost, t_cmd **command)
{
	if (!ft_strcmp((*ghost)->tokens->content, "|"))
	{
		(*command)->seprator_type = PIPE;
		if ((*ghost)->tokens->next)
		{
			if (!ft_strcmp((*ghost)->tokens->next->content, "|"))
				error_handler(ghost, PARSE_ERROR,
					 "ghostshell does not support double pipes", NULL);
		}
		return (1);
	}
	if (!ft_strcmp((*ghost)->tokens->content, ";"))
		return (1);
	return (0);
}

int	handle_redir(t_shell **ghost, t_cmd **command)
{
	t_redir	*rdr;

	rdr = NULL;
	if (!ft_strcmp((*ghost)->tokens->content, ">"))
	{
		if (!ft_strcmp((*ghost)->tokens->next->content, ">"))
		{
			(*ghost)->tokens = (*ghost)->tokens->next;
			rdr = new_redir(ghost, (*ghost)->tokens->next->content, OUTPUT_ADD);
		}
		else
			rdr = new_redir(ghost, (*ghost)->tokens->next->content, OUTPUT);
		ft_lstadd_back(&(*command)->redirection, ft_lstnew(rdr));
		(*ghost)->tokens = (*ghost)->tokens->next;
	}
	else if (!ft_strcmp((*ghost)->tokens->content, "<"))
	{
		rdr = new_redir(ghost, (*ghost)->tokens->next->content, INPUT);
		ft_lstadd_back(&(*command)->redirection, ft_lstnew(rdr));
		(*ghost)->tokens = (*ghost)->tokens->next;
	}
	else
		return (0);
	return (1);
}

char	*handle_quotes(t_shell **ghost, char *str, int len)
{
	char	*ret;
	int		i;
	int		j;
	int		type;

	i = 0;
	j = 0;
	type = 0;
	ret = malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (error_handler(ghost, INTERNAL_ERROR, "failed malloc", NULL));
	while (str[i])
	{
		if ((str[i] == '\"' || str[i] == '\'') && type == 0)
			type = str[i];
		if (type != str[i] || type == 0)
			ret[j++] = str[i];
		i++;
		if (type == str[i])
			type = 0;
	}
	ret[j++] = '\0';
	return (ret);
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
