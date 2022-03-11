/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olabrahm <olabrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 19:24:23 by olabrahm          #+#    #+#             */
/*   Updated: 2022/03/11 11:52:50 by olabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_pwd(char *pwd)
{
	if (pwd)
	{
		free(pwd);
		pwd = NULL;
	}
	pwd = getcwd(NULL, PATH_MAX);
	return (pwd);
}

void	ft_chdir_home(t_state *state)
{
	if (!state->home)
	{
		ft_put_error("cd", "HOME not set.\n");
		state->status = 1;
		return ;
	}
	state->oldpwd = get_pwd(state->oldpwd);
	if (chdir(state->home->value) == -1)
		ft_perror(state, "cd", 1);
	state->pwd = get_pwd(state->pwd);
	state->status = 0;
}

static void	ft_chdir_back(t_state *state)
{
	char	*tmp;

	if (!state->oldpwd)
	{
		ft_put_error("cd", "OLDPWD not set\n");
		state->status = 1;
		return ;
	}
	tmp = ft_strdup(state->oldpwd);
	if (!tmp)
		ft_free_exit(state, OUT_OF_MEM);
	state->oldpwd = get_pwd(state->oldpwd);
	if (chdir(tmp) == -1)
		ft_perror(state, "cd", 1);
	free(tmp);
	state->pwd = get_pwd(state->pwd);
	state->status = 0;
}

static void	ft_chdir(t_state *state, char *dir_name)
{
	state->oldpwd = get_pwd(state->oldpwd);
	if (chdir(dir_name) == -1)
		ft_perror(state, dir_name, 1);
	state->pwd = get_pwd(state->pwd);
	state->status = 0;
}

void	ft_cd(t_state *state, t_cmd *current_cmd)
{
	if (current_cmd->num_of_args == 1)
		ft_chdir_home(state);
	else if (current_cmd->num_of_args == 2)
	{
		if (!ft_strncmp(current_cmd->args[1], ".", 2) && errno == ENOENT)
		{
			ft_put_error("cd", "error retrieving current directory ");
			ft_put_error("getcwd", "cannot access parent directories: ");
			ft_put_error(NULL, "No such file or directory\n");
			state->status = 0;
			return ;
		}
		if (!ft_strcmp(current_cmd->args[1], "--"))
			ft_chdir_home(state);
		else if (!ft_strcmp(current_cmd->args[1], "-"))
			ft_chdir_back(state);
		else
			ft_chdir(state, current_cmd->args[1]);
	}
}
