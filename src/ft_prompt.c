/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olabrahm <olabrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 15:07:26 by olabrahm          #+#    #+#             */
/*   Updated: 2022/03/11 12:49:51 by olabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_empty_line(char *str)
{
	int	i;

	i = -1;
	if (str[0] == 0)
		return (1);
	while (str[++i])
		if (str[i] != ' ' && str[i] != DELIMIT)
			return (0);
	return (1);
}

static void	ft_parse(t_state *state)
{
	char	**cmd;

	add_history(state->line);
	cmd = ft_clean_args(state);
	if (!cmd && state->man_err)
		return ;
	state->cmd_tree = ft_parse_tree(cmd);
	if (!state->cmd_tree)
	{
		state->man_err = 1;
		ft_free_tree(&state->cmd_tree);
	}
}

static void	ft_init_loop(t_state *state)
{
	state->cmd_tree = NULL;
	state->man_err = 0;
	state->pid = -1;
	state->sig = 0;
	state->line = readline("\033[1mminishell-1.9$> \033[m");
	rl_on_new_line();
}

void	ft_prompt(t_state *state)
{
	while (69)
	{
		signal(SIGINT, ft_handle_sigint_parent);
		signal(SIGQUIT, SIG_IGN);
		ft_init_loop(state);
		if (!state->line)
			break ;
		if (ft_empty_line(state->line))
		{
			state->status = 0;
			free(state->line);
			continue ;
		}
		ft_parse(state);
		if (state->man_err)
		{
			state->status = 258;
			free(state->line);
			continue ;
		}
		signal(SIGINT, SIG_IGN);
		ft_save_io(state);
		ft_execution(state);
		free(state->line);
		ft_free_tree(&state->cmd_tree);
		ft_reset_io(state);
		ft_update_env(state);
	}
}
