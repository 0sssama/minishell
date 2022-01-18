/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olabrahm <olabrahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 13:21:58 by olabrahm          #+#    #+#             */
/*   Updated: 2021/11/07 09:24:35 by olabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	to_find;
	int		i;

	to_find = (char) c;
	i = ft_strlen(s);
	while (i >= 0)
	{
		if (s[i] == to_find)
			return ((char *)&s[i]);
		i--;
	}
	return (0);
}
