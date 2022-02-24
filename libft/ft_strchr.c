/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouadel <obouadel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 14:40:02 by olabrahm          #+#    #+#             */
/*   Updated: 2022/02/23 16:10:47 by obouadel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	to_find;
	int		i;

	i = 0;
	to_find = (char) c;
	while (s[i])
	{
		if (s[i] == to_find)
			return ((char *)(s + i));
		i++;
	}
	return (0);
}
