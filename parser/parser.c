/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: zenotan <zenotan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/15 19:14:32 by zenotan       #+#    #+#                 */
/*   Updated: 2021/04/29 18:57:20 by ztan          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ghostshell.h"

void	parser(t_shell **ghost)
{
	t_cmd	*command;
	t_list	*new_lst = NULL;

	if ((*ghost)->commands)
		ft_lstclear(&(*ghost)->commands, del_commands);
	while ((*ghost)->tokens)
	{
		command = new_command(); // NULL
		ft_lstadd_back(&new_lst, ft_lstnew(ft_strdup((*ghost)->tokens->content)));
		(*ghost)->tokens = (*ghost)->tokens->next;
		while ((*ghost)->tokens && ft_strcmp((*ghost)->tokens->content, ";")) //parse command
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
		if (!new_lst)
			return ;
		remove_quotes(ghost, &new_lst);
		command->type = ft_strdup(new_lst->content);
		command->args = ft_lstmap(new_lst->next, copy_data, del_content);
		ft_lstclear(&new_lst, del_content);
		ft_lstadd_back(&(*ghost)->commands, ft_lstnew(command));
		if (!(*ghost)->tokens)
			break ;
		if (!ft_strcmp((*ghost)->tokens->content, ";"))
		{
			(*ghost)->tokens = (*ghost)->tokens->next;
			break ;
		}
		(*ghost)->tokens = (*ghost)->tokens->next;
	}
}