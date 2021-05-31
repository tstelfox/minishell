/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_input.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: zenotan <zenotan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/16 13:26:40 by zenotan       #+#    #+#                 */
/*   Updated: 2021/05/31 15:27:47 by zenotan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ghostshell.h"

int	up_function(t_input *line, char *buf, t_hook *hook)
{
	t_shell	**ghost;

	ghost = hook->param;
	(void)buf;
	if (!(*ghost)->current)
		return (RD_IDLE);
	if ((*ghost)->first_command)
	{
		ft_dlstadd_front(&(*ghost)->history, ft_dlstnew(ft_strdup("")));
		(*ghost)->first_command = FALSE;
		(*ghost)->current = (*ghost)->current->prev;
	}
	if (line->line.size)
		edit_content(&(*ghost)->current, line->line.store, line->line.size);
	else
		edit_content(&(*ghost)->current, "", 1);
	if (!reins_input_clear(line))
		return (1);
	if ((*ghost)->current->next)
		(*ghost)->current = (*ghost)->current->next;
	if (ft_strcmp((*ghost)->current->content, ""))
		reins_input_add(line, (*ghost)->current->content,
			 ft_strlen((*ghost)->current->content));
	return (RD_IDLE);
}

int	down_function(t_input *line, char *buf, t_hook *hook)
{
	t_shell	**ghost;
	t_dlist	*node;

	ghost = hook->param;
	node = (*ghost)->current;
	(void)buf;
	if (!node || !node->prev)
		return (RD_IDLE);
	if (line->line.size)
		edit_content(&node, line->line.store, line->line.size);
	else
		edit_content(&node, "", 1);
	if (!reins_input_clear(line))
		return (1);
	node = node->prev;
	if (ft_strcmp(node->content, ""))
		reins_input_add(line, node->content, ft_strlen(node->content));
	(*ghost)->current = node;
	return (RD_IDLE);
}

int	ctrl_c_function(t_input *line, char *buf, t_hook *hook)
{
	t_shell	**ghost;
	t_dlist	*node;

	ghost = hook->param;
	node = (*ghost)->current;
	(void)buf;
	if (!reins_input_clear(line))
		return (1);
	return (RD_SEND);
}

char	*read_line(t_shell **ghost)
{
	int		ret;
	char	*input;

	input = NULL;
	ret = reins_get_input((*ghost)->reins, &input);
	if (ret == 0)
	{
		ft_putstr_fd("exit\n", STDERR_FILENO);
		reins_disable((*ghost)->reins);
		del_ghost(ghost);
		exit(0);
	}
	if (ret < 0)
	{
		free(input);
		error_handler(ghost, INTERNAL_ERROR, "failed to get input", NULL);
	}
	if (ft_strcmp(input, ""))
		store_command(ghost, input);
	reins_disable((*ghost)->reins);
	ft_putchar_fd('\n', STDOUT_FILENO);
	return (input);
}
