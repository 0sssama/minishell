/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olabrahm <olabrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 19:24:23 by olabrahm          #+#    #+#             */
/*   Updated: 2022/01/11 21:51:40 by olabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(t_state *state)
{
	if (state->current_cmd.num_of_args == 1)
	{
		if (chdir(state->home) == -1)
			perror("cd");
	}
	else if (state->current_cmd.num_of_args == 2)
	{
		if (chdir(state->current_cmd.args[1]) == -1)
			perror(state->current_cmd.args[1]);
	}
}
