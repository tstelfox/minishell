/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: zenotan <zenotan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/20 19:23:12 by zenotan       #+#    #+#                 */
/*   Updated: 2021/04/20 23:29:59 by zenotan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ghostshell.h"

int		check_quote(t_shell **ghost)
{
	char	type;
	int		check;
	int		i;
	char	**str;

	type = 0;
	check = 0;
	i = 0;
	str = (char **)&(*ghost)->tokens->content;
	while ((*str)[i])
	{
		if (((*str)[i] == '\"' || (*str)[i] == '\'') && type == 0)
			type = (*str)[i];
		if (type != 0 && (*str)[i] == type)
			check++;
		if (!(check % 2))
			type = 0;
		if ((*str)[i] == '$' && type != '\'')
			i += replace_env_quoted(ghost, str, i + 1) - 1;
		i++;
	}
	if (check % 2)
	{
		error_handler(ghost, NO_MULTI_LINE, "no multiline", NULL);
		return (-1);
	}
	(*str) = remove_quotes(ghost, (*str), ft_strlen((*str)) - check);
	free((*ghost)->tokens->content);
	(*ghost)->tokens->content = (*str);
	return (0);
}

int		check_meta(char *str)
{
	if (!ft_strcmp(str, ">") || !ft_strcmp(str, "<") || !ft_strcmp(str, "|"))
		return (1);
	return (0);
}

// int		check_colon(t_shell **ghost, t_list **temp, t_cmd **command)
int		check_colon(t_shell **ghost, t_cmd **command)
{
	if (!ft_strcmp((*ghost)->tokens->content, ";"))
	{
		(*ghost)->status = EXECUTE;
		if ((*ghost)->tokens->next)
			(*ghost)->tokens = (*ghost)->tokens->next;
		else
			(*ghost)->status = FINISHED;
		ft_lstadd_back(&(*ghost)->commands, ft_lstnew(*command));
		//---------------------------------------------------------------------------------------------------------------//parse
		return (1);
	}
	return (0);
}

int		check_seperator(t_shell **ghost, t_cmd **command)
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

int		check_redir(t_shell **ghost, t_cmd **command)
{
	t_redir *redir;
	t_dlist	*tokens;

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