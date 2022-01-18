/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olabrahm <olabrahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 17:25:36 by olabrahm          #+#    #+#             */
/*   Updated: 2021/11/07 07:26:08 by olabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*casted_s;
	unsigned char	to_find;

	to_find = (unsigned char) c;
	casted_s = (unsigned char *) s;
	while (n--)
	{
		if (*casted_s == to_find)
			return ((void *) casted_s);
		casted_s++;
	}
	return (0);
}
