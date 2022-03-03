/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olabrahm <olabrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 16:00:50 by obouadel          #+#    #+#             */
/*   Updated: 2022/03/03 10:25:57 by olabrahm         ###   ########.fr       */
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

static int	expand_it(t_state *state)
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
		i++;
	}
	if (quotes % 2)
		return (0);
	return (1);
}

static char	**set_man_err_null(t_state *state)
{
	state->man_err = 1;
	return (NULL);
}

static char	**ft_put_syntax_error(t_state *state, int syntax_code)
{
	char	*message;

	if (syntax_code == 1)
		message = ft_strdup("syntax error due to unclosed quotes\n");
	else if (syntax_code == 2)
		message = ft_strdup("syntax error near unexpected token\n");
	else
		message = ft_strdup("VERY unexpected error occurred.\n");
	if (!message)
		ft_free_exit(state, 12);
	ft_put_error(NULL, message);
	free(message);
	message = NULL;
	return (set_man_err_null(state));
}

char	**ft_clean_args(t_state *state)
{
	char	**cmd;
	int		syntax_code;

	if (ft_empty_line(state->line)) // checks if line empty
		return (set_man_err_null(state));
	ft_token(state->line); // tokenization
	cmd = ft_split_args(state->line, DELIMIT);
	// not checking if ft_split_args returned null, cuz
	// ft_check_tokens already does that!
	cmd = ft_check_tokens(cmd); // checks if there are tokens not separated by delimit
	if (!cmd)
		ft_free_exit(state, 12);
	syntax_code = ft_check_syntax(cmd, state->line);
	if (syntax_code != 0) // checking for syntax errors
		return (ft_put_syntax_error(state, syntax_code));
	if (!expand_it(state)) // expands $, removes quotes
		return (set_man_err_null(state));
	return (cmd);
}
