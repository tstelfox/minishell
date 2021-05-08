/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: zenotan <zenotan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/15 19:14:32 by zenotan       #+#    #+#                 */
/*   Updated: 2021/05/08 21:49:58 by zenotan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ghostshell.h"

int		check_syntax(t_shell **ghost, t_list *lst)
{
	t_list *temp;

	temp = lst;
	while (temp)
	{
		if (temp->next)
		{
			if (!ft_strcmp(temp->content, "|"))
				if (!ft_strcmp(temp->next->content, ";"))
					error_handler(ghost, SYNTAX_ERROR, \
					"syntax error near unexpected token", temp->next->content);
			if (!ft_strcmp(temp->content, ";"))
			{
				if (!ft_strcmp(temp->next->content, "|"))
					error_handler(ghost, SYNTAX_ERROR, \
					"syntax error near unexpected token", temp->next->content);
				if (!ft_strcmp(temp->next->content, ";"))
					error_handler(ghost, SYNTAX_ERROR, \
					"syntax error near unexpected token", temp->next->content);
			}
				
		}
		if ((*ghost)->error == SYNTAX_ERROR)
			return (1);
		temp = temp->next;
	}
	return (0);
}

t_list	*parser(t_shell **ghost)
{
	t_cmd	*command;
	t_list	*new_lst;
	t_list	*lst;

	new_lst = NULL;
	lst = NULL;
	if ((*ghost)->commands)
		free_list(&((*ghost)->commands), del_commands);
	if (check_syntax(ghost, (*ghost)->tokens))
		return (NULL);
	// printf("\nyah\n");
	while ((*ghost)->tokens)
	{
		command = new_command(); // NULL
		if (!handle_redir(ghost, &command) && !(*ghost)->error)
			ft_lstadd_back(&new_lst, ft_lstnew(ft_strdup((*ghost)->tokens->content)));
		(*ghost)->tokens = (*ghost)->tokens->next;
		while ((*ghost)->tokens) //parse command
		{
			if (handle_seperator(ghost, &command) && !(*ghost)->error)
				break ;
			if (!handle_redir(ghost, &command) && !(*ghost)->error)
				ft_lstadd_back(&new_lst, ft_lstnew(ft_strdup((*ghost)->tokens->content)));
			if (!(*ghost)->tokens)
				break ;
			(*ghost)->tokens = (*ghost)->tokens->next;
		}
		expand_env(ghost, &new_lst);
		if ((!new_lst && !command->redirection))
		{
			del_commands(command);
			if (new_lst)
			{
				ft_lstclear(&new_lst, del_content);
				free(new_lst);
			}
			return (NULL);
		}
		remove_quotes(ghost, &new_lst);
		if (new_lst)
		{
			command->type = ft_strdup(new_lst->content);
			if (new_lst->next)
				command->args = ft_lstmap(new_lst->next, copy_data, del_content);
			ft_lstclear(&new_lst, del_content);
		}
		ft_lstadd_back(&lst, ft_lstnew(command));
		new_lst = NULL;
		if (!(*ghost)->tokens)
			break ;
		(*ghost)->tokens = (*ghost)->tokens->next;
	}
	return (lst);
}