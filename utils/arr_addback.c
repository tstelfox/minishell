/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   arr_addback.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/23 15:44:25 by tmullan       #+#    #+#                 */
/*   Updated: 2021/04/20 13:10:51 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ghostshell.h"

char	**arr_addback(char **arr, char *str)
{
	int i;
	int k;
	char **temp;

	i = 0;
	k = 0;
	while (arr[i])
		i++;
	temp = (char **)malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (arr[i])
	{
		temp[i] = ft_strdup(arr[i]);
		i++;
	}
	temp[i] = ft_strdup(str);
	temp[i + 1] = 0;
	for (int i = 0; arr[i]; i++)
		free(arr[i]);
	free(arr);
	return (temp);
}
