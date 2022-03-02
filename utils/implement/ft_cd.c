/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouadel <obouadel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 19:24:23 by olabrahm          #+#    #+#             */
/*   Updated: 2022/03/01 18:16:30 by obouadel         ###   ########.fr       */
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
			printf("cd: error retrieving current directory ");
			printf("getcwd: cannot access parent directories: ");
			printf("No such file or directory\n");
			return ;
		}
		if (chdir(current_cmd->args[1]) == -1)
			ft_perror(state, current_cmd->args[1], 1);
		state->pwd = get_pwd(state->pwd);
	}
}
