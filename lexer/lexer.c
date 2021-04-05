/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: zenotan <zenotan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/16 13:28:10 by zenotan       #+#    #+#                 */
/*   Updated: 2021/04/02 20:52:26 by zenotan       ########   odam.nl         */
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

void	add_token(t_shell **ghost, char *input, int start, int len)
{
	char	*result;
	t_list	*new;
	result = ft_substr(input, start, len);
	new = ft_lstnew(ft_strdup(result));
	if (!new)
		error_handler(ghost, INTERNAL_ERROR, "something went wrong with tokenizing", NULL);
	ft_lstadd_back(&(*ghost)->tokens, new);
	free(result);
}

int		handle_quote(char *input, int current)
{
	int i;
	char type;

	i = current + 1;
	type = input[current];
	while (input[i])
	{
		if (input[i] == type)
			return (i);
		i++;
	}
	return (i);
}

int		handle_seperator(t_shell **ghost, char *input, int start, int i)
{
	int len;
	
	len = i - start;
	if (i == start) // if nothing before seperator
		len = 1;
	if (input[start] != ' ') // ignore spaces
		add_token(ghost, input, start, len); // if input before separator or esparator, tokenize it
	if (i != start && input[i] != ' ') // if input before separator, tokenize seperator
		add_token(ghost, input, i, 1);
	return (i);
}

void	lexer(t_shell **ghost)
{
	int i;
	int start;
	char *input;

	i = 0;
	start = 0;
	if (!(*ghost)->line)
		return ;
	input = (*ghost)->line;
	while (input[i])
	{
		if (ft_strchr(" ><|;", input[i]))
		{
			if (input[i] == '>' && input[i + 1] == '>')
				i = handle_seperator(ghost, input, start, i);
			else
				i = handle_seperator(ghost, input, start, i);
			start = i + 1;
		}
		if (input[i] == '\"' || input[i] == '\'')
			i = handle_quote(input, i);
		i++;
	}
	if (i != start)
		add_token(ghost, input, start, i - start);
}

