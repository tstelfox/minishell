/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: zenotan <zenotan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/16 13:28:10 by zenotan       #+#    #+#                 */
/*   Updated: 2021/02/17 18:11:17 by zenotan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ghostshell.h"

// rules
// echo "\"", echo "\'" are possible
// echo '\"' is possible
// echo '\'' is not possible -> a single quote cannot appear in single quotes

// method
// when a quote is met, read untill valid ending quote (so not \")
// everything is part of the same token untill seperator (;, |, <, >, <<, >>)
// todo:
// - check if opening quote
// - if quote read untill valid end quote
// - check for invalid ( \") -> check if valid "\", so not "\\"

// void print_data(void *data)
// {
// 	// char *str = data;
// 	// ft_putstr_fd("[", STDOUT_FILENO);
// 	// ft_putstr_fd(str, STDOUT_FILENO);
// 	// ft_putstr_fd("]", STDOUT_FILENO);
// }

t_list	*split_literal_tokens(char *input)
{
	char *seperator = " ><";
	char *result;
	t_list *ptr = NULL;

	int i, start, len;
	
	i = 0;
	start = 0;
	while (input[i])
	{
		if (ft_strchr(seperator, input[i]))
		{
			len = i - start;
			if (i == start)
				len = 1;
			result = ft_substr(input, start, len);
			ft_lstadd_back(&ptr, ft_lstnew(ft_strdup(result)));
			free(result);
			if (i != start)
			{
				result = ft_substr(input, i, 1);
				ft_lstadd_back(&ptr, ft_lstnew(ft_strdup(result)));
				free(result);
			}
			start = i + 1;
		}
		i++;
	}
	if (i != start)
	{
		len = i - start;
		result = ft_substr(input, start, len + 1);
		ft_lstadd_back(&ptr, ft_lstnew(ft_strdup(result)));
		free(result);
	}
	return (ptr);
}

t_list	*lexer(char *input)
{
	t_list *literal_tokens;

	literal_tokens = split_literal_tokens(input);
	// ft_lstiter(literal_tokens, print_data);
	// ft_putstr_fd("\n", STDOUT_FILENO);
	return (literal_tokens);
}
