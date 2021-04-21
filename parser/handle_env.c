/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_env.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: zenotan <zenotan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/24 15:14:27 by zenotan       #+#    #+#                 */
/*   Updated: 2021/04/21 22:24:37 by zenotan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ghostshell.h"

char	**get_envp(char **envp)
{
	char	**env;
	int		i;
	int		k;

	i = 0;
	k = 0;
	while (envp[i])
		i++;
	env = (char **)malloc(sizeof(char *) * (i + 1));
	if (!env)
		return (NULL);
	while (envp[k])
	{
		env[k] = ft_strdup(envp[k]);
		k++;
	}
	env[k] = 0;
	return (env);
}
