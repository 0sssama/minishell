/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouadel <obouadel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 16:49:10 by obouadel          #+#    #+#             */
/*   Updated: 2022/02/15 20:35:30 by obouadel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_check_status(t_state *state)
{
	char	*arg;
	int		i;

	i = 0;
	arg = state->current_cmd.args[1];
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	while (arg[i])
	{
		if (arg[i] > 57 || arg[i] < 48)
		{
			printf("minishell :exit: %s: numeric argument required\n", arg);
			ft_free_cmd(state);
			ft_free_exit(state, 255);
		}
		i++;
	}
}

void	ft_exit(t_state *state)
{
	int	status;

	if (state->current_cmd.args[1] == NULL)
	{
		ft_free_cmd(state);
		ft_free_exit(state, 0);
	}
	else if (state->current_cmd.args[2] == NULL)
	{
		ft_check_status(state);
		status = ft_atoi(state->current_cmd.args[1]);
		ft_free_cmd(state);
		ft_free_exit(state, status);
	}
	else
		printf("minishell: exit: too many arguments\n");
}
