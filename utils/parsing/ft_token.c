/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olabrahm <olabrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 15:11:26 by obouadel          #+#    #+#             */
/*   Updated: 2022/03/02 21:00:15 by olabrahm         ###   ########.fr       */
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

	quote = line[*i];
	(*i)++;
	while (line[*i] && line[*i] != quote)
		(*i)++;
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
	(*i)++;
}

int	ft_token(char *line)
{
	unsigned int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '"' || line[i] == '\'')
			ft_end_quote(line, &i);
		else if (ft_strchr("<>|", line[i]))
			ft_replace_opp(line, &i);
		else if (line[i] == ' ')
			line[i++] = DELIMIT;
		else
			i++;
	}
	return (1);
}
