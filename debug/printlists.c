/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   printlists.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: zenotan <zenotan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/02 13:56:38 by zenotan       #+#    #+#                 */
/*   Updated: 2021/03/03 13:35:13 by zenotan       ########   odam.nl         */
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
		if (ft_strcmp(temp->content, " "))
		{
			ret[i] = ft_strdup(temp->content);
			i++;
		}
		temp = temp->next;
	}
	ret[i] = 0;
	return (ret);
}
