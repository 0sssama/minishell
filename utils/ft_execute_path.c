/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouadel <obouadel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 15:26:31 by obouadel          #+#    #+#             */
/*   Updated: 2022/02/19 19:28:45 by obouadel         ###   ########.fr       */
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
