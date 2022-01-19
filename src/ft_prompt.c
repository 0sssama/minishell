/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olabrahm <olabrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 15:07:26 by olabrahm          #+#    #+#             */
/*   Updated: 2022/01/19 09:34:28 by olabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_fill(t_state *state)
{
	char	**cmd;
	int		i;

	cmd = ft_clean_args(state);
	if (!cmd && state->man_err)
		return ;
	if (!cmd)
		ft_free_exit(state, 12);
	i = 0;
	while (cmd[i])
		i++;
	state->current_cmd.name = cmd[0];
	state->current_cmd.args = cmd;
	state->current_cmd.num_of_args = i;
}

void	ft_prompt(t_state *state)
{
	state->line = NULL;
	signal(SIGINT, ft_handle_sigint);
	signal(SIGQUIT, ft_handle_sigquit);
	while (1)
	{
		state->man_err = 0;
		state->pid = -1;
		state->line = readline("\033[1mminishell-1.1$> \033[m");
		rl_on_new_line();
		if (!state->line)
			break ;
		if (!state->line[0])
		{
			free(state->line);
			continue ;
		}
		add_history(state->line);
		ft_fill(state);
		if (state->man_err)
		{
			free(state->line);
			continue ;
		}
		ft_execute(state);
		free(state->line);
	}
}
