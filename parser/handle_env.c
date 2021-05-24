/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_env.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: zenotan <zenotan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/24 15:14:27 by zenotan       #+#    #+#                 */
/*   Updated: 2021/05/24 09:20:57 by ztan          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ghostshell.h"

char	*find_env_val(t_shell **ghost, char *str)
{
	char	**envs;
	int		j;
	int		i;

	j = 0;
	envs = (*ghost)->env;
	if (!ft_strcmp("", str))
		return (ft_strdup(str));
	if (!ft_strcmp("?", str))
		return (ft_itoa((*ghost)->ret_stat));
	while (envs[j])
	{
		i = 0;
		while (envs[j][i] != '=')
			i++;
		if (!envs[j][i + 1])
			return (NULL);
		if (!compare_env(envs[j], str, i))
			return (ft_strdup(envs[j] + i + 1));
		j++;
	}
	return (NULL);
}

int	replace_env(t_shell **ghost, char **input, int i)
{
	char	*temp;
	char	*ret;
	char	*env;
	int		len;
	int		taillen;

	len = get_len(input, i);
	if (len == 0 && (*input)[i] != '\'' && (*input)[i] != '"')
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
	free(*input);
	*input = ret;
	return (len);
}

char	*find_env(t_shell **ghost, char *str)
{
	char	type;
	char	*temp;
	int		check;
	int		i;

	type = 0;
	check = 0;
	i = 0;
	temp = ft_strdup(str);
	while (temp[i])
	{
		if ((temp[i] == '\"' || temp[i] == '\'') && type == 0)
			type = temp[i];
		if (type != 0 && temp[i] == type)
			check++;
		if (!(check % 2))
			type = 0;
		if (temp[i] == '$' && type != '\'')
			i += replace_env(ghost, &temp, i + 1) - 1;
		i++;
	}
	if (check % 2)
		error_handler(ghost, NO_MULTI_LINE, "no multiline", NULL);
	return (temp);
}

void	handle_expnd(t_shell **ghost, t_list **lst, t_list **head)
{
	t_list	*temp;
	char	*tmp;

	temp = NULL;
	tmp = NULL;
	tmp = find_env(ghost, (*lst)->content);
	temp = lexer(ghost, tmp, " ");
	free(tmp);
	ft_lstadd_back(head, ft_lstmap(temp, copy_data, del_content));
	ft_lstclear(&temp, del_content);
	free(temp);
	(*lst) = (*lst)->next;
}

void	expand_env(t_shell **ghost, t_list **lst)
{
	t_list	*head;
	t_list	*og;

	head = NULL;
	if ((*ghost)->error || !lst || !*lst)
		return ;
	og = *lst;
	handle_expnd(ghost, lst, &head);
	while ((*lst))
		handle_expnd(ghost, lst, &head);
	if ((*ghost)->error)
	{
		ft_lstclear(&head, del_content);
		free(head);
		ft_lstclear(&og, del_content);
		free(og);
		return ;
	}
	ft_lstclear(&og, del_content);
	free(og);
	*lst = head;
}
