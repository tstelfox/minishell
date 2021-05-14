/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_input.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: zenotan <zenotan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/16 13:26:40 by zenotan       #+#    #+#                 */
/*   Updated: 2021/05/13 11:58:53 by zenotan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ghostshell.h"

// void	assign_parameters(t_shell **node)

// int		up_function(t_input *line, char *buf, t_hook *hook)
// {
// 	t_shell **ghost;
// 	t_dlist *node;

// 	ghost = hook->param;
// 	node = (*ghost)->current;
// 	(void)buf;
// 	if (!node || !node->next)
// 		return (RD_IDLE);
// 	if ((*ghost)->first_command)
// 	{
// 		ft_dlstadd_front(&(*ghost)->history, ft_dlstnew(ft_strdup("")));
// 		(*ghost)->first_command = FALSE;
// 		node = node->prev;
// 	}
// 	if (line->line.size)
// 		edit_content(&node, line->line.store, line->line.size);
// 	else
// 		edit_content(&node, "", 1);
// 	if (!reins_input_clear(line))
// 		return (1);
// 	node = node->next;
// 	if (ft_strcmp(node->content, ""))
// 		reins_input_add(line, node->content, ft_strlen(node->content));
// 	(*ghost)->current = node;
// 	return (RD_IDLE);
// }

// int		down_function(t_input *line, char *buf, t_hook *hook)
// {
// 	t_shell **ghost;
// 	t_dlist *node;

// 	ghost = hook->param;
// 	node = (*ghost)->current;
// 	(void)buf;
// 	if (!node || !node->prev)
// 		return (RD_IDLE);
// 	if (line->line.size)
// 		edit_content(&node, line->line.store, line->line.size);
// 	else
// 		edit_content(&node, "", 1);
// 	if (!reins_input_clear(line))
// 		return (1);
// 	node = node->prev;
// 	if (ft_strcmp(node->content, ""))
// 		reins_input_add(line, node->content, ft_strlen(node->content));
// 	(*ghost)->current = node;
// 	return (RD_IDLE);
// }

// int		ctrl_d_function(t_input *line, char *buf, t_hook *hook)
// {
// 	t_shell **ghost;
// 	t_dlist *node;

// 	ghost = hook->param;
// 	node = (*ghost)->current;
// 	(void)buf;
// 	// printf("YAHHH\n");
// 	if (!reins_input_clear(line))
// 		return (1);
// 	return (RD_SEND);
// }

char	*read_line(t_shell **ghost)
{
	int		ret;
	char	*input;
	// char *input = NULL;

	// ret = reins_print_keycodes((*ghost)->reins);
	// ret = reins_get_input((*ghost)->reins, &input);
	ret = get_next_line(STDIN_FILENO, &input);
	// printf("\ninput[%s]\n", input);
	if (ret == 0)
	{
		// ft_putstr_fd("exit\n", 1);
		exit(0);
	}
	if (ret < 0)
	{
		free(input);
		error_handler(ghost, INTERNAL_ERROR, "failed to get input", NULL);
	}
	// if (ft_strcmp(input, ""))
	// 	store_command(ghost, input);
	// reins_disable((*ghost)->reins);
	// ft_putchar_fd('\n', STDOUT_FILENO);
	return (input);
}