/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: zenotan <zenotan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/15 19:14:32 by zenotan       #+#    #+#                 */
/*   Updated: 2021/03/04 15:25:47 by zenotan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ghostshell.h"

int		check_meta(char *str)
{
	if (!ft_strcmp(str, ">") || !ft_strcmp(str, "<") || !ft_strcmp(str, "|") ||\
		!ft_strcmp(str, ";"))
		return (1);
	return (0);
}

t_redir	*new_redir(char *file, int type)
{
	t_redir *new_redir;

	if (check_meta(file))
		error_handler("Unexpected token after redirection");
	new_redir = malloc(sizeof(t_redir));
	new_redir->file = ft_strdup(file);
	new_redir->type = type;

	return (new_redir);
}

t_cmd	*new_command()
{
	t_cmd	*new_command;

	new_command = malloc(sizeof(t_cmd));
	new_command->args = NULL;
	new_command->redirection = NULL;
	new_command->type = NULL;
	new_command->seprator_type = 0;

	return (new_command);
}

int		check_seperator(t_cmd *command, t_list *tokens)
{
	if (!ft_strcmp(tokens->content, "|"))
	{
		command->seprator_type = PIPE;
		if (!ft_strcmp(tokens->next->content, "|"))
			error_handler("ghostshell does not support double pipes");
		return (1);
	}
	if (!ft_strcmp(tokens->content, ";"))
	{
		command->seprator_type = SEPERATOR;
		return (1);
	}
	return (0);
}

int		check_redir(t_cmd *command, t_list **tokens)
{
	t_redir *redir;
	t_list *temp;
	
	redir = NULL;
	temp = *tokens;
	if (!ft_strcmp(temp->content, ">"))
	{
		if (!ft_strcmp(temp->next->content, ">")) // check for ">>"
		{
			temp = temp->next;
			redir = new_redir(temp->next->content, OUTPUT_ADD);
		}
		else
			redir = new_redir(temp->next->content, OUTPUT);
		ft_lstadd_back(&command->redirection, ft_lstnew(redir));
		temp = temp->next;
	}
	else if (!ft_strcmp(temp->content, "<"))
	{
		redir = new_redir(temp->next->content, INPUT);
		ft_lstadd_back(&command->redirection, ft_lstnew(redir));
		temp = temp->next;
	}
	else
	{
		*tokens = temp;
		return (0);
	}
	*tokens = temp;
	return (1);
}

t_list	*parser(t_list *tokens)
{
	t_list	*commands = NULL;
	t_cmd	*command = NULL;

	if (!tokens)
		return NULL;
	while (tokens)
	{
		command = new_command();
		command->type = ft_strdup(tokens->content);
		tokens = tokens->next;
		while (tokens) //parse command
		{
			if (check_seperator(command, tokens))
				break ;
			if (!check_redir(command, &tokens))
				ft_lstadd_back(&command->args, ft_lstnew(ft_strdup(tokens->content)));
			if (!tokens)
				break ;
			tokens = tokens->next;
		}
		ft_lstadd_back(&commands, ft_lstnew(command));
		if (!tokens)
			break ;
		tokens = tokens->next;
	}
	return (commands);
}