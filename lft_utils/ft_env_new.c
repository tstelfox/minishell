/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_env_new.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/23 10:37:19 by tmullan       #+#    #+#                 */
/*   Updated: 2021/02/23 10:37:19 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ghostshell.h"

t_env	*ft_envnew(char *name, void *content)
{
	t_env *new_node;

	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->name = name;
	new_node->content = content;
	new_node->next = NULL;
	return (new_node);
}
