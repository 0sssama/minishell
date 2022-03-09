/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_setup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouadel <obouadel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 19:19:46 by obouadel          #+#    #+#             */
/*   Updated: 2022/03/07 19:33:41 by obouadel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_pipefds(t_state *state, int i)
{
	i--;
	while (i >= 0)
	{
		close(state->fds[i][1]);
		close(state->fds[i][0]);
		i--;
	}
	ft_free_setup(state, -1);
	free(state->pids);
}

void	ft_free_setup(t_state *state, int i)
{
	int	j;

	j = 0;
	if (i >= 0)
	{
		i--;
		while (i >= 0)
			free(state->fds[i--]);
		free(state->fds);
		return ;
	}
	if (i == -1)
	{
		while (j < state->pipes)
			free(state->fds[j++]);
		free(state->fds);
		return ;
	}
}