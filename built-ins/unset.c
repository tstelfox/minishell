/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/20 17:23:40 by tmullan       #+#    #+#                 */
/*   Updated: 2021/05/20 18:22:15 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ghostshell.h"

void	unset_arg(t_cmd *cmd, t_shell **ghost, int i, int k)
{
	int len;
	int	j;
	char **temp;

	len = ft_strlen(cmd->args->content);
	while ((*ghost)->env[i])
	{
		if (ft_strnstr((*ghost)->env[i], cmd->args->content, len))
			k = i;
		i++;
	}
	ft_putnbr_fd(i, 1);
	ft_putstr_fd("\n", 1);
	temp = (char**)malloc(sizeof(char*) * (i));
	j = 0;
	for (int i = 0; (*ghost)->env[i]; i++)
	{
		if (i != k)
		{
			temp[j] = (*ghost)->env[i];
			j++;
		}
		else
			free((*ghost)->env[i]);
	}
	temp[j] = 0;
	free((*ghost)->env);
	(*ghost)->env = temp;
	i = 0;
	while ((*ghost)->env[i])
	{
		i++;
	}
	ft_putstr_fd("And then\n", 1);
	ft_putnbr_fd(i, 1);
	ft_putstr_fd("\n", 1);
}

int	run_unset(t_cmd *cmd, t_shell **ghost)
{
	int i;
	int k;
	
	k = 0;
	i = 0;
	if (!cmd->args)
		return (1);
	while (cmd->args->next)
	{
		unset_arg(cmd, ghost, i, k);
		cmd->args = cmd->args->next;
	}
	unset_arg(cmd, ghost, i, k);
	// int len = ft_strlen(cmd->args->content);
	// while ((*ghost)->env[i])
	// {
	// 	if (ft_strnstr((*ghost)->env[i], cmd->args->content, len))
	// 		k = i;
	// 	i++;
	// }
	// // char **temp;
	// temp = (char**)malloc(sizeof(char*) * (i));
	// int j = 0;
	// for (int i = 0; (*ghost)->env[i]; i++)
	// {
	// 	if (i != k)
	// 	{
	// 		temp[j] = (*ghost)->env[i];
	// 		j++;
	// 	}
	// 	else
	// 		free((*ghost)->env[i]);
	// }
	// temp[j] = 0;
	// free((*ghost)->env);
	// (*ghost)->env = temp;
	return(1);
}
