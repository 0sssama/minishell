/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olabrahm <olabrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 16:00:50 by obouadel          #+#    #+#             */
/*   Updated: 2022/03/07 18:21:29 by olabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void	ft_get_quote(t_state *state, int *q, int *i, char c)
// {
// 	state->line[(*i)++] = QUOTE;
// 	(*q)++;
// 	while (state->line[(*i)] && state->line[(*i)] != c)
// 	{
// 		if (state->line[(*i)] == '$' && c == '"')
// 			ft_get_vars(state, i);
// 		else
// 			(*i)++;
// 	}
// 	if (state->line[(*i)] == c)
// 	{
// 		(*q)++;
// 		state->line[(*i)] = QUOTE;
// 	}
// }

// static int	expand_it(t_state *state)
// {
// 	int	i;
// 	int	quotes;

// 	i = 0;
// 	quotes = 0;
// 	while (state->line[i])
// 	{
// 		if (state->line[i] == 39 || state->line[i] == 34)
// 		{
// 			ft_get_quote(state, &quotes, &i, state->line[i]);
// 			if (!state->line[i])
// 				break ;
// 		}
// 		else if (state->line[i] == '$')
// 			ft_get_vars(state, &i);
// 		i++;
// 	}
// 	if (quotes % 2)
// 		return (0);
// 	return (1);
// }

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

static char	*ft_expand_str(t_state *state, char *old_str)
{
	unsigned int	i;
	char			*new_str;
	char			*env_name;
	t_env_var		*env;

	new_str = NULL;
	env_name = NULL;
	i = 0;
	if (ft_strlen(old_str) == 1)
		return (ft_strdup("$"));
	while (old_str[i])
	{
		while (old_str[i] && old_str[i] != ENV_SIGN)
		{
			new_str = ft_charjoin(new_str, old_str[i]);
			i++;
		}
		i++;
		if (!old_str[i])
			break ;
		if (old_str[i] && ft_isdigit(old_str[i]))
		{
			i++;
			continue ;
		}
		while (old_str[i] && (ft_isalnum(old_str[i]) || old_str[i] == '_'))
		{
			env_name = ft_charjoin(env_name, old_str[i]);
			i++;
		}
		if (!env_name && old_str[i])
			new_str = ft_charjoin(new_str, '$');
		else
		{
			env = ft_get_env(&state->env, env_name);
			if (!env)
			{
				new_str = ft_strjoin(new_str, "");
				continue ;
			}
			new_str = ft_strjoin(new_str, env->value);
			free(env_name);
			env_name = NULL;
		}
	}
	return (new_str);
}

static char	**ft_expand(t_state *state, char **cmd)
{
	unsigned int	i;
	char			**output;
	
	i = 0;
	output = NULL;
	while (cmd[i])
	{
		if (ft_strchr(cmd[i], ENV_SIGN))
			output = ft_add_arg(output, ft_expand_str(state, cmd[i]));
		else
			output = ft_add_arg(output, cmd[i]);
		i++;
	}
	ft_free_matrix(cmd);
	return (output);
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
	cmd = ft_expand(state, cmd); // expands $
	return (cmd);
}
