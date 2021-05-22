/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/20 17:23:40 by tmullan       #+#    #+#                 */
/*   Updated: 2021/05/22 12:38:11 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ghostshell.h"

int	resize_arr(t_shell **ghost, char **temp, int k)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while ((*ghost)->env[i])
	{
		if (i != k)
		{
			temp[j] = (*ghost)->env[i];
			j++;
		}
		else
			free((*ghost)->env[i]);
		i++;
	}
	return (j);
}

void	unset_arg(t_list *arg, t_shell **ghost, int i, int k)
{
	int		len;
	char	**temp;

	len = ft_strlen(arg->content);
	while ((*ghost)->env[i])
	{
		if (ft_strnstr((*ghost)->env[i], arg->content, len))
			k = i;
		i++;
	}
	temp = (char **)malloc(sizeof(char *) * (i));
	i = resize_arr(ghost, temp, k);
	temp[i] = 0;
	free((*ghost)->env);
	(*ghost)->env = temp;
}

int	run_unset(t_cmd *cmd, t_shell **ghost)
{
	int		i;
	int		k;
	t_list	*head;

	k = 0;
	i = 0;
	if (!cmd->args)
		return (1);
	head = cmd->args;
	while (cmd->args->next)
	{
		unset_arg(cmd->args, ghost, i, k);
		cmd->args = cmd->args->next;
	}
	unset_arg(cmd->args, ghost, i, k);
	cmd->args = head;
	return (1);
}
