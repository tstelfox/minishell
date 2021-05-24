/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ztan <ztan@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/17 09:36:07 by ztan          #+#    #+#                 */
/*   Updated: 2021/05/24 09:23:14 by ztan          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ghostshell.h"

int	compare_env(char *env, char *str, int len)
{
	if (len != (int)ft_strlen(str))
		return (1);
	while (len != 0 && (*env != '\0' || *env != '\0'))
	{
		if (*env == *str)
		{
			env++;
			str++;
		}
		else
			return ((unsigned char)*env - (unsigned char)*str);
		len--;
	}
	return (0);
}

int	get_len(char **input, int i)
{
	int	len;

	len = 0;
	while (ft_isalnum((*input)[i + len]) || (*input)[i + len] == '_')
		len++;
	if ((*input)[i + len] == '?' && (!ft_isalnum((*input)[i + len + 1]) \
											 || (*input)[i + len + 1] != '_'))
		len++;
	return (len);
}

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
