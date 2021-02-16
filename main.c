/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: zenotan <zenotan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/15 19:18:46 by zenotan       #+#    #+#                 */
/*   Updated: 2021/02/15 20:14:27 by zenotan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ghostshell.h"

void	read_line(char **input)
{
	int ret;
	
	ret = get_next_line(STDIN_FILENO, input);
	if (ret == -1)
	{
		free(*input);
		// err handler
	}
	return ;
}

int main(void)
{
	char	*input;

	input = NULL;
	// prompt
	// printf("ghostshell$> ");
	ft_putstr_fd("ghostshell$> ", STDIN_FILENO);
	read_line(&input);
	printf("[%s]" , input);
	return (0);
}