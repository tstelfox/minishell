/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_env.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: zenotan <zenotan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/24 15:14:27 by zenotan       #+#    #+#                 */
/*   Updated: 2021/04/27 17:31:12 by ztan          ########   odam.nl         */
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

char		*find_env_val(t_shell **ghost, char *str)
{
	char	**envs;
	int 	j;
	int		i;

	j = 0;
	envs = (*ghost)->env;
	if (!ft_strcmp("?", str))
		return (ft_strdup(ft_itoa((*ghost)->ret_stat)));
	while (envs[j])
	{
		i = 0;
		while (envs[j][i] != '=')
			i++;
		if (!ft_strncmp(envs[j], str, ft_strlen(str)))
			return (ft_strdup(envs[j] + i + 1));	
		j++;
	}
	return (NULL);
}

int		replace_env(t_shell **ghost, char **input, int i)
{
	char	*temp;
	char 	*ret;
	char	*env;
	int		len;
	int		taillen;

	len = 0;
	while (ft_isalnum((*input)[i + len]) || (*input)[i + len] == '_')
		len++;
	if ( (*input)[i + len] == '?' && (!ft_isalnum((*input)[i + len + 1]) \
											|| (*input)[i + len + 1] != '_'))
		len++;
	if (len == 0)
		return (1);
	temp = ft_substr((*input), i, len);
	env = find_env_val(ghost, temp);
	free(temp);
	taillen = ft_strlen((*input)) - len - i;
	temp = ft_substr((*input), 0, ft_strlen((*input)) - len - taillen - 1);
	len = ft_strlen(env);
	ret = ft_strjoin_free(temp, env);
	temp = ft_strdup((*input) + ft_strlen((*input)) - taillen);
	ret = ft_strjoin_free(ret, temp);
	*input = ret;
	return (len);
}

char	*find_env(t_shell **ghost, char *str)
{
	char	type;
	int		check;
	int		i;

	type = 0;
	check = 0;
	i = 0;
	while (str[i])
	{
		if ((str[i] == '\"' || str[i] == '\'') && type == 0)
			type = str[i];
		if (type != 0 && str[i] == type)
			check++;
		if (!(check % 2))
			type = 0;
		if (str[i] == '$' && type != '\'')
			i += replace_env(ghost, &str, i + 1) - 1;
		i++;
	}
	if (check % 2)
		error_handler(ghost, NO_MULTI_LINE, "no multiline", NULL);
	return (str);
}

void	expand_env(t_shell **ghost, t_list **lst)
{
	t_list *head = NULL;
	t_list *temp = NULL;
	
	temp = lexer(ghost, find_env(ghost, (*lst)->content), " ");
	ft_lstadd_back(&head, ft_lstmap(temp, copy_data, del_content));
	free(temp);
	(*lst) = (*lst)->next;
	while ((*lst) && (*ghost)->status == PARSE)
	{
		temp = lexer(ghost, find_env(ghost, (*lst)->content), " ");
		ft_lstadd_back(&head, ft_lstmap(temp, copy_data, del_content));
		free(temp);
		(*lst) = (*lst)->next;
	}
	if ((*ghost)->error)
	{
		ft_lstclear(&head, del_content);
		return ;
	}
	ft_lstclear(lst, del_content);
	*lst = head;
}