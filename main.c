/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: zenotan <zenotan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/15 19:18:46 by zenotan       #+#    #+#                 */
/*   Updated: 2021/02/16 11:42:55 by zenotan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ghostshell.h"

void	lexer(char *input)
{
	// split input on spaces
	// save split items as tokens
	//  - as 2d array?
	// 
}

void	read_line(char **input)
{
	// this also needs to read from a file?
	int ret;
	
	ret = get_next_line(STDIN_FILENO, input);
	if (ret == -1)
	{
		free(*input);
		/* err handler */
	}
}

void	exec_shell(void)
{
	char	*input;

	input = NULL;
	while (1) // check for errors
	{
		ft_putstr_fd("ghostshell$> ", STDIN_FILENO);
		read_line(&input);
		// lexer
		// parser
		// exec  command
		// check errors
		ft_putstr_fd("[" , STDIN_FILENO);
		ft_putstr_fd(input , STDIN_FILENO);
		ft_putstr_fd("]\n" , STDIN_FILENO);
	}
	
}

int main(void)
{
	exec_shell();
	return (0);
}