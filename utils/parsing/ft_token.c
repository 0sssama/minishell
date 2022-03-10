/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olabrahm <olabrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 15:11:26 by obouadel          #+#    #+#             */
/*   Updated: 2022/03/10 16:26:59 by olabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	The functions below are removed because they interfere syntax errors
	with tokenization. Our parsing process will completely tokenize the entire
	line, and then check syntax errors right after that.
	We don't want to do both at the same time.
*/

static void	ft_end_quote(char *line, int *i)
{
	char	quote;
	int		replace_env;

	quote = line[*i];
	replace_env = quote == '"';
	line[*i] = QUOTE;
	(*i)++;
	while (line[*i] && line[*i] != quote)
	{
		if (line[*i] == '$' && replace_env)
		{
			if (line[*i + 1] == '?')
			{
				line[*i] = EXIT_STATUS;
				line[*i + 1] = EXIT_STATUS;
				(*i)++;
			}
			else
				line[*i] = ENV_SIGN;
		}
		(*i)++;
	}
	if (!line[*i])
		return ;
	line[*i] = QUOTE;
	(*i)++;
}

static void	ft_replace_opp(char *line, int *i)
{
	if (line[*i] == '|')
		line[*i] = PIPE;
	else if (line[*i] == '<')
	{
		if (line[(*i) + 1] == '<')
		{
			line[*i] = HEREDOC;
			line[(*i) + 1] = HEREDOC;
			(*i)++;
		}
		else
			line[*i] = REDIN;
	}
	else if (line[*i] == '>')
	{
		if (line[(*i) + 1] == '>')
		{
			line[*i] = APPEND;
			line[(*i) + 1] = APPEND;
			(*i)++;
		}
		else
			line[*i] = REDOUT;
	}
	else if (line[*i] == '$')
	{
		if (line[*i + 1] == '?')
		{
			line[*i] = EXIT_STATUS;
			line[*i + 1] = EXIT_STATUS;
			(*i)++;
		}
		else
			line[*i] = ENV_SIGN;
	}
	(*i)++;
}

int	ft_token(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '"' || line[i] == '\'')
			ft_end_quote(line, &i);
		else if (ft_strchr("<>|$", line[i]))
			ft_replace_opp(line, &i);
		else if (line[i] == ' ')
			line[i++] = DELIMIT;
		else
			i++;
	}
	return (1);
}
