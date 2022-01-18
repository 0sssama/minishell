/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olabrahm <olabrahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 14:40:02 by olabrahm          #+#    #+#             */
/*   Updated: 2021/11/07 09:20:51 by olabrahm         ###   ########.fr       */
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
	if (s[i] == to_find)
		return ((char *)(s + i));
	return (0);
}
