/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olabrahm <olabrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 19:24:23 by olabrahm          #+#    #+#             */
/*   Updated: 2022/03/09 12:45:46 by olabrahm         ###   ########.fr       */
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

void	ft_cd(t_state *state, t_cmd *current_cmd)
{
	state->oldpwd = get_pwd(state->oldpwd);
		state->status = 0;
	if (current_cmd->num_of_args == 1)
	{
		if (chdir(state->home->value) == -1)
			ft_perror(state, "cd", 1);
		state->pwd = get_pwd(state->pwd);
	}
	else if (current_cmd->num_of_args == 2)
	{
		if (!ft_strncmp(current_cmd->args[1], ".", 2) && errno == ENOENT)
		{
			ft_put_error("cd", "error retrieving current directory ");
			ft_put_error("getcwd", "cannot access parent directories: ");
			ft_put_error(NULL, "No such file or directory\n");
			return ;
		}
		if (chdir(current_cmd->args[1]) == -1)
			ft_perror(state, current_cmd->args[1], 1);
		state->pwd = get_pwd(state->pwd);
	}
}
