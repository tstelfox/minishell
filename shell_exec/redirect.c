/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/11 12:45:04 by tmullan       #+#    #+#                 */
/*   Updated: 2021/05/25 18:09:20 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ghostshell.h"

int	open_fd(t_cmd *cmd, t_shell **ghost, t_redir *redir)
{
	if (redir->type == INPUT)
	{
		(*ghost)->error = NO_FILE;
		if ((*ghost)->red_in > 0)
		{
			ft_putstr_fd("Closed the old input red\n", 1);
			close((*ghost)->red_in);
		}
		(*ghost)->red_in = open(redir->file, O_APPEND | O_RDWR, 0666);
		if ((*ghost)->red_in == -1)
		{
			cmd_notfound(cmd, NO_FILE, ghost, 0);
			return (-1);
		}
	}
	else
	{
		// ft_putnbr_fd(redir->type, 1);
		// ft_putstr_fd("How many times?\n", 1);
		if ((*ghost)->red_out > 0)
		{
			ft_putstr_fd("Closed the old output red\n", 1);
			close((*ghost)->red_out);
		}
		if (redir->type == OUTPUT)
			(*ghost)->red_out = open(redir->file, O_CREAT | O_TRUNC | O_RDWR, 0666);
		else
			(*ghost)->red_out = open(redir->file, O_CREAT | O_APPEND | O_RDWR, 0666);
	}
	return (0);
}


int	redirect(t_cmd *cmd, t_shell **ghost)
{
	t_redir	*redir;
	t_list	*head;

	head = cmd->redirection;
	redir = (t_redir *)cmd->redirection->content;
	while (cmd->redirection->next)
	{
		if (open_fd(cmd, ghost, redir) == -1)
		{
			cmd->redirection = head;
			return (-1);
		}
		cmd->redirection = cmd->redirection->next;
		redir = cmd->redirection->content;
	}
	if (open_fd(cmd, ghost, redir) == -1)
	{
		cmd->redirection = head;
		return (-1);
	}
	cmd->redirection = head;
	ft_putnbr_fd((*ghost)->red_out, 1);
	ft_putchar_fd('\n', 1);
	ft_putnbr_fd((*ghost)->red_in, 1);
	if ((*ghost)->red_in > 0)
	{
		(*ghost)->in = dup(STDIN_FILENO);
		dup2((*ghost)->red_in, STDIN_FILENO);
		close((*ghost)->red_in);
	}
	if ((*ghost)->red_out > 0)
	{
		(*ghost)->out = dup(STDOUT_FILENO);
		dup2((*ghost)->red_out, STDOUT_FILENO);
		close((*ghost)->red_out);
	}
	return (0);
}

// int	final_redir(t_cmd *cmd, t_shell **ghost, t_redir *redir)
// {
// 	int	fd;

// 	if (redir->type == INPUT)
// 	{
// 		(*ghost)->error = NO_FILE;
// 		fd = open(redir->file, O_APPEND | O_RDWR, 0666);
// 		if (fd == -1)
// 		{
// 			cmd_notfound(cmd, NO_FILE, ghost, 0);
// 			return (-1);
// 		}
// 		// if (last_op && last_op->type != INPUT)
// 		// {
// 		// 	close(fd);
// 		// 	if (last_op->type == OUTPUT)
// 		// 		fd = open(last_op->file, O_CREAT | O_TRUNC | O_RDWR, 0666);
// 		// 	else
// 		// 		fd = open(last_op->file, O_CREAT | O_APPEND | O_RDWR, 0666);
// 		// 	(*ghost)->out = dup(STDOUT_FILENO);
// 		// 	dup2(fd, STDOUT_FILENO);
// 		// }
// 		// else
// 		// {
// 		(*ghost)->in = dup(STDIN_FILENO);
// 		dup2(fd, STDIN_FILENO);
// 		// }
// 	}
// 	else
// 	{
// 		if (redir->type == OUTPUT)
// 			fd = open(redir->file, O_CREAT | O_TRUNC | O_RDWR, 0666);
// 		else
// 			fd = open(redir->file, O_CREAT | O_APPEND | O_RDWR, 0666);
// 		(*ghost)->out = dup(STDOUT_FILENO);
// 		dup2(fd, STDOUT_FILENO);
// 	}
// 	close(fd);
// 	return (0);
// }