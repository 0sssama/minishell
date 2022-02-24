/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouadel <obouadel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 15:35:29 by obouadel          #+#    #+#             */
/*   Updated: 2022/02/24 17:05:57 by obouadel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_free_temp(char **s1)
{
	int	i;

	i = 0;
	if (!s1)
		return ;
	while (s1[i])
		free(s1[i++]);
	free(s1);
}

static void	ft_cmd_exec(t_state *state, char **paths, char **cmdarg)
{
	char	*path;
	int		i;

	i = 0;
	path = ft_check_path(state, paths, cmdarg);
	if (!path)
	{
		ft_put_error(state->current_cmd.name, "command not found\n");
		return ;
	}
	state->pid = fork();
	if (state->pid == -1)
		ft_free_exit(state, 1);
	if (state->pid == 0)
		execve(path, cmdarg, state->envtab);
	waitpid(state->pid, &state->status, 0);
	free(path);
	state->status = WEXITSTATUS(state->status);
}

static void	ft_exec_path(t_state *state)
{
	state->pid = fork();
	if (state->pid == -1)
		ft_free_exit(state, 1);
	if (state->pid == 0)
	{
		if (execve(state->current_cmd.name, \
			state->current_cmd.args, state->envtab) == -1)
		{
			if (ft_strchr(state->current_cmd.name, '/'))
				ft_put_error(state->current_cmd.name, \
					"No such file or directory\n");
			else
				ft_put_error(state->current_cmd.name, "command not found\n");
			exit(127);
		}
	}
	waitpid(state->pid, &state->status, 0);
	state->status = WEXITSTATUS(state->status);
}

static void	ft_execve(t_state *state)
{
	char	**paths;
	char	**cmdarg;
	char	*forfree;
	int		i;

	i = -1;
	if (state->current_cmd.args[0][0] == '.' ||
		ft_strchr(state->current_cmd.args[0], '/'))
		return (ft_exec_path(state));
	cmdarg = state->current_cmd.args;
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

void	ft_execute(t_state *state)
{
	if (!ft_strncmp(state->current_cmd.name, "echo", 5))
		ft_echo(state);
	else if (!ft_strncmp(state->current_cmd.name, "cd", 3))
		ft_cd(state);
	else if (!ft_strncmp(state->current_cmd.name, "pwd", 4))
		ft_pwd(state);
	else if (!ft_strncmp(state->current_cmd.name, "env", 4))
		ft_env(state);
	else if (!ft_strncmp(state->current_cmd.name, "unset", 6))
		ft_env_unset(state);
	else if (!ft_strncmp(state->current_cmd.name, "export", 7))
		ft_env_export(state);
	else if (!ft_strncmp(state->current_cmd.name, "exit", 5))
		ft_exit(state);
	else
		ft_execve(state);
	ft_free_cmd(state);
}
