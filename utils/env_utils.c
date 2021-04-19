/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ztan <ztan@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/12 12:13:03 by ztan          #+#    #+#                 */
/*   Updated: 2021/04/19 17:33:21 by ztan          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ghostshell.h"

int 	valid_val(char *str)
{
	int i;

	i = 1;
	if (!ft_isalpha(str[0]))
		return (0);
	while (str[i] != '=')
	{
		if (!ft_isalnum(str[i]) || str[i] == '_')
			return (0);
		i++;
	}
	if (str[i + 1])
		return (2);
	return (1);
}

int		valid_word(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) || str[i] == '_')
			return (0);
		i++;
	}
	return (1);
}

int		valid_env(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

char		*find_env_val(t_shell **ghost, char *str)
{
	char	**envs;
	int 	j;
	int		i;

	j = 0;
	envs = (*ghost)->env;
	while (envs[j])
	{
		i = 0;
		while (envs[j][i] != '=')
			i++;
		// printf("str[%s]env[%s]\n", str, envs[j] + i + 1);
		if (!ft_strncmp(envs[j], str, i))
			return (ft_strdup(envs[j] + i + 1));
		j++;
	}
	return (NULL);
}

// void	replace_env(char **input, char *replace, int start)
// {
// 	int i;
// 	int j;
// 	char	*str;

// 	i = 0;
// 	j = 0;
// 	str = *input;
// 	while (str[i])
// 	{
// 		if (i == start)
// 		{
// 			while (replace[j])
// 			{
// 				str[i] = replace[j];
// 				i++;
// 				j++;
// 			}
// 		}
// 	}
// }

int		replace_env_quoted(t_shell **ghost, char **input, int i)
{
	// char 	*str = (*input);
	char	*temp;
	char 	*ret;
	char	*env;
	int		len;
	int		taillen;

	len = 0;
	// printf("[%c]\n", (*input)[i]);
	while (ft_isalnum((*input)[i + len]) || (*input)[i + len] == '_')
		len++;
	temp = ft_substr((*input), i, len);
	// printf("env->[%s][%i]\n", temp, len);
	env = find_env_val(ghost, temp);
	free(temp);
	// printf("ret->[%s]\n", env);
	taillen = ft_strlen((*input)) - len - i;
	// if (env)
	// {
		// printf("str[%s]\n", (*input));
		temp = ft_substr((*input), 0, ft_strlen((*input)) - len - taillen - 1);
		// printf("temp[%s]\n", temp);
		// printf("debug\n");
		len = ft_strlen(env);
		ret = ft_strjoin_free(temp, env);
		// printf("ret[%s]\n", ret);
		// printf("debug2\n");
		// printf("strjoin[%s]\n", ret);
		temp = ft_strdup((*input) + ft_strlen((*input)) - taillen);
		ret = ft_strjoin_free(ret, temp);
		// printf("strjoin2[%s]\n", ret);
		*input = ret;
	// }
	
	// printf("len:[%i]ret[%c]\n", len, ret[i + len]);
	return (len);
}

t_dlist	*split_env(char *str)
{
	t_dlist	*new;
	int 	i;
	int 	start;
	char	*data;

	new = NULL;
	i = 0;
	while (str[i] != '=')
		i++;
	i++;
	start = i;
	data = ft_substr(str, 0, i);
	if (!data)
		return (NULL);
	ft_dlstadd_back(&new,ft_dlstnew(ft_strdup(data)));
	free(data);
	data = NULL;
	while (str[i])
		i++;
	data = ft_substr(str, start, i);
	if (!data)
		return (NULL);
	ft_dlstadd_back(&new,ft_dlstnew(data));
	return (new);
}

void	replace_env()
{
	int		i;
	char	str;

	i = 0;
	str = (*ghost)->tokens->content;
	while (ft_isalnum(str[i + len]) || str[i + len] == '_')
		len++;
	temp = ft_substr(str, i, len);
	// printf("env->[%s][%i]\n", temp, len);
	env = find_env_val(ghost, temp);
}

void	check_env(t_shell **ghost)
{
	int		i;
	char	str;

	i = 0;
	str = (*ghost)->tokens->content;
	while (str[i] != '$')
		i++;
	if (str[i] == '$')
		replace_env()
}