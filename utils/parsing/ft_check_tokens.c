/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olabrahm <olabrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 09:28:58 by olabrahm          #+#    #+#             */
/*   Updated: 2022/03/11 11:19:06 by olabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**ft_split_token(char *str)
{
	unsigned int	i;
	char			**output;
	char			*tmp;

	i = 0;
	output = NULL;
	tmp = NULL;
	while (str[i])
	{
		while (str[i] && !ft_istoken(str[i]))
		{
			tmp = ft_charjoin(tmp, str[i++]);
			if (!tmp)
				return (NULL);
		}
		if (tmp)
		{
			output = ft_add_arg(output, tmp);
			free(tmp);
			tmp = NULL;
		}
		while (str[i] && ft_istoken(str[i]))
		{
			if (tmp && tmp[0] != APPEND && tmp[0] != HEREDOC)
				break ;
			if (tmp && (tmp[0] == APPEND || tmp[0] == HEREDOC) && ft_strlen(tmp) == 2)
				break ;
			tmp = ft_charjoin(tmp, str[i++]);
			if (!tmp)
				return (NULL);
		}
		if (tmp)
		{
			output = ft_add_arg(output, tmp);
			free(tmp);
			tmp = NULL;
		}
	}
	return (output);
}

int	ft_is_literal_wildcard(char *str)
{
	unsigned int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '*')
			return (0);
		i++;
	}
	return (1);
}

int	ft_is_wildcard(char *str)
{
	unsigned int	i;

	if (!str || !str[0])
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] != WILDCARD)
			return (0);
		i++;
	}
	return (1);
}

char	**ft_check_tokens(char **cmd)
{
	unsigned int	i;
	char			**output;
	char			**split_arg;

	i = 0;
	output = NULL;
	split_arg = NULL;
	if (!cmd)
		return (NULL);
	while (cmd[i])
	{
		if (!ft_contains_token(cmd[i]))
		{
			output = ft_add_arg(output, cmd[i]);
			if (!output)
				return (NULL);
		}
		else
		{
			split_arg = ft_split_token(cmd[i]);
			if (!split_arg)
				return (NULL);
			output = ft_merge_args(output, split_arg);
			if (!output)
				return (NULL);
		}
		i++;
	}
	ft_free_matrix(cmd);
	return (output);
}
