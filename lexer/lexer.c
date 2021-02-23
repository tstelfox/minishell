/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: zenotan <zenotan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/16 13:28:10 by zenotan       #+#    #+#                 */
/*   Updated: 2021/02/22 16:04:46 by zenotan       ########   odam.nl         */
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

void	list_del(void *data)
{
	free(data);
	data = NULL;
}

void	add_token(t_list **ptr, char *input, int start, int len)
{
	char	*result;
	t_list	*new;

	result = ft_substr(input, start, len);
	// ft_putstr_fd("<", STDOUT_FILENO);
	// ft_putstr_fd(result, STDOUT_FILENO);
	// ft_putstr_fd(">", STDOUT_FILENO);
	// ft_putstr_fd("<", STDOUT_FILENO);
	// ft_putnbr_fd(start, STDOUT_FILENO);
	// ft_putstr_fd(" - ", STDOUT_FILENO);
	// ft_putnbr_fd(len, STDOUT_FILENO);
	// ft_putstr_fd(">", STDOUT_FILENO);
	new = ft_lstnew(ft_strdup(result));
	if (!new)
		error_handler("something went wrong with tokenizing");
	ft_lstadd_back(ptr, new);
	free(result);
}

int		handle_quote(t_list **ptr, char *input, int start, int current)
{
	int i;
	char type;

	if (current != start)
		add_token(ptr, input, start, current - start); // if input before quote
	i = current + 1;
	type = input[current];
	// ft_putchar_fd(type, STDOUT_FILENO);
	while (input[i])
	{
		if (input[i] == '\\' && (input[i + 1] != type && type != '\'')) // '\'' is not allowed
		// if (input[i] == '\\')
		{
			// ft_putstr_fd("<backslash>", STDOUT_FILENO);
			i += 1;
		}
		else if (input[i] == type)
		{
			add_token(ptr, input, current, i - current + 1);
			return (i);
		}
		i++;
	}
	return (i);
}

t_list	*split_literal_tokens(char *input)
{
	char *seperator = " ><";
	t_list *ptr = NULL;

	int i;
	int start;
	int len;
	
	i = 0;
	start = 0;
	len = 0;
	while (input[i])
	{
		if (ft_strchr(seperator, input[i]))
		{
			len = i - start;
			if (i == start)
				len = 1;
			add_token(&ptr, input, start, len); // if input before separator or esparator, tokenize it
			if (i != start) // if input before separator, tokenize seperator
				add_token(&ptr, input, i, 1);
			start = i + 1;
		}
		if (input[i] == '\"' || input[i] == '\'')
		{
			i = handle_quote(&ptr, input, start, i);
			start = i + 1;
		}
		i++;
	}
	if (i != start)
	{
		len = i - start;
		add_token(&ptr, input, start, len);
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
