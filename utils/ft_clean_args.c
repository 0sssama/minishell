/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouadel <obouadel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 16:00:50 by obouadel          #+#    #+#             */
/*   Updated: 2022/02/19 16:13:25 by obouadel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_get_quote(t_state *state, int *q, int *i, char c)
{
	state->line[(*i)++] = QUOTE;
	(*q)++;
	while (state->line[(*i)] && state->line[(*i)] != c)
	{
		if (state->line[(*i)] == '$' && c == '"')
			ft_get_vars(state, i);
		else
			(*i)++;
	}
	if (state->line[(*i)] == c)
	{
		(*q)++;
		state->line[(*i)] = QUOTE;
	}
}

static int	token_it(t_state *state)
{
	int	i;
	int	quotes;

	i = 0;
	quotes = 0;
	while (state->line[i])
	{
		if (state->line[i] == 39 || state->line[i] == 34)
		{
			ft_get_quote(state, &quotes, &i, state->line[i]);
			if (!state->line[i])
				break ;
		}
		else if (state->line[i] == '$')
			ft_get_vars(state, &i);
		else if (state->line[i] == ' ')
			state->line[i] = DELIMIT;
		i++;
	}
	if (quotes % 2)
		return (0);
	return (1);
}

char	**ft_clean_args(t_state *state)
{
	char	**cmd;

	if (!token_it(state))
	{
		printf("minishell: Unclosed quotes\n");
		state->man_err = 1;
		return (NULL);
	}
	if (ft_empty_line(state->line))
	{
		state->man_err = 1;
		return (NULL);
	}
	cmd = ft_split_args(state->line, DELIMIT);
	if (!cmd)
		ft_free_exit(state, 12);
	return (cmd);
}
