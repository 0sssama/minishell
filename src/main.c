/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouadel <obouadel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 09:05:39 by olabrahm          #+#    #+#             */
/*   Updated: 2022/03/04 18:13:05 by obouadel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_state	g_state;

void	ft_handle_sigquit(int signal)
{
	(void) signal;
	if (g_state.pid > 0)
	{
		write(2, "Quit: 3\n", 8);
		kill(g_state.pid, SIGQUIT);
		g_state.pid = -1;
		g_state.sig = SIGQUIT;
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
	write(2, "\n", 1);
	if (g_state.pid > 0)
	{
		kill(g_state.pid, SIGINT);
		g_state.pid = -1;
		g_state.sig = SIGINT;
	}
	else
	{
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

static void	ft_init_main(char **env)
{
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
	g_state.sig = 0;
}

int	main(int ac, char **av, char **env)
{
	(void) av;
	(void) ac;
	ft_init_main(env);
	signal(SIGINT, ft_handle_sigint);
	signal(SIGQUIT, ft_handle_sigquit);
	ft_prompt(&g_state);
	ft_free_exit(&g_state, 0);
	return (0);
}

// signals	[X]
// syntax	[|]
// files	[ ]

/*

	-> Add quit 3
------------------------------
	-> tokenization [need to token operators, > < >> << | || &&]

	-> expand

	-> parse tree
	
	-> Syntax
		- if ( | ) are in the beginning or end
		- if (> - < - << - >>) are in the end
		- unclosed quote

	token = 0
*/