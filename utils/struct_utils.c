/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   struct_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: ztan <ztan@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/08 11:25:13 by ztan          #+#    #+#                 */
/*   Updated: 2021/05/12 16:26:33 by ztan          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ghostshell.h"

void	del_content(void *content)
{
	free(content);
	content = NULL;
}

void	del_redir(void *list)
{
	t_redir *redir;

	redir = list;
	free(redir->file);
	redir->file = NULL;
	redir->type = 0;
	free(redir);
}

void	del_commands(void *list)
{
	t_cmd *commands;

	commands = (t_cmd *)list;
	if (commands->type)
	{
		free(commands->type);
		ft_lstclear(&commands->args, del_content);
	}
	if (commands->args)
		free(commands->args);
	if (commands->redirection)
	{
		ft_lstclear(&commands->redirection, del_redir);
		free(commands->redirection);
	}
	commands->seprator_type = 0;
	free(commands);
}

void	del_darray(char **str)
{
	int i;

	i = 0;
	if (str)
	{
		if (str[i])
		{
			while (str[i])
			{
				free(str[i]);
				i++;
			}
		}
		free(str);
	}
}

t_redir	*new_redir(t_shell **ghost, char *file, int type)
{
	t_redir *new_redir;
	char	*temp;
	int		qts;

	if (check_meta(file))
		error_handler(ghost, SYNTAX_ERROR, "syntax error near unexpected token", file);
	temp = find_env(ghost, file);
	if (check_redir(temp)) // quotesssssssssssss
		error_handler(ghost, PARSE_ERROR, "ambiguous redirect", NULL);
	new_redir = malloc(sizeof(t_redir));
	if (!new_redir)
		error_handler(ghost, INTERNAL_ERROR, "failed to allocate space", NULL);
	qts = count_quotes(temp);
	if (qts)
	{
		new_redir->file = handle_quotes(ghost, temp, ft_strlen(temp) - qts);
		free(temp);
	}
	else
		new_redir->file = temp;
	new_redir->type = type;
	return (new_redir);
}

t_cmd	*new_command()
{
	t_cmd	*new_command;

	new_command = malloc(sizeof(t_cmd));
	if (!new_command)
		return NULL;
	new_command->args = NULL;
	new_command->redirection = NULL;
	new_command->type = NULL;
	new_command->seprator_type = 0;

	return (new_command);
}

void		del_ghost(t_shell **ghost)
{
	if (*ghost)
	{
		if ((*ghost)->current)
		{
			ft_dlstclear(&(*ghost)->current, del_content);
			free((*ghost)->current);
		}
		if ((*ghost)->commands)
		{
			ft_lstclear(&(*ghost)->commands, del_commands);
			free((*ghost)->commands);
		}
		if ((*ghost)->tokens)
		{
			ft_lstclear(&(*ghost)->tokens, del_content);
			free((*ghost)->tokens);
		}
		if ((*ghost)->env)
			del_darray((*ghost)->env);
		if ((*ghost)->reins)
			reins_destroy((*ghost)->reins);
		free(*ghost);
	}
}

void	get_env(t_shell **ghost, char **envp)
{
	int i = 0;
	while (envp[i])
		i++;
	(*ghost)->env = (char **)malloc(sizeof(char *) * (i + 1));
	if (!(*ghost)->env)
		error_handler(ghost, INTERNAL_ERROR, "failed to allocate space", NULL);
	int k = 0;
	while (envp[k])
	{
		(*ghost)->env[k] = ft_strdup(envp[k]);
		k++;
	}
	(*ghost)->env[k] = 0;
}

void	restart_shell(t_shell **ghost)
{
	ft_lstclear(&((*ghost)->tokens), del_content);
	free((*ghost)->tokens);
	ft_lstclear(&((*ghost)->commands), del_commands);
	free((*ghost)->commands);
	(*ghost)->commands = NULL;
	(*ghost)->tokens = NULL;
	(*ghost)->status = PARSE;
	(*ghost)->error = 0;
}

t_shell	*init_shell(char **env)
{
	t_shell *new_shell;
	
	new_shell = malloc(sizeof(t_shell));
	if (!new_shell)
	{
		printf("OFHIER\n");
		return (NULL);
	}
		
	ft_bzero(new_shell, sizeof(t_shell));
	new_shell->reins = reins_init();
	if (!new_shell->reins)
	{
		printf("HIER\n");
		free(new_shell);
		return (NULL);
	}
	new_shell->first_command = TRUE;
	new_shell->current = new_shell->history;
	new_shell->env = get_envp(env);
	// new_shell->path = 0;
	new_shell->args = NULL;
	new_shell->status = 0;
	new_shell->out = -42;
	new_shell->pipefd[0] = -69;
	new_shell->pipefd[1] = -47;
	new_shell->error = 0;
	new_shell->ret_stat = 0;
	new_shell->pid = -99;
	new_shell->built_in[0] = "echo";
	new_shell->built_in[1] = "cd";
	new_shell->built_in[2] = "pwd";
	new_shell->built_in[3] = "exit";
	new_shell->built_in[4] = "env";
	new_shell->built_in[5] = "unset";
	new_shell->built_in[6] = "export";
	new_shell->g_builtin_f[0] = &run_echo;
	new_shell->g_builtin_f[1] = &run_cd;
	new_shell->g_builtin_f[2] = &run_pwd;
	new_shell->g_builtin_f[3] = &run_exit;
	new_shell->g_builtin_f[4] = &run_env;
	new_shell->g_builtin_f[5] = &run_unset;
	new_shell->g_builtin_f[6] = &run_export;
	return (new_shell);
}