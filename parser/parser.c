/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: zenotan <zenotan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/15 19:14:32 by zenotan       #+#    #+#                 */
/*   Updated: 2021/04/21 22:40:16 by zenotan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ghostshell.h"

char 	*remove_quotes(t_shell **ghost, char *str, int len)
{
	char *ret;
	int i;
	int j;
	int type;
	int check;

	i = 0;
	j = 0;
	check = 0;
	type = 0;
	ret = malloc(sizeof(char) * (len + 1));
	if (!ret)
	{
		error_handler(ghost, INTERNAL_ERROR, "no multiline", NULL);
		return (NULL);
	}
	while (str[i])
	{
		if ((str[i] == '\"' || str[i] == '\'') && type == 0)
			type = str[i];
		if (type != 0 && str[i] == type)
			check++;
		if (type != str[i] || type == 0)
		{
			ret[j] = str[i];
			j++;
		}
		if (!(check % 2))
			type = 0;
		i++;
	}
	ret[j] = '\0';
	return (ret);
}

void	parser(t_shell **ghost, t_list **temp, t_cmd **command)
{
	(*command)->type = ft_strdup((*temp)->content);
	(*temp) = (*temp)->next;
	while ((*temp) && (*ghost)->status == PARSE)
	{
		ft_lstadd_back(&(*command)->args, ft_lstnew(ft_strdup((*temp)->content)));
		(*temp) = (*temp)->next;
	}
}

void	parser_loop(t_shell **ghost)
{
	t_cmd	*command;
	t_list	*temp = NULL;

	if ((*ghost)->commands)
		ft_lstclear(&(*ghost)->commands, del_commands);
	while ((*ghost)->tokens && (*ghost)->status == PARSE && !(*ghost)->status)
	{
		if (check_quote(ghost))
			break ;
		command = new_command();
		ft_lstadd_back(&temp, ft_lstnew(ft_strdup((*ghost)->tokens->content)));
		(*ghost)->tokens = (*ghost)->tokens->next;
		while ((*ghost)->tokens && (*ghost)->status == PARSE) //parse command
		{
			// if (check_colon(ghost, &temp, &command)) //parse shit in here
			if (check_colon(ghost, &command)) //parse shit in here
				return ;
			if (check_seperator(ghost, &command))
				break ;
			if (!check_redir(ghost, &command))
				ft_lstadd_back(&temp, ft_lstnew(ft_strdup((*ghost)->tokens->content)));
			if (!(*ghost)->tokens)
				break ;
			(*ghost)->tokens = (*ghost)->tokens->next;
		}
		parser(ghost, &temp, &command);
		print_cmd(command);
		ft_lstadd_back(&(*ghost)->commands, ft_lstnew(command));
		if (!(*ghost)->tokens)
			break ;
		(*ghost)->tokens = (*ghost)->tokens->next;
	}
	(*ghost)->status = FINISHED;
}
