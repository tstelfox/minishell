/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   printlists.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: zenotan <zenotan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/02 13:56:38 by zenotan       #+#    #+#                 */
/*   Updated: 2021/03/26 12:53:33 by zenotan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ghostshell.h"

void	print_data(void *data)
{
	char *str = data;
	ft_putstr_fd("[", STDOUT_FILENO);
	ft_putstr_fd(str, STDOUT_FILENO);
	ft_putstr_fd("]", STDOUT_FILENO);
}

void	print_redir(t_redir *data)
{
	ft_putstr_fd("[", STDOUT_FILENO);
	ft_putstr_fd(data->file, STDOUT_FILENO);
	ft_putstr_fd(", ", STDOUT_FILENO);
	ft_putnbr_fd(data->type, STDOUT_FILENO);
	ft_putstr_fd("]", STDOUT_FILENO);
}

void	ft_redir_lstiter(t_list *lst, void (*f)(t_redir *))
{
	t_list *temp;

	if (!lst)
		return ;
	temp = lst;
	while (temp)
	{
		f(temp->content);
		temp = temp->next;
	}
}

void	print_cmd(t_cmd *data)
{
	ft_putstr_fd("name:", STDOUT_FILENO);
	ft_putstr_fd(data->type, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	if (data->args)
	{
		ft_putstr_fd("arguments:", STDOUT_FILENO);
		ft_lstiter(data->args, print_data);
		ft_putstr_fd("\n", STDOUT_FILENO);
	}
	if (data->redirection)
	{
		ft_putstr_fd("redirections:", STDOUT_FILENO);
		ft_redir_lstiter(data->redirection, print_redir);
		ft_putstr_fd("\n", STDOUT_FILENO);
	}
	ft_putstr_fd("pipe or sep or nothing:", STDOUT_FILENO);
	ft_putnbr_fd(data->seprator_type, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
}

void	ft_cmd_lstiter(t_list *lst, void (*f)(t_cmd *))
{
	t_list *temp;

	if (!lst)
		return ;
	temp = lst;
	while (temp)
	{
		f(temp->content);
		temp = temp->next;
	}
}

void	debug_loop(t_shell **ghost)
{
	if ((*ghost)->status > 0)// debug
	{
		ft_lstiter((*ghost)->tokens, print_data);
		// ft_putstr_fd("\n", STDOUT_FILENO);
		ft_cmd_lstiter((*ghost)->commands, print_cmd);
	}
	else//if error debug
	{
		ft_putnbr_fd((*ghost)->status, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
	}
	ft_putstr_fd("----DEBUG----\n", STDOUT_FILENO);
}