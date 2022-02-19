/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouadel <obouadel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 09:05:39 by olabrahm          #+#    #+#             */
/*   Updated: 2022/02/19 19:13:16 by obouadel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_state	g_state;

void	ft_handle_sigquit(int signal)
{
	(void) signal;
	if (g_state.pid > 0)
	{
		kill(g_state.pid, SIGTERM);
		g_state.pid = -1;
	}
	else
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

void	ft_handle_sigint(int signal)
{
	(void) signal;
	write(1, "\n", 1);
	if (g_state.pid > 0)
		kill(g_state.pid, SIGINT);
	if (g_state.pid == -1)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

int	main(int ac, char **av, char **env)
{
	(void) av;
	(void) ac;
	g_state.line = NULL;
	g_state.man_err = 0;
	g_state.envtab = env;
	g_state.env = ft_setup_env(env);
	if (g_state.env)
	{
		g_state.home = ft_get_env(&g_state.env, "HOME");
		g_state.path = ft_get_env(&g_state.env, "PATH");
	}
	g_state.pid = -1;
	g_state.status = 0;
	g_state.oldpwd = NULL;
	g_state.pwd = NULL;
	ft_prompt(&g_state);
	ft_free_exit(&g_state, 0);
	return (0);
}

// signals	[X]
// syntax	[|]
// files	[ ]
