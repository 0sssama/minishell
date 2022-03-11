/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olabrahm <olabrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 16:00:50 by obouadel          #+#    #+#             */
/*   Updated: 2022/03/11 11:19:29 by olabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		ft_free_exit(state, OUT_OF_MEM);
	state->status = 258;
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
			new_str = ft_charjoin(new_str, old_str[i++]);
		i++;
		if (!old_str[i])
			break ;
		if (old_str[i] && ft_isdigit(old_str[i]))
		{
			i++;
			continue ;
		}
		while (old_str[i] && (ft_isalnum(old_str[i]) || old_str[i] == '_'))
			env_name = ft_charjoin(env_name, old_str[i++]);
		if (!env_name && old_str[i])
			new_str = ft_charjoin(new_str, '$');
		else
		{
			env = ft_get_env(&state->env, env_name);
			free(env_name);
			env_name = NULL;
			if (!env)
				new_str = ft_strjoin_osm(new_str, "");
			else if (ft_is_literal_wildcard(env->value) && !new_str)
				new_str = ft_charjoin(new_str, WILDCARD);
			else
				new_str = ft_strjoin_osm(new_str, env->value);
		}
	}
	return (new_str);
}

static char	**ft_expand(t_state *state, char **cmd)
{
	unsigned int	i;
	char			**output;
	char			*tmp;

	i = 0;
	output = NULL;
	tmp = NULL;
	while (cmd[i])
	{
		if (ft_strchr(cmd[i], ENV_SIGN))
		{
			tmp = ft_expand_str(state, cmd[i]);
			output = ft_add_arg(output, tmp);
			free(tmp);
		}
		else if (ft_strchr(cmd[i], EXIT_STATUS))
		{
			tmp = ft_put_exitcode(state, cmd[i]);
			output = ft_add_arg(output, tmp);
			free(tmp);
		}
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
		ft_free_exit(state, OUT_OF_MEM);
	syntax_code = ft_check_syntax(cmd, state->line);
	if (syntax_code != 0) // checking for syntax errors
		return (ft_put_syntax_error(state, syntax_code));
	cmd = ft_expand(state, cmd); // expands $
	cmd = ft_replace_wildcard(state, cmd); // replaces arg or WILDCARD with wildcard elements
	return (cmd);
}
