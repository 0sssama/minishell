/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouadel <obouadel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 15:26:31 by obouadel          #+#    #+#             */
/*   Updated: 2022/03/11 18:26:15 by obouadel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_check_path(t_state *state, char **paths, char **cmdarg)
{
	int		i;
	char	*forfree;

	i = 0;
	while (paths && paths[i])
	{
		forfree = ft_strjoin(paths[i++], cmdarg[0]);
		if (!access(forfree, X_OK | F_OK))
			return (forfree);
		free(forfree);
	}
	state->status = 127;
	return (NULL);
}

char	*ft_check_relative(t_state *state, char *cmd)
{
	struct stat	statbuf;

	stat(cmd, &statbuf);
	if (!access(cmd, X_OK | F_OK))
	{
		if (S_ISDIR(statbuf.st_mode) == 1)
		{
			state->status = 126;
			return (ft_put_error(cmd, "is a directory\n"), NULL);
		}
		else
			return (cmd);
	}
	if (ft_strchr(cmd, '/'))
		ft_put_error(cmd, "No such file or directory\n");
	else
		ft_put_error(cmd, "command not found\n");
	state->status = 127;
	return (NULL);
}
