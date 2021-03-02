/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: zenotan <zenotan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/15 19:14:32 by zenotan       #+#    #+#                 */
/*   Updated: 2021/03/02 12:22:55 by zenotan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ghostshell.h"

char	**list_to_arr(t_list *tokens)
{
	t_list	*temp;
	char	**ret;
	int		i;

	if (!tokens)
		return (NULL);
	temp = tokens;
	if (!(ret = (char **)malloc(sizeof(char *) * ft_lstsize(tokens) + 1)))
		error_handler("malloc fail");
	i = 0;
	while (temp)
	{
		ret[i] = ft_strdup(temp->content);
		temp = temp->next;
		i++;
	}
	ret[i] = 0;
	return (ret);
}

void	parser(t_list *tokens)
{
	char **list;
	int i = 0;
	
	list = list_to_arr(tokens);
	while (list[i])
	{
		ft_putstr_fd(list[i], STDOUT_FILENO);
		i++;
	}
	ft_putchar_fd('\n', STDOUT_FILENO);
	// assign_tokens(list);
    //handle_io(tokens)
    //parse redirections
    //parse command and args until i/o seperatore or pipe
    //if io, parse redirection
    //remove spaces where needed
    //if pipe ,  make new command
}