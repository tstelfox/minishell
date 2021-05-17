/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_funcs.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: ztan <ztan@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/17 09:33:36 by ztan          #+#    #+#                 */
/*   Updated: 2021/05/17 11:21:03 by ztan          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ghostshell.h"

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
	int		j;
	int		type;

	j = 0;
	type = 0;
	ret = malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (error_handler(ghost, INTERNAL_ERROR, "failed malloc", NULL));
	while (*str)
	{
		if ((*str == '\"' || *str == '\'') && type == 0)
			type = *str;
		if (type != *str || type == 0)
			ret[j++] = *str;
		str++;
		if (type == *str && type != 0)
		{
			type = 0;
			if (str + 1)
				str++;
		}
	}
	ret[j++] = '\0';
	return (ret);
}

void	check_seperator(t_shell **ghost, t_list *tokens)
{
	if (!ft_strcmp(tokens->content, "|"))
		if (!ft_strcmp(tokens->next->content, ";"))
			error_handler(ghost, SYNTAX_ERROR,
				 "syntax error near unexpected token", tokens->next->content);
	if (!ft_strcmp(tokens->content, ";"))
	{
		if (!ft_strcmp(tokens->next->content, "|"))
			error_handler(ghost, SYNTAX_ERROR,
				 "syntax error near unexpected token", tokens->next->content);
		if (!ft_strcmp(tokens->next->content, ";"))
			error_handler(ghost, SYNTAX_ERROR,
				 "syntax error near unexpected token", tokens->next->content);
	}
}

int	handle_syntax(t_shell **ghost, t_list *lst)
{
	t_list	*temp;

	temp = lst;
	while (temp)
	{
		if (temp->next)
		{
			check_seperator(ghost, temp);
			if ((!ft_strcmp(temp->content, ">")
					 || !ft_strcmp(temp->next->content, ">"))
				 	 && !temp->next->next)
				error_handler(ghost, SYNTAX_ERROR,
					 "syntax error near unexpected token", "newline");
		}
		else if (!ft_strcmp(temp->content, ">")
			 || !ft_strcmp(temp->content, "<"))
			error_handler(ghost, SYNTAX_ERROR,
				 "syntax error near unexpected token", "newline");
		if ((*ghost)->error == SYNTAX_ERROR)
			return (1);
		temp = temp->next;
	}
	return (0);
}
