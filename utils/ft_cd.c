/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouadel <obouadel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 19:24:23 by olabrahm          #+#    #+#             */
/*   Updated: 2022/02/15 20:38:00 by obouadel         ###   ########.fr       */
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

void	ft_cd(t_state *state)
{
	state->oldpwd = get_pwd(state->oldpwd);
	if (state->current_cmd.num_of_args == 1)
	{
		if (chdir(state->home) == -1)
			perror("cd");
		state->pwd = get_pwd(state->pwd);
	}
	else if (state->current_cmd.num_of_args == 2)
	{
		if (!ft_strncmp(state->current_cmd.args[1], ".", 2) && errno == ENOENT)
		{
			printf("cd: error retrieving current directory ");
			printf("getcwd: cannot access parent directories: ");
			printf("No such file or directory\n");
			return ;
		}
		if (chdir(state->current_cmd.args[1]) == -1)
			perror(state->current_cmd.args[1]);
		state->pwd = get_pwd(state->pwd);
	}
}
