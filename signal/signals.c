/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/22 13:07:02 by tmullan       #+#    #+#                 */
/*   Updated: 2021/05/24 18:04:05 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ghostshell.h"

void	ctrl(int sig)
{
	if (sig == SIGINT)
		ft_putstr_fd("\n\e[1;34mghostshell$> \e[0m", STDERR_FILENO);
}

void	ctrl_process(int sig)
{
	if (sig == SIGINT)
		ft_putstr_fd("\n", 1);
	if (sig == SIGQUIT)
		ft_putstr_fd("Quit: 3\n", 1);
}
