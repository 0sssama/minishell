/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olabrahm <olabrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 19:23:13 by olabrahm          #+#    #+#             */
/*   Updated: 2022/03/16 10:29:08 by olabrahm         ###   ########.fr       */
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

void	ft_echo(t_state *state, t_cmd *current_cmd)
{
	int	i;

	i = 1;
	if (current_cmd->num_of_args >= 2)
	{
		if (!ft_strncmp(current_cmd->args[i], "-n", 3))
		{
			while (current_cmd->args[i] && !ft_strncmp(current_cmd->args[i], "-n", 3))
				i++;
			if (current_cmd->num_of_args < 3)
				return ;
			ft_print(current_cmd->args, i);
			return ;
		}
		ft_print(current_cmd->args, 1);
	}
	printf("\n");
	state->status = 0;
}
