/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildcard.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olabrahm <olabrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 15:28:11 by obouadel          #+#    #+#             */
/*   Updated: 2022/03/11 11:18:52 by olabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_contains_wildcard(char **cmd)
{
	unsigned int	i;

	i = 0;
	while (cmd[i])
	{
		if (ft_is_wildcard(cmd[i]))
			return (1);
		i++;
	}
	return (0);
}

char	**ft_replace_wildcard(t_state *state, char **cmd)
{
	unsigned int	i;
	char			**output;
	char			**wildcard;

	output = NULL;
	if (!cmd)
		return (ft_free_exit(state, OUT_OF_MEM), NULL);
	if (!ft_contains_wildcard(cmd))
		return (cmd);
	i = 0;
	while (cmd[i])
	{
		if (ft_is_wildcard(cmd[i]))
		{
			wildcard = ft_wildcard();
			if (!wildcard)
				output = ft_add_arg(output, cmd[i]);
			else
				output = ft_merge_args(output, wildcard);
		}
		else
			output = ft_add_arg(output, cmd[i]);
		i++;
	}
	ft_free_matrix(cmd);
	return (output);
}

char	**ft_wildcard(void)
{
	struct dirent	*dir;
	char			**wildcard;
	DIR				*directory;

	wildcard = NULL;
	directory = opendir(".");
	if (!directory)
		return (NULL);
	while (1337)
	{
		dir = readdir(directory);
		if (!dir)
			break ;
		if (dir->d_name[0] != '.')
			wildcard = ft_add_arg(wildcard, dir->d_name);
	}
	closedir(directory);
	return (wildcard);
}
