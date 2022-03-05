/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_syntax.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olabrahm <olabrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 19:02:09 by olabrahm          #+#    #+#             */
/*   Updated: 2022/03/03 10:25:38 by olabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_correct_quotes(char *line)
{
	unsigned int	i;
	int				count;

	i = 0;
	count = 0;
	if (!line)
		return (0);
	while (line[i])
	{
		if (line[i] == QUOTE)
			count++;
		i++;
	}
	return (count % 2 == 0);
}

static int	ft_get_token(char *str)
{
	if (!str)
		return (0);
	if (ft_istoken(str[0]) && (!str[1] || (str[0] == str[1] && !str[2])))
		return (str[0]);
	return (0);
}

/*
	DEV NOTE: meaning of each ft_check_syntax return code
	sorry for the hard code, its syntax checking for fuckssake.

	0: success;
	1: unclosed quotes; (ft_correct_quotes())
	2: syntax error near unexpected token;
	99: something unexpected;
*/
int	ft_check_syntax(char **cmd, char *line)
{
	unsigned int	i;

	i = 0;
	if (!cmd || !cmd[0])
		return (99);
	if (!ft_correct_quotes(line))
		return (1);
	while (cmd[i])
	{
		if (ft_contains_token(cmd[i]) && !cmd[i + 1])
			return (2);
		if ((ft_get_token(cmd[i]) == REDOUT || ft_get_token(cmd[i]) == REDIN)
			&& ft_contains_token(cmd[i + 1]))
			return (2);
		if (ft_get_token(cmd[i]) == PIPE
			&& ft_contains_token(cmd[i + 1]) && ft_get_token(cmd[i + 1]) == REDOUT)
			return (2);
		if (ft_get_token(cmd[i]) != 0 && ft_get_token(cmd[i]) == ft_get_token(cmd[i + 1]))
			return (2);
		if (ft_get_token(cmd[i]) == HEREDOC && ft_get_token(cmd[i + 1]) == APPEND)
			return (2);
		if (ft_get_token(cmd[i]) == REDIN && ft_get_token(cmd[i]) == REDOUT)
			return (2);
		if (ft_contains_token(cmd[i]) && ft_get_token(cmd[i + 1]) == PIPE)
			return (2);
		i++;
	}
	return (0);
}
