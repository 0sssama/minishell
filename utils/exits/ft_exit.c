/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olabrahm <olabrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 16:49:10 by obouadel          #+#    #+#             */
/*   Updated: 2022/03/07 18:45:06 by olabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_close(t_state *state)
{
	int	i;

	i = 0;
	while (i < state->pipes)
	{
		close(state->fds[i][0]);
		close(state->fds[i][1]);
		i++;
	}
}

static void	ft_check_status(t_state *state, t_cmd *current_cmd)
{
	char	*arg;
	int		i;

	i = 0;
	arg = current_cmd->args[1];
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	while (arg[i])
	{
		if (arg[i] > 57 || arg[i] < 48)
		{
			printf("minishell :exit: %s: numeric argument required\n", arg);
			ft_free_exit(state, 255);
		}
		i++;
	}
}

void	ft_exit(t_state *state, t_cmd *current_cmd)
{
	int	status;

	if (current_cmd->args[1] == NULL)
		ft_free_exit(state, 0);
	else if (current_cmd->args[2] == NULL)
	{
		ft_check_status(state, current_cmd);
		status = ft_atoi(current_cmd->args[1]);
		ft_free_exit(state, status);
	}
	else
		printf("minishell: exit: too many arguments\n");
}
