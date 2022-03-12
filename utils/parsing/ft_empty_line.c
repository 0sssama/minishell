/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_empty_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouadel <obouadel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 14:37:29 by olabrahm          #+#    #+#             */
/*   Updated: 2022/03/12 17:25:16 by obouadel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_empty_line(char *str)
{
	int	i;

	i = -1;
	if (str[0] == 0)
		return (1);
	while (str[++i])
		if (str[i] != ' ' && str[i] != DELIMIT)
			return (0);
	add_history(str);
	return (1);
}
