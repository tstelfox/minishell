/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: zenotan <zenotan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/20 19:23:12 by zenotan       #+#    #+#                 */
/*   Updated: 2021/05/05 13:52:47 by zenotan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ghostshell.h"

int		check_redir(char *str)
{
	int i;
	
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

int		check_meta(char *str)
{
	if (!ft_strcmp(str, ">") || !ft_strcmp(str, "<") || !ft_strcmp(str, "|"))
		return (1);
	return (0);
}

int		handle_seperator(t_shell **ghost, t_cmd **command)
{
	if (!ft_strcmp((*ghost)->tokens->content, "|"))
	{
		(*command)->seprator_type = PIPE;
		if (!ft_strcmp((*ghost)->tokens->next->content, "|"))
			error_handler(ghost, PARSE_ERROR, "ghostshell does not support double pipes", NULL);
		return (1);
	}
	return (0);
}

int		handle_redir(t_shell **ghost, t_cmd **command)
{
	t_redir *redir;
	t_list	*tokens;

	redir = NULL;
	tokens = (*ghost)->tokens;
	if (!ft_strcmp(tokens->content, ">"))
	{
		if (!ft_strcmp(tokens->next->content, ">")) // check for ">>"
		{
			tokens = tokens->next;
			redir = new_redir(ghost, tokens->next->content, OUTPUT_ADD);
		}
		else
			redir = new_redir(ghost, tokens->next->content, OUTPUT);
		ft_lstadd_back(&(*command)->redirection, ft_lstnew(redir));
		(*ghost)->tokens = tokens->next;
	}
	else if (!ft_strcmp(tokens->content, "<"))
	{
		redir = new_redir(ghost, tokens->next->content, INPUT);
		ft_lstadd_back(&(*command)->redirection, ft_lstnew(redir));
		(*ghost)->tokens = tokens->next;
	}
	else
		return (0);
	return (1);
}

char 	*handle_quotes(t_shell **ghost, char *str, int len)
{
	char *ret;
	int i;
	int j;
	int type;
	int check;

	i = -1;
	j = 0;
	check = 0;
	type = 0;
	if (!(ret = malloc(sizeof(char) * (len + 1))))
		return (error_handler(ghost, INTERNAL_ERROR, "failed malloc", NULL));
	while (str[(i++) + 1])
	{
		if ((str[i] == '\"' || str[i] == '\'') && type == 0)
			type = str[i];
		if (type != 0 && str[i] == type)
			check++;
		if (type != str[i] || type == 0)
			ret[j++] = str[i];
		if (!(check % 2))
			type = 0;
	}
	ret[j++] = '\0';
	return (ret);
}

int		count_quotes(char *str)
{
	int type;
	int check;
	int i;

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
	if ((*ghost)->error)
		return ;
	if (*list)
		temp = *list;
	ft_putchar_fd('\n', STDOUT_FILENO);
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
