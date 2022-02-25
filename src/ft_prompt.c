/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olabrahm <olabrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 15:07:26 by olabrahm          #+#    #+#             */
/*   Updated: 2022/02/25 17:23:15 by olabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_lexer(char *line)
{
	int i;

	i = -1;
	while (line[++i])
	{
		if (line[i] == PIPE)
			printf("PIPE");
		else if (line[i] == REDIN)
			printf("REDIN");
		else if (line[i] == REDOUT)
			printf("REDOUT");
		else if (line[i] == APPEND)
			printf("APPEND");
		else if (line[i] == HEREDOC)
			printf("HEREDOC");
		else if (line[i] == DELIMIT)
			printf("SPACE");
		else if (line[i] == QUOTE)
			printf("QUOTE");
		else
			printf("%c", line[i]);
	}
	printf("\n");
}

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
	int		i;

	add_history(state->line);
	cmd = ft_clean_args(state); // tokenizer
	if (!cmd && state->man_err)
		return ;
	ft_lexer(state->line);
	i = 0;
	while (cmd[i])
		i++;
	// here put parse tree :)
	state->current_cmd.name = ft_lowerstr(cmd[0]);
	state->current_cmd.args = cmd;
	state->current_cmd.num_of_args = i;
}

void	ft_prompt(t_state *state)
{
	signal(SIGINT, ft_handle_sigint);
	signal(SIGQUIT, ft_handle_sigquit);
	while (1)
	{
		state->man_err = 0;
		state->pid = -1;
		state->sig = 0;
		state->line = readline("\033[1mminishell-1.0$> \033[m");
		rl_on_new_line();
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
		// ft_execute(state);
		free(state->line);
	}
}
