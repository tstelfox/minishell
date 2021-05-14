/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: zenotan <zenotan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/16 13:28:10 by zenotan       #+#    #+#                 */
/*   Updated: 2021/05/14 23:52:48 by zenotan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ghostshell.h"

void	add_tkn(t_shell **ghost, t_list **ret, char *input, int len)
{
	char	*result;
	t_list	*new;

	result = ft_substr(input, 0, len);
	new = ft_lstnew(result);
	if (!new)
		error_handler(ghost, INTERNAL_ERROR, \
		"something went wrong with tokenizing", NULL);
	ft_lstadd_back(ret, new);
}

int	tknise_sep(t_shell **ghost, t_list **ret, char *str, int len)
{
	if (len == 0)
		len = 1;
	if (*str != ' ')
		add_tkn(ghost, ret, str, len);
	if (len == 1 && *str != ' ')
		add_tkn(ghost, ret, str, 1);
	return (1);
}

int	skip_quotes(char *str, int i)
{
	int	inc;
	int	type;

	inc = 0;
	type = 0;
	if (str[i] == '\"' || str[i] == '\'')
	{
		type = str[i];
		inc++;
		while (str[i + inc] != type && str[i + inc])
			inc++;
	}
	return (inc);
}

t_list	*lexer(t_shell **ghost, char *input, char *seperators)
{
	int		i;
	int		start;
	char	*str;
	t_list	*ret;

	i = 0;
	start = 0;
	ret = NULL;
	if (!input)
		return (NULL);
	str = input;
	while (str[i])
	{
		i += skip_quotes(str, i);
		if (!str[i])
			break ;
		if (ft_strchr(seperators, str[i]))
			start = i + tknise_sep(ghost, &ret, str + start, i - start);
		i++;
	}
	if (i != start)
		add_tkn(ghost, &ret, str + start, i - start);
	return (ret);
}
