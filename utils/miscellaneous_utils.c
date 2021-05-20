/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   miscellaneous_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: zenotan <zenotan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/21 22:30:58 by zenotan       #+#    #+#                 */
/*   Updated: 2021/05/20 16:37:06 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ghostshell.h"

int	check_dir(t_cmd *cmd, t_shell **ghost)
{
	struct stat	buf;

	lstat(cmd->type, &buf);
	if (S_ISDIR(buf.st_mode))
	{
		(*ghost)->error = DIRECTORY;
		return (0);
	}
	return (1);
}

void	free_arr(char **arr)
{
	int		i;

	i = 0;
	if (arr != 0)
	{
		while (arr[i])
		{
			free(arr[i]);
			i++;
		}
		free(arr);
	}
}

void	free_all(t_shell **ghost)
{
	int	i;

	i = 0;
	while ((*ghost)->env[i])
	{
		free((*ghost)->env[i]);
		i++;
	}
	free((*ghost)->env);
}

char	**arr_addback(char **arr, char *str)
{
	int		i;
	int		k;
	char	**temp;

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
	free_arr(arr);
	return (temp);
}

char	*ft_strjoinfree(char *s1, char const *s2)
{
	size_t	s1len;
	size_t	s2len;
	char	*ret;

	if (!s1)
		return (NULL);
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	ret = malloc(sizeof(char) * (s1len + s2len + 1));
	if (!ret)
		return (NULL);
	ft_memcpy(ret, s1, s1len);
	ft_strlcpy(ret + s1len, s2, s2len + 1);
	free(s1);
	return (ret);
}
