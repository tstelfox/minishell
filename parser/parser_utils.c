/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: zenotan <zenotan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/20 19:23:12 by zenotan       #+#    #+#                 */
/*   Updated: 2021/04/26 15:21:43 by ztan          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ghostshell.h"

int		check_meta(char *str)
{
	if (!ft_strcmp(str, ">") || !ft_strcmp(str, "<") || !ft_strcmp(str, "|"))
		return (1);
	return (0);
}

int		handle_colon(t_shell **ghost, t_list **new_lst, t_cmd **command)
{
	t_list *temp;

	temp = NULL;
	if (!ft_strcmp((*ghost)->tokens->content, ";"))
	{
		temp = ft_lstmap(*new_lst, copy_data, del_content);
		expand_env(ghost, &temp);
		remove_quotes(ghost, &temp);
		(*command)->type = ft_strdup(temp->content);
		(*command)->args = ft_lstmap(temp->next, copy_data, del_content);
		ft_lstclear(&temp, del_content);
		(*ghost)->status = EXECUTE;
		if ((*ghost)->tokens->next)
			(*ghost)->tokens = (*ghost)->tokens->next;
		else
			(*ghost)->status = FINISHED;
		return (1);
	}
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
	if (*list)
		temp = *list;
	while (temp)
	{
		str = temp->content;
		if ((qts = count_quotes(str)))
		{
			temp->content = handle_quotes(ghost, str, ft_strlen(str) - qts);
			free(str);
		}
		temp = temp->next;
	}
}
