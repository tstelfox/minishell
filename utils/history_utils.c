/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   history_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: zenotan <zenotan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/17 19:03:59 by zenotan       #+#    #+#                 */
/*   Updated: 2021/03/20 17:13:46 by zenotan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ghostshell.h"

void	edit_content(t_dlist **node, char *line)
{
	free((*node)->content);
	(*node)->content = NULL;
	(*node)->content = ft_strdup(line);
}

int	delete_characters(t_input *input, char *buf, t_hook *hook)
{
	(void)buf;
	(void)hook;

	return (reins_input_del(input, 30));
}

int	delete_row(t_input *input, char *buf, t_hook *hook)
{
	(void)buf;
	(void)hook;
	size_t	columns;

	columns = input->max_col - (!input->shell_cursor.row * input->prompt_size);

	return (reins_input_del(input, columns));
}

void	store_command(t_shell **ghost, char *line)
{
	if ((*ghost)->first_command)
		ft_dlstadd_front(&(*ghost)->history, ft_dlstnew(ft_strdup(line)));
	else
		edit_content(&(*ghost)->history, line);
	(*ghost)->current = (*ghost)->history;
}

// int	up_function(t_input *line, char *buf, t_hook *hook)
// {
// 	t_shell **ghost = NULL;
// 	t_dlist *node = NULL;
// 	if (hook && hook->function && hook->param)
// 	{
// 		ghost = hook->param;
// 		node = (*ghost)->current;
// 	}
// 	if (node && (*ghost)->first_command)
// 	{
// 		if (!line->line.size)
// 			ft_dlstadd_front(&(*ghost)->history, ft_dlstnew(ft_strdup("")));
// 		else
// 			ft_dlstadd_front(&(*ghost)->history, ft_dlstnew(ft_strdup(line->line.store)));		
// 		(*ghost)->first_command = FALSE;
// 		node = (*ghost)->history;
// 	}
// 	if (!node)
// 		return (RD_IDLE);
// 	if (node->next != NULL)
// 		node = node->next;
// 	delete_row(line, buf, hook);
// 	if (ft_strcmp(node->content, ""))
// 		reins_input_add(line, node->content, ft_strlen(node->content));
// 	edit_content(ghost, line->line.store);
// 	(*ghost)->current = node;
// 	return (RD_IDLE);
// }

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
	// 1 - edit input in current node
	if (line->line.size)
	{
		printf("lineup[%s]\n", line->line.store);
		edit_content(&node, line->line.store);
	}
	else
		edit_content(&node, "");
	// 2 - clear input
	if (!reins_input_clear(line))
		return (1);
	// delete_characters(line, buf, hook);
	// line->line.store = NULL;
	printf("after[%s][%zu]\n", line->line.store, line->line.size);
	// 3 - move to next node
	if (node->next != NULL)
		node = node->next;
	// delete_row(line, buf, hook);
	// 4 - add node content to input
	if (ft_strcmp(node->content, ""))
		reins_input_add(line, node->content, ft_strlen(node->content));
	printf("after_adding[%s][%zu]\n", line->line.store, line->line.size);
	(*ghost)->current = node;
	return (RD_IDLE);
}

int	down_function(t_input *line, char *buf, t_hook *hook)
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
	if (line->line.size)
	{
		printf("linedown[%s]\n", line->line.store);
		edit_content(&node, line->line.store);
	}
	else
		edit_content(&node, "");
	if (!reins_input_clear(line))
		return (1);
	// line->line.store = ;
	// delete_characters(line, buf, hook);
	printf("after[%s][%zu]\n", line->line.store, line->line.size);
	if (node->prev != NULL)
		node = node->prev;
	// delete_row(line, buf, hook);
	if (ft_strcmp(node->content, ""))
		reins_input_add(line, node->content, ft_strlen(node->content));
	printf("after_adding[%s][%zu]\n", line->line.store, line->line.size);
	(*ghost)->current = node;
	return (RD_IDLE);
}

// int	down_function(t_input *line, char *buf, t_hook *hook)
// {
// 	t_shell **ghost = NULL;
// 	t_dlist *node = NULL;
// 	if (hook && hook->function && hook->param)
// 	{
// 		ghost = hook->param;
// 		node = (*ghost)->current;
// 	}
// 	if (!node)
// 		return (RD_IDLE);
// 	if (node->prev != NULL)
// 		node = node->prev;
// 	delete_row(line, buf, hook);
// 	if (ft_strcmp(node->content, ""))
// 		reins_input_add(line, node->content, ft_strlen(node->content));
// 	(*ghost)->current = node;
// 	return (RD_IDLE);
// }
