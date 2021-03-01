/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: zenotan <zenotan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/16 13:28:10 by zenotan       #+#    #+#                 */
/*   Updated: 2021/02/25 15:54:50 by zenotan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ghostshell.h"

void	print_data(void *data)
{
	char *str = data;
	ft_putstr_fd("[", STDOUT_FILENO);
	ft_putstr_fd(str, STDOUT_FILENO);
	ft_putstr_fd("]", STDOUT_FILENO);
}

void	add_token(t_list **ptr, char *input, int start, int len)
{
	char	*result;
	t_list	*new;
	result = ft_substr(input, start, len);
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
	while (input[i])
	{
		if (input[i] == '\\' && (input[i + 1] != type && type != '\'')) // '\'' is not allowed
			i += 1;
		else if (input[i] == type)
		{
			add_token(ptr, input, current + 1, i - current - 1); // delete quote from token
			return (i);
		}
		i++;
	}
	return (i);
}

int		handle_seperator(t_list **ptr, char *input, int start, int i)
{
	int len;
	
	len = i - start;
	if (i == start) // if nothing before seperator
		len = 1;
	add_token(ptr, input, start, len); // if input before separator or esparator, tokenize it
	if (i != start) // if input before separator, tokenize seperator
	{
		add_token(ptr, input, i, 1);
	}	
	while (input[i + 1] == ' ')
		i++;
	return (i);
}

t_list	*split_literal_tokens(char *input)
{
	t_list *ptr = NULL;

	int i;
	int start;
	int len;
	
	i = 0;
	start = 0;
	len = 0;
	while (input[i])
	{
		if (ft_strchr(" ><|", input[i]))
		{
			i = handle_seperator(&ptr, input, start, i);
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

void	lexer(char *input)
{
	t_list *literal_tokens;

	literal_tokens = split_literal_tokens(input);
	ft_lstiter(literal_tokens, print_data);
	// trim_spaces();
	ft_putstr_fd("\n", STDOUT_FILENO);
}
