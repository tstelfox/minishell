/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/20 16:39:19 by tmullan       #+#    #+#                 */
/*   Updated: 2021/05/20 17:11:47 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ghostshell.h"

int	export_replace(char *str, t_shell **ghost, int i)
{
	char	*var;

	while (str[i])
	{
		if (str[i] == '=')
			break ;
		i++;
	}
	var = (char *)malloc(sizeof(char) * (i + 1)); // Protect the mallocs
	ft_strlcpy(var, str, i + 1);
	i = 0;
	while ((*ghost)->env[i])
	{
		if (ft_strnstr((*ghost)->env[i], var, ft_strlen(var)))
		{
			the_replacing(str, var, ghost, i);
			return (0);
		}
		i++;
	}
	free(var);
	return (1);
}

void	print_quotes(t_shell **ghost, int i, int k)
{
	ft_putstr_fd("=\"", 1);
	k++;
	while ((*ghost)->env[i][k])
	{
		ft_putchar_fd((*ghost)->env[i][k], 1);
		k++;
	}
	ft_putstr_fd("\"\n", 1);
}

void	print_export(t_shell **ghost, int i, int k)
{
	while ((*ghost)->env[i])
	{
		ft_putstr_fd("declare -x ", 1);
		if (ft_strchr((*ghost)->env[i], '='))
		{
			while ((*ghost)->env[i][k] != '"')
			{
				ft_putchar_fd((*ghost)->env[i][k], 1);
				k++;
				if ((*ghost)->env[i][k] == '=')
				{
					print_quotes(ghost, i, k);
					k = 0;
					i++;
					break ;
				}
			}
		}
		else
		{
			ft_putstr_fd((*ghost)->env[i], 1);
			ft_putchar_fd('\n', 1);
			i++;
		}
	}
}

int	parse_export(t_cmd *cmd, t_shell **ghost, char *str)
{
	int	i;

	i = 0;
	if (str[0] == '=')
	{
		cmd_notfound(cmd, EXPRT_FAIL, ghost, 0);
		return (1);
	}
	while (str[i])
	{
		if (str[i] == '=')
			break ;
		if ((!ft_isalpha(str[i]) && (str[i] != '_' && str[i] != '$'
					&& str[i] != '=' && str[i] != '/' && str[i] != '"'
					&& str[i] != ' ')) || str[0] == '=')
		{
			cmd_notfound(cmd, EXPRT_FAIL, ghost, 0);
			return (1);
		}
		i++;
	}
	if (export_replace(str, ghost, 0))
		(*ghost)->env = arr_addback((*ghost)->env, cmd->args->content);
	return (0);
}

int	run_export(t_cmd *cmd, t_shell **ghost)
{
	int		i;
	int		k;
	char	*str;

	i = 0;
	k = 0;
	if (!cmd->args)
	{
		print_export(ghost, i, k);
		return (1);
	}
	while (cmd->args->next)
	{
		str = cmd->args->content;
		if (parse_export(cmd, ghost, str) == 1)
			return (1);
		cmd->args = cmd->args->next;
	}
	str = cmd->args->content;
	if (parse_export(cmd, ghost, str) == 1)
		return (1);
	return (1);
}
