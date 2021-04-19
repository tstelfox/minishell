/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: zenotan <zenotan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/15 19:14:32 by zenotan       #+#    #+#                 */
/*   Updated: 2021/04/19 17:15:00 by ztan          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ghostshell.h"

// char	**get_envp(char **envp)
// {
// 	char	**env;
// 	int		i;
// 	int		k;

// 	i = 0;
// 	k = 0;
// 	while (envp[i])
// 		i++;
// 	env = (char **)malloc(sizeof(char *) * (i + 1));
// 	if (!env)
// 		return (NULL);
// 	while (envp[k])
// 	{
// 		env[k] = ft_strdup(envp[k]);
// 		k++;
// 	}
// 	env[k] = 0;
// 	return (env);
// }

char 	*remove_quotes(t_shell **ghost, char *str, int len)
{
	char *ret;
	int i;
	int j;
	int type;
	int check;

	i = 0;
	j = 0;
	check = 0;
	type = 0;
	ret = malloc(sizeof(char) * (len + 1));
	if (!ret)
	{
		error_handler(ghost, INTERNAL_ERROR, "no multiline", NULL);
		return (NULL);
	}
	while (str[i])
	{
		if ((str[i] == '\"' || str[i] == '\'') && type == 0)
			type = str[i];
			
		if (type != 0 && str[i] == type)
			check++;
		if (type != str[i] || type == 0)
		{
			ret[j] = str[i];
			j++;
		}
		if (!(check % 2))
			type = 0;
		i++;
	}
	ret[j] = '\0';
	return (ret);
}

// int		check_quote(t_shell **ghost)
// {
// 	char	type;
// 	int		check;
// 	int		i;
// 	char	*str;

// 	type = 0;
// 	check = 0;
// 	i = 0;
// 	check_env_quoted(ghost);
// 	// printf("data:%s\n", (*ghost)->tokens->content);
// 	str = (*ghost)->tokens->content;
// 	while (str[i])
// 	{
// 		if ((str[i] == '\"' || str[i] == '\'') && type == 0)
// 			type = str[i];
// 		if (type != 0 && str[i] == type)
// 			check++;
// 		if (!(check % 2))
// 			type = 0;
// 		i++;
// 	}
// 	if (check % 2)
// 	{
// 		error_handler(ghost, NO_MULTI_LINE, "no multiline", NULL);
// 		return (-1);
// 	}
// 	// printf("data2:[%s],check[%i]\n", str, check);
// 	str = remove_quotes(ghost, str, ft_strlen(str) - check);
// 	// printf("data3:%s\n", str);
// 	free((*ghost)->tokens->content);
// 	(*ghost)->tokens->content = str;
// 	return (0);
// }

int		check_quote(t_shell **ghost)
{
	char	type;
	int		check;
	int		i;
	char	**str;

	type = 0;
	check = 0;
	i = 0;
	str = (char **)&(*ghost)->tokens->content;
	while ((*str)[i])
	{
		if (((*str)[i] == '\"' || (*str)[i] == '\'') && type == 0)
			type = (*str)[i];
		if (type != 0 && (*str)[i] == type)
			check++;
		if (!(check % 2))
			type = 0;
		if ((*str)[i] == '$' && type != '\'')
			i += replace_env_quoted(ghost, str, i + 1) - 1;
		i++;
	}
	if (check % 2)
	{
		error_handler(ghost, NO_MULTI_LINE, "no multiline", NULL);
		return (-1);
	}
	// printf("data2:[%s],check[%i]\n", str, check);
	(*str) = remove_quotes(ghost, (*str), ft_strlen((*str)) - check);
	// printf("data3:%s\n", str);
	free((*ghost)->tokens->content);
	(*ghost)->tokens->content = (*str);
	return (0);
}

int		check_meta(char *str)
{
	if (!ft_strcmp(str, ">") || !ft_strcmp(str, "<") || !ft_strcmp(str, "|"))
		return (1);
	return (0);
}

int		check_colon(t_shell **ghost, t_cmd *command)
{
	if (!ft_strcmp((*ghost)->tokens->content, ";"))
	{
		(*ghost)->status = EXECUTE;
		if ((*ghost)->tokens->next)
			(*ghost)->tokens = (*ghost)->tokens->next;
		else
			(*ghost)->status = FINISHED;
		ft_lstadd_back(&(*ghost)->commands, ft_lstnew(command));
		return (1);
	}
	return (0);
}

int		check_seperator(t_shell **ghost, t_cmd *command)
{
	if (!ft_strcmp((*ghost)->tokens->content, "|"))
	{
		command->seprator_type = PIPE;
		if (!ft_strcmp((*ghost)->tokens->next->content, "|"))
			error_handler(ghost, PARSE_ERROR, "ghostshell does not support double pipes", NULL);
		return (1);
	}
	return (0);
}

int		check_redir(t_shell **ghost, t_cmd *command)
{
	t_redir *redir;
	t_dlist	*tokens;

	redir = NULL;
	tokens = (*ghost)->tokens;

	if (!ft_strcmp(tokens->content, ">"))
	{
		if (!ft_strcmp(tokens->next->content, ">")) // check for ">>"
		{
			tokens = tokens->next;
			redir = new_redir(ghost, tokens->next->content, OUTPUT_ADD);
		}
		else
			redir = new_redir(ghost, tokens->next->content, OUTPUT);
		ft_lstadd_back(&command->redirection, ft_lstnew(redir));
		(*ghost)->tokens = tokens->next;
	}
	else if (!ft_strcmp(tokens->content, "<"))
	{
		redir = new_redir(ghost, tokens->next->content, INPUT);
		ft_lstadd_back(&command->redirection, ft_lstnew(redir));
		(*ghost)->tokens = tokens->next;
	}
	else
		return (0);
	return (1);
}

void	parser(t_shell **ghost)
{
	t_cmd	*command;

	if ((*ghost)->commands)
		ft_lstclear(&(*ghost)->commands, del_commands);
	while ((*ghost)->tokens && (*ghost)->status == PARSE && !(*ghost)->status)
	{
		// if env token->content
		if (check_quote(ghost))
			break ;
		command = new_command();
		command->type = ft_strdup((*ghost)->tokens->content);
		(*ghost)->tokens = (*ghost)->tokens->next;
		while ((*ghost)->tokens && (*ghost)->status == PARSE) //parse command
		{
			// if env token->content
			if (check_quote(ghost))
				break ;
			if (check_colon(ghost, command))
				return ;
			if (check_seperator(ghost, command))
				break ;
			if (!check_redir(ghost, command))
				ft_lstadd_back(&command->args, ft_lstnew(ft_strdup((*ghost)->tokens->content)));
			if (!(*ghost)->tokens)
				break ;
			(*ghost)->tokens = (*ghost)->tokens->next;
		}
		ft_lstadd_back(&(*ghost)->commands, ft_lstnew(command));
		if (!(*ghost)->tokens)
			break ;
		(*ghost)->tokens = (*ghost)->tokens->next;
	}
	(*ghost)->status = FINISHED;
}