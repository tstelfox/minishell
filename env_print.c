/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_print.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/23 12:27:56 by tmullan       #+#    #+#                 */
/*   Updated: 2021/02/23 12:27:56 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ghostshell.h"

void	print_env(void *env_list)
{
	t_env *env = (t_env*)env_list;
	ft_putstr_fd(env->name, STDOUT_FILENO);
	ft_putstr_fd("=", STDOUT_FILENO);
	ft_putstr_fd(env->content, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
}
