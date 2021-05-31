/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   history_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: zenotan <zenotan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/17 19:03:59 by zenotan       #+#    #+#                 */
/*   Updated: 2021/05/31 15:26:08 by zenotan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ghostshell.h"

void	pass_param(void *param)
{
	(void)param;
}

void	edit_content(t_dlist **node, char *line, int size)
{
	char	*temp;

	free((*node)->content);
	(*node)->content = NULL;
	(*node)->content = malloc(sizeof(char) * (size + 1));
	temp = (*node)->content;
	ft_memcpy(temp, line, size);
	temp[size] = '\0';
}

int	delete_row(t_input *input, char *buf, t_hook *hook)
{
	size_t	columns;

	(void)buf;
	(void)hook;
	columns = input->max_col - (!input->shell_cursor.row * input->prompt_size);
	return (reins_input_del(input, columns));
}

void	store_command(t_shell **ghost, char *line)
{
	if ((*ghost)->first_command)
		ft_dlstadd_front(&(*ghost)->history, ft_dlstnew(ft_strdup(line)));
	else
		edit_content(&(*ghost)->history, line, ft_strlen(line));
	(*ghost)->current = (*ghost)->history;
}

void	init_reins(t_shell **ghost)
{
	if (!(*ghost))
		error_handler(ghost, INIT_ERROR, "failed to initialize structs", NULL);
	if (!reins_key((*ghost)->reins, KEY_ESC "[" KEY_UP, up_function))
		error_handler(ghost, INIT_ERROR, "failed to bind key", NULL);
	if (!reins_hook((*ghost)->reins, KEY_ESC "[" KEY_UP, &pass_param, ghost))
		error_handler(ghost, INIT_ERROR, "failed to bind key", NULL);
	if (!reins_key((*ghost)->reins, KEY_ESC "[" KEY_DOWN, down_function))
		error_handler(ghost, INIT_ERROR, "failed to bind key", NULL);
	if (!reins_hook((*ghost)->reins, KEY_ESC "[" KEY_DOWN, &pass_param, ghost))
		error_handler(ghost, INIT_ERROR, "failed to bind key", NULL);
	if (!reins_key((*ghost)->reins, KEY_CNTRL_C, ctrl_c_function))
		error_handler(ghost, INIT_ERROR, "failed to bind key", NULL);
	if (!reins_hook((*ghost)->reins, KEY_CNTRL_C, &pass_param, ghost))
		error_handler(ghost, INIT_ERROR, "failed to bind key", NULL);
}
