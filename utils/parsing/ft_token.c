/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olabrahm <olabrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 15:11:26 by obouadel          #+#    #+#             */
/*   Updated: 2022/03/03 18:23:37 by olabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	The functions below are removed because they interfere syntax errors
	with tokenization. Our parsing process will completely tokenize the entire
	line, and then check syntax errors right after that.
	We don't want to do both at the same time.
*/

// static int	ft_check_redin(char *line, int *i)
// {
// 	if (line[*i] == '<' && line[*i + 1] == '<')
// 	{
// 		if (line[*i + 2] == '<')
// 			return (ft_put_error(NULL, \
// 				"syntax error near unexpected token `<'\n"), 0);
// 		line[*i] = HEREDOC;
// 		line[*i + 1] = HEREDOC;
// 	}
// 	if (line[*i] == '<')
// 		line[(*i)++] = REDIN;
// 	return (1);
// }

// static int	ft_check_redout(char *line, int *i)
// {
// 	if (line[(*i)] == '>' && line[(*i) + 1] == '>')
// 	{
// 		if (line[(*i) + 2] == '>')
// 			return (ft_put_error(NULL, \
// 				"syntax error near unexpected token `>'\n"), 0);
// 		line[(*i)++] = APPEND;
// 		line[(*i)++] = APPEND;
// 	}
// 	if (line[(*i)] == '>')
// 		line[(*i)++] = REDOUT;
// 	return (1);
// }

// static int	ft_replace_opp(char *line, int *i)
// {
// 	if (line[*i] == '>')
// 		return (ft_check_redout(line, i));
// 	else if (line[*i] == '<')
// 		return (ft_check_redin(line, i));
// 	else if (line[*i] == '|')
// 	{	
// 		if (line[*i + 1] == '|')
// 			return (ft_put_error(NULL, \
// 				"syntax error near unexpected token `||'\n"), 0);
// 		line[(*i)++] = PIPE;
// 	}
// 	return (1);
// }

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
