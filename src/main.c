/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olabrahm <olabrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 09:05:39 by olabrahm          #+#    #+#             */
/*   Updated: 2022/03/09 14:19:29 by olabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_state	g_state;

void	ft_handle_sigquit(int signal)
{
	(void) signal;
	write(2, "Quit: 3\n", 8);
}

void	ft_handle_sigint(int signal)
{
	(void) signal;
	write(2, "\n", 1);
}

static void	ft_init_main(char **env)
{
	g_state.line = NULL;
	g_state.man_err = 0;
	g_state.env = ft_setup_env(env);
	if (g_state.env)
	{
		g_state.home = ft_get_env(&g_state.env, "HOME");
		g_state.path = ft_get_env(&g_state.env, "PATH");
	}
	g_state.envtab = ft_update_envtab(&g_state);
	g_state.pid = -1;
	g_state.status = 0;
	g_state.oldpwd = NULL;
	g_state.pwd = getcwd(NULL, PATH_MAX);
	g_state.sig = 0;
}

int	main(int ac, char **av, char **env)
{
	(void) av;
	(void) ac;
	ft_init_main(env);
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