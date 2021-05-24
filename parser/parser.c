/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: zenotan <zenotan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/15 19:14:32 by zenotan       #+#    #+#                 */
/*   Updated: 2021/05/24 16:23:25 by ztan          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ghostshell.h"

t_list	*parse_command(t_shell **ghost, t_cmd **cmd)
{
	t_list	*new_lst;

	new_lst = NULL;
	if (!handle_redir(ghost, cmd) && !(*ghost)->error)
		ft_lstadd_back(&new_lst, \
		ft_lstnew(ft_strdup((*ghost)->tokens->content)));
	if ((*ghost)->tokens)
		(*ghost)->tokens = (*ghost)->tokens->next;
	while ((*ghost)->tokens)
	{
		if (handle_seperator(ghost, cmd) && !(*ghost)->error)
			break ;
		if (!handle_redir(ghost, cmd) && !(*ghost)->error)
			ft_lstadd_back(&new_lst, \
			ft_lstnew(ft_strdup((*ghost)->tokens->content)));
		if (!(*ghost)->tokens)
			break ;
		(*ghost)->tokens = (*ghost)->tokens->next;
	}
	expand_env(ghost, &new_lst);
	remove_quotes(ghost, &new_lst);
	return (new_lst);
}

int	parser_add_command(t_cmd **command, t_list **new_lst, t_list **lst)
{
	if ((!*new_lst && !(*command)->redirection))
	{
		del_commands(*command);
		return (1);
	}
	if (new_lst)
	{
		if ((*new_lst))
			(*command)->type = ft_strdup((*new_lst)->content);
		if ((*new_lst))
			if ((*new_lst)->next)
				(*command)->args = ft_lstmap((*new_lst)->next, \
										copy_data, del_content);
		ft_lstclear(new_lst, del_content);
	}
	ft_lstadd_back(lst, ft_lstnew(*command));
	new_lst = NULL;
	return (0);
}

int	parser_next_token(t_shell **ghost, t_cmd *command)
{
	if ((*ghost)->tokens)
	{
		(*ghost)->tokens = (*ghost)->tokens->next;
		if ((*ghost)->tokens->content && command->seprator_type != PIPE)
			return (1);
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
	while ((*ghost)->tokens)
	{
		command = new_command();
		if (!command)
			return (error_handler(ghost, INTERNAL_ERROR, \
						"Failed to init command", NULL));
		new_lst = parse_command(ghost, &command);
		if (parser_add_command(&command, &new_lst, &lst))
			return (NULL);
		if (parser_next_token(ghost, command))
			break ;
	}
	return (lst);
}
