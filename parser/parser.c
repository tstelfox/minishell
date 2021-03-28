/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: zenotan <zenotan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/15 19:14:32 by zenotan       #+#    #+#                 */
/*   Updated: 2021/03/26 14:30:10 by zenotan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ghostshell.h"

char	**get_envp(char **envp)
{
	char	**env;
	int		i;
	int		k;

	i = 0;
	k = 0;
	while (envp[i])
		i++;
	env = (char **)malloc(sizeof(char *) * (i + 1));
	if (!env)
		return (NULL);
	while (envp[k])
	{
		env[k] = ft_strdup(envp[k]);
		k++;
	}
	env[k] = 0;
	return (env);
}

int		check_meta(char *str)
{
	if (!ft_strcmp(str, ">") || !ft_strcmp(str, "<") || !ft_strcmp(str, "|"))
		return (1);
	return (0);
}

int		check_colon(t_shell **ghost, t_cmd *command)
{
	(void)command;
	if (!ft_strcmp((*ghost)->tokens->content, ";"))
	{
		// command->seprator_type = SEPERATOR;
		(*ghost)->status = EXECUTE;
		if ((*ghost)->tokens->next)
			(*ghost)->tokens = (*ghost)->tokens->next;
		else
			(*ghost)->status = FINISHED;
		return (1);
	}
	return (0);
}

int		check_seperator(t_shell **ghost, t_cmd *command)
{
	if (!ft_strcmp((*ghost)->tokens->content, "|"))
	{
		command->seprator_type = PIPE;
		if (!ft_strcmp((*ghost)->tokens->next->content, "|"))
			error_handler(ghost, PARSE_ERROR, "ghostshell does not support double pipes", NULL);
		return (1);
	}
	return (0);
}

int		check_redir(t_shell **ghost, t_cmd *command)
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
		ft_lstadd_back(&command->redirection, ft_lstnew(redir));
		(*ghost)->tokens = tokens->next;
	}
	else if (!ft_strcmp(tokens->content, "<"))
	{
		redir = new_redir(ghost, tokens->next->content, INPUT);
		ft_lstadd_back(&command->redirection, ft_lstnew(redir));
		(*ghost)->tokens = tokens->next;
	}
	else
		return (0);
	return (1);
}

void	parser(t_shell **ghost)
{
	t_cmd	*command;

	if ((*ghost)->commands)
		ft_lstclear(&(*ghost)->commands, del_commands);
	while ((*ghost)->tokens && (*ghost)->status == PARSE)
	{
		command = new_command();
		command->type = ft_strdup((*ghost)->tokens->content);
		(*ghost)->tokens = (*ghost)->tokens->next;
		while ((*ghost)->tokens && (*ghost)->status == PARSE) //parse command
		{
			if (check_colon(ghost, command))
			{
				ft_lstadd_back(&(*ghost)->commands, ft_lstnew(command));
				return ;
			}
			if (check_seperator(ghost, command))
				break ;
			if (!check_redir(ghost, command))
				if ((*ghost)->status == 0)
					ft_lstadd_back(&command->args, ft_lstnew(ft_strdup((*ghost)->tokens->content)));
			if (!(*ghost)->tokens)
				break ;
			(*ghost)->tokens = (*ghost)->tokens->next;
		}
		ft_lstadd_back(&(*ghost)->commands, ft_lstnew(command));
		if (!(*ghost)->tokens)
			break ;
		(*ghost)->tokens = (*ghost)->tokens->next;
	}
	(*ghost)->status = FINISHED;
}