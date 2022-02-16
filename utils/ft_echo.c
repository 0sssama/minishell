/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouadel <obouadel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 19:23:13 by olabrahm          #+#    #+#             */
/*   Updated: 2022/02/16 15:41:46 by obouadel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_print(char **array, int starting_from)
{
	int	i;

	i = starting_from;
	while (array[i])
	{
		if (i != starting_from)
			printf(" ");
		printf("%s", array[i++]);
	}
}

void	ft_echo(t_state *state)
{
	if (state->current_cmd.num_of_args >= 2)
	{
		if (!ft_strncmp(state->current_cmd.args[1], "-n", 3))
		{
			if (state->current_cmd.num_of_args < 3)
				return ;
			ft_print(state->current_cmd.args, 2);
			return ;
		}
		ft_print(state->current_cmd.args, 1);
	}
	printf("\n");
	state->status = 0;
}
