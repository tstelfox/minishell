/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: zenotan <zenotan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/16 13:28:10 by zenotan       #+#    #+#                 */
/*   Updated: 2021/05/14 19:20:20 by ztan          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ghostshell.h"

void	add_tkn(t_shell **ghost, t_list **ret, char *input, int start, int len)
{
	char	*result;
	t_list	*new;

	result = ft_substr(input, start, len);
	new = ft_lstnew(result);
	if (!new)
		error_handler(ghost, INTERNAL_ERROR, \
		"something went wrong with tokenizing", NULL);
	ft_lstadd_back(ret, new);
}

int	tknise_sep(t_shell **ghost, t_list **ret, char *str, int start, int i)
{
	int len;
	
	len = i - start;
	if (i == start)
		len = 1;
	if (str[start] != ' ')
		add_tkn(ghost, ret, str, start, len);
	if (i != start && str[i] != ' ')
		add_tkn(ghost, ret, str, i, 1);
	return (i);
}

t_list	*lexer(t_shell **ghost, char *input, char *seperators)
{
	int		i;
	int		start;
	char	*str;
	int		type;
	t_list	*ret;

	i = 0;
	start = 0;
	type = 0;
	ret = NULL;
	if (!input)
		return (NULL);
	str = input;
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '\'')
		{
			type = str[i];
			i++;
			while (str[i] != type && str[i])
				i++;
			if (!str[i])
				break ;
		}
		if (ft_strchr(seperators, str[i]))
		{
			i = tknise_sep(ghost, &ret, str, start, i);
			start = i + 1;
		}
		i++;
	}
	if (i != start)
		add_tkn(ghost, &ret, str, start, i - start);
	return (ret);
}