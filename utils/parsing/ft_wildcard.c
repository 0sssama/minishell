/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildcard.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouadel <obouadel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 15:28:11 by obouadel          #+#    #+#             */
/*   Updated: 2022/03/04 13:57:07 by obouadel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//token WILDCARD

static void	ft_fill_wildcard(struct dirent *dir, char *wildcard)
{
	char	*temp;

	temp = NULL;
	if (!wildcard)
		wildcard = ft_strdup(dir->d_name);
	else
	{
		temp = wildcard;
		wildcard = ft_strjoin(wildcard, " ");
		free(temp);
		temp = wildcard;
		wildcard = ft_strjoin(wildcard, dir->d_name);
		free(temp);
	}
}

char	*ft_wildcard(char *str)
{
	char			*wildcard;
	DIR				*directory;
	struct dirent	*dir;

	directory = opendir(".");
	wildcard = NULL;
	if (!directory)
		return (str);
	while (1337)
	{
		dir = readdir(directory);
		if (!directory)
			break ;
		ft_fill_wildcard(dir, wildcard);
	}
	closedir(directory);
	//free(str); if u want to replace the old str with the wildcard
	return (wildcard);
}
