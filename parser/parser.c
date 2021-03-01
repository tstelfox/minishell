/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: zenotan <zenotan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/15 19:14:32 by zenotan       #+#    #+#                 */
/*   Updated: 2021/03/01 18:03:42 by ztan          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ghostshell.h"

// t_list commands
// commands->command = token[0]
// commands->args = token[0]

// void	handle_io(t_shell *shell, t_list *lst)
// {
// 	t_list *temp;
// 	bool input;

// 	input = false;
// 	if (!lst)
// 		return ;
// 	temp = lst;
// 	while (temp)
// 	{
// 		if (temp->content[0] == '>' && temp->content[1] == '\0')
// 			input = split_io(&shell, INPUT);
// 		if (temp->content[0] == '<' && temp->content[1] == '\0')
// 			input = split_io(&shell, OUTPUT);
// 		temp = temp->next;
// 	}
// }

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

// void	assign_tokens(char **tokens)
// {
// 	t_list	*command = NULL;
// 	// t_list *arg = NULL;
// 	t_cmd *cmd = (t_cmd *)malloc(sizeof(t_cmd));
// 	t_redirection = NULL;
// 	int args = 0;
// 	int i = 0;
	
// 	while (tokens[i])
// 	{
// 		if ((tokens[i][0] != ' ' && tokens[i][1] != '\n'))
// 		{
// 			cmd->type = ft_substr(token[0]);			
// 			args = 1;
// 		}
// 		if 
// 		else if (tokens[i][0] == '>' && tokens[i][1] == '\n')
// 		{
			
// 		}
// 		else if (tokens[i][0] == '<' && tokens[i][1] == '\n')
// 		{
			
// 		}
// 		i++;
// 	}
// }

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