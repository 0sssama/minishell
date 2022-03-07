/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olabrahm <olabrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 15:35:29 by obouadel          #+#    #+#             */
/*   Updated: 2022/03/07 21:14:12 by olabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_cmd_exec(t_state *state, char **paths, char **cmdarg)
{
	char	*path;
	int		i;

	i = 0;
	path = ft_check_path(state, paths, cmdarg);
	if (!path)
	{
		ft_put_error(cmdarg[0], "command not found\n");
		return ;
	}
	state->pid = fork();
	if (state->pid == -1)
		ft_free_exit(state, 1);
	if (state->pid == 0)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		execve(path, cmdarg, state->envtab);
	}
	waitpid(state->pid, &state->status, 0);
	free(path);
	if (state->sig == SIGQUIT)
		state->status = 131;
	else if (state->sig == SIGINT)
		state->status = 130;
	else
		state->status = WEXITSTATUS(state->status);
}

static void	ft_exec_path(t_state *state, t_cmd *current_cmd)
{
	state->pid = fork();
	if (state->pid == -1)
		ft_free_exit(state, 1);
	if (state->pid == 0)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		if (execve(current_cmd->name, \
			current_cmd->args, state->envtab) == -1)
		{
			if (ft_strchr(current_cmd->name, '/'))
				ft_put_error(current_cmd->name, \
					"No such file or directory\n");
			else
				ft_put_error(current_cmd->name, "command not found\n");
			exit(127);
		}
	}
	waitpid(state->pid, &state->status, 0);
	state->status = WEXITSTATUS(state->status);
}

static void	ft_execve(t_state *state, t_cmd *current_cmd)
{
	char	**paths;
	char	**cmdarg;
	char	*forfree;
	int		i;

	i = -1;
	if (current_cmd->args[0][0] == '.' ||
		ft_strchr(current_cmd->args[0], '/'))
		return (ft_exec_path(state, current_cmd));
	cmdarg = current_cmd->args;
	state->path = ft_get_env(&state->env, "PATH");
	paths = NULL;
	if (state->path)
		paths = ft_split(state->path->value, ':');
	while (paths && paths[++i])
	{
		forfree = paths[i];
		paths[i] = ft_strjoin(paths[i], "/");
		free(forfree);
	}
	ft_cmd_exec(state, paths, cmdarg);
	ft_free_temp(paths);
}

void	ft_execute(t_state *state, t_cmd *current_cmd)
{
	if (!ft_strncmp(current_cmd->name, "echo", 5))
		ft_echo(state, current_cmd);
	else if (!ft_strncmp(current_cmd->name, "cd", 3))
		ft_cd(state, current_cmd);
	else if (!ft_strncmp(current_cmd->name, "pwd", 4))
		ft_pwd(state);
	else if (!ft_strncmp(current_cmd->name, "env", 4))
		ft_env(state, current_cmd);
	else if (!ft_strncmp(current_cmd->name, "unset", 6))
		ft_env_unset(state, current_cmd);
	else if (!ft_strncmp(current_cmd->name, "export", 7))
		ft_env_export(state, current_cmd);
	else if (!ft_strncmp(current_cmd->name, "exit", 5))
		ft_exit(state, current_cmd);
	else
		ft_execve(state, current_cmd);
}
