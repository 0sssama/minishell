/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouadel <obouadel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 15:11:26 by obouadel          #+#    #+#             */
/*   Updated: 2022/02/24 16:59:21 by obouadel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_check_redin(char *line, int *i)
{
	if (line[*i] == '<' && line[*i + 1] == '<')
	{
		if (line[*i + 2] == '<')
			return (ft_put_error(NULL, \
				"syntax error near unexpected token `<'\n"), 0);
		line[*i] = HEREDOC;
		line[*i + 1] = HEREDOC;
	}
	if (line[*i] == '<')
		line[(*i)++] = REDIN;
	return (1);
}

static int	ft_check_redout(char *line, int *i)
{
	if (line[(*i)] == '>' && line[(*i) + 1] == '>')
	{
		if (line[(*i) + 2] == '>')
			return (ft_put_error(NULL, \
				"syntax error near unexpected token `>'\n"), 0);
		line[(*i)++] = APPEND;
		line[(*i)++] = APPEND;
	}
	if (line[(*i)] == '>')
		line[(*i)++] = REDOUT;
	return (1);
}

static void	ft_end_quote(char *line, int *i)
{
	int	quote;

	quote = *i;
	while (line[*i] && line[*i] != quote)
		(*i)++;
}

static int	ft_replace_opp(char *line, int *i)
{
	if (line[*i] == '>')
		return (ft_check_redout(line, i));
	else if (line[*i] == '<')
		return (ft_check_redin(line, i));
	else if (line[*i] == '|')
	{	
		if (line[*i + 1] == '|')
			return (ft_put_error(NULL, \
				"syntax error near unexpected token `|'\n"), 0);
		line[(*i)++] = PIPE;
	}
	return (1);
}

int	ft_token(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '"')
			ft_end_quote(line, &i);
		else if (ft_strchr("<>|", line[i]))
		{
			if (!ft_replace_opp(line, &i))
				return (0);
		}
		else if (line[i] == ' ')
			line[i++] = DELIMIT;
		else
			i++;
	}
	return (1);
}
