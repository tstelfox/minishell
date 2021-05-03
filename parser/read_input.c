/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_input.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: zenotan <zenotan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/16 13:26:40 by zenotan       #+#    #+#                 */
/*   Updated: 2021/05/03 12:08:37 by ztan          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ghostshell.h"

int	up_function(t_input *line, char *buf, t_hook *hook)
{
	t_shell **ghost = NULL;
	t_dlist *node = NULL;
	(void)buf;
	if (hook && hook->function && hook->param)
	{
		ghost = hook->param;
		node = (*ghost)->current;
	}
	if (!node)
		return (RD_IDLE);
	if ((*ghost)->first_command)
	{
		ft_dlstadd_front(&(*ghost)->history, ft_dlstnew(ft_strdup("")));
		(*ghost)->first_command = FALSE;
		node = node->prev;
	}
	if (line->line.size)
		edit_content(&node, line->line.store, line->line.size);
	else
		edit_content(&node, "", 1);
	if (!reins_input_clear(line))
		return (1);
	if (node->next != NULL)
		node = node->next;
	if (ft_strcmp(node->content, ""))
		reins_input_add(line, node->content, ft_strlen(node->content));
	(*ghost)->current = node;
	return (RD_IDLE);
}

int	down_function(t_input *line, char *buf, t_hook *hook)
{
	// printf("\nDOWN\n");
	t_shell **ghost = NULL;
	t_dlist *node = NULL;
	(void)buf;
	if (hook && hook->function && hook->param)
	{
		ghost = hook->param;
		node = (*ghost)->current;
	}
	if (!node)
		return (RD_IDLE);
	if (line->line.size)
		edit_content(&node, line->line.store, line->line.size);
	else
		edit_content(&node, "", 1);
	if (!reins_input_clear(line))
		return (1);
	if (node->prev != NULL)
		node = node->prev;
	if (ft_strcmp(node->content, ""))
		reins_input_add(line, node->content, ft_strlen(node->content));
	(*ghost)->current = node;
	return (RD_IDLE);
}

char	*read_line(t_shell **ghost)
{
	int		ret;
	char	*input;

	ret = reins_get_input((*ghost)->reins, &input);
	if (ret != 1)
	{
		free(input);
		error_handler(ghost, INTERNAL_ERROR, "failed to get input", NULL);
	}
	store_command(ghost, input);
	reins_disable((*ghost)->reins);
	ft_putchar_fd('\n', STDOUT_FILENO);
	return (input);
}