/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ztan <ztan@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/12 12:13:03 by ztan          #+#    #+#                 */
/*   Updated: 2021/04/25 22:59:48 by zenotan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ghostshell.h"

// int 	valid_val(char *str)
// {
// 	int i;

// 	i = 1;
// 	if (!ft_isalpha(str[0]))
// 		return (0);
// 	while (str[i] != '=')
// 	{
// 		if (!ft_isalnum(str[i]) || str[i] == '_')
// 			return (0);
// 		i++;
// 	}
// 	if (str[i + 1])
// 		return (2);
// 	return (1);
// }

// int		valid_word(char *str)
// {
// 	int i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		if (!ft_isalnum(str[i]) || str[i] == '_')
// 			return (0);
// 		i++;
// 	}
// 	return (1);
// }

// int		valid_env(char *str)
// {
// 	int i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '=')
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }

// t_dlist	*split_env(char *str)
// {
// 	t_dlist	*new;
// 	int 	i;
// 	int 	start;
// 	char	*data;

// 	new = NULL;
// 	i = 0;
// 	while (str[i] != '=')
// 		i++;
// 	i++;
// 	start = i;
// 	data = ft_substr(str, 0, i);
// 	if (!data)
// 		return (NULL);
// 	ft_dlstadd_back(&new,ft_dlstnew(ft_strdup(data)));
// 	free(data);
// 	data = NULL;
// 	while (str[i])
// 		i++;
// 	data = ft_substr(str, start, i);
// 	if (!data)
// 		return (NULL);
// 	ft_dlstadd_back(&new,ft_dlstnew(data));
// 	return (new);
// }

// void	add_token_2(t_shell **ghost, char *input, int start, int len, t_dlist **insert)
// {
// 	char	*result;
// 	t_dlist	*new;
// 	result = ft_substr(input, start, len);
// 	// (*str) = remove_quotes(ghost, (*str), ft_strlen((*str)) - check);
// 	new = ft_dlstnew(ft_strdup(result));
// 	if (!new)
// 		error_handler(ghost, INTERNAL_ERROR, "something went wrong with tokenizing", NULL);
// 	ft_dlstadd_back(&(*insert), new);
// 	free(result);
// }

// int		tokenize_space(t_shell **ghost, char *input, int start, int i, t_dlist **insert)
// {
// 	int len;
	
// 	len = i - start;
// 	if (i == start) // if nothing before seperator
// 		len = 1;
// 	if (input[start] != ' ') // ignore spaces
// 		add_token_2(ghost, input, start, len, insert); // if input before separator or esparator, tokenize it
// 	if (i != start && input[i] != ' ') // if input before separator, tokenize seperator
// 		add_token_2(ghost, input, i, 1, insert);
// 	return (i);
// }

// t_dlist	*tokenize_env(t_shell **ghost, t_dlist **temp)
// {
// 	int i;
// 	int type;
// 	int start;
// 	int count;
// 	char *str;
// 	t_dlist *insert = NULL;
	
// 	i = 0;
// 	type = 0;
// 	start = 0;
// 	count = 0;
// 	str = (*temp)->content;
// 	while (str[i])
// 	{
// 		if (str[i] == '\"' || str[i] == '\'')
// 		{
// 			type = str[i];
// 			i++;
// 			while (str[i] != type)
// 				i++;
// 		}
// 		if (str[i] == ' ')
// 		{
// 			count = 0;
// 			i = tokenize_space(ghost, str, start, i, &insert);
// 			start = i + 1;
// 		}
// 		i++;
// 	}
// 	if (i != start)
// 		add_token_2(ghost, str, start, i - start, &insert);
// 	return (insert);
// }

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
		if (!ft_strncmp(envs[j], str, i))
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

int		find_env(t_shell **ghost, t_list **temp)
{
	char	type;
	int		check;
	int		i;
	char	**str;

	type = 0;
	check = 0;
	i = 0;
	str = (char **)&(*temp)->content;
	while ((*str)[i])
	{
		if (((*str)[i] == '\"' || (*str)[i] == '\'') && type == 0)
			type = (*str)[i];
		if (type != 0 && (*str)[i] == type)
			check++;
		if (!(check % 2))
			type = 0;
		if ((*str)[i] == '$' && type != '\'')
			i += replace_env(ghost, str, i + 1) - 1;
		i++;
	}
	if (check % 2)
		error_handler(ghost, NO_MULTI_LINE, "no multiline", NULL);
	free((*temp)->content);
	(*temp)->content = (*str);
	return (check);
}

// void	expand_env(t_shell **ghost, t_list **lst)
// {
// 	t_list *head = NULL;
// 	t_list *temp = NULL;
	
// 	find_env(ghost, &(*lst));
// 	printf("temp:[%s]\n", (*lst)->content);
// 	temp = lexer(ghost, (*lst)->content, " ");
// 	ft_lstadd_back(&head, ft_lstmap(temp, copy_data, del_content));
// 	free(temp);
// 	ft_putstr_fd("list after adding back: ", STDOUT_FILENO);
// 	ft_lstiter(head, print_data);
// 	printf("\n");
// 	(*lst) = (*lst)->next;
// 	while ((*lst) && (*ghost)->status == PARSE)
// 	{
// 		find_env(ghost, &(*lst));
// 		printf("temp:[%s]\n", (*lst)->content);
// 		temp = lexer(ghost, (*lst)->content, " ");
// 		ft_lstadd_back(&head, ft_lstmap(temp, copy_data, del_content));
// 		free(temp);
// 		printf("DEBUG\n");
// 		ft_putstr_fd("list after adding back: ", STDOUT_FILENO);
// 		ft_lstiter(head, print_data);
// 		printf("\n");
// 		(*lst) = (*lst)->next;
// 	}
// 	if ((*ghost)->error)
// 	{
// 		ft_lstclear(&head, del_content);
// 		return ;
// 	}
// 	ft_lstclear(lst, del_content);
// 	*lst = head;
// 	ft_putstr_fd("list after expanding: ", STDOUT_FILENO);
// 	ft_lstiter(*lst, print_data);
// 	printf("\n");
// 	// remove_quotes(ghost, &head);
// 	// printf("PRINT COMMAND PARSER\n");
// 	// print_cmd(*command);
// 	// printf("--------------------\n");
// 	// return (head);
// }

void	expand_env(t_shell **ghost, t_list **lst)
{
	t_list *head = NULL;
	t_list *temp = NULL;
	
	find_env(ghost, &(*lst));
	temp = lexer(ghost, (*lst)->content, " ");
	// ft_putstr_fd("temp: ", STDOUT_FILENO);
	// ft_lstiter(temp, print_data);
	// printf("\n");
	ft_joinlist(&head, ft_lstmap(temp, copy_data, del_content));
	free(temp);
	// ft_putstr_fd("list after adding back: ", STDOUT_FILENO);
	// ft_lstiter(head, print_data);
	// printf("\n");
	(*lst) = (*lst)->next;
	while ((*lst) && (*ghost)->status == PARSE)
	{
		find_env(ghost, &(*lst));
		
		temp = lexer(ghost, (*lst)->content, " ");
		// ft_putstr_fd("temp: ", STDOUT_FILENO);
		// ft_lstiter(temp, print_data);
		// printf("\n");
		ft_joinlist(&head, ft_lstmap(temp, copy_data, del_content));
		free(temp);
		// printf("DEBUG\n");
		// ft_putstr_fd("list after adding back: ", STDOUT_FILENO);
		// ft_lstiter(head, print_data);
		// printf("\n");
		(*lst) = (*lst)->next;
	}
	if ((*ghost)->error)
	{
		ft_lstclear(&head, del_content);
		return ;
	}
	ft_lstclear(lst, del_content);
	*lst = head;
	// ft_putstr_fd("list after expanding: ", STDOUT_FILENO);
	// ft_lstiter(*lst, print_data);
	// printf("\n");
	// remove_quotes(ghost, &head);
	// printf("PRINT COMMAND PARSER\n");
	// print_cmd(*command);
	// printf("--------------------\n");
	// return (head);
}