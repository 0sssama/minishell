/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olabrahm <olabrahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 13:28:09 by olabrahm          #+#    #+#             */
/*   Updated: 2021/11/05 13:49:56 by olabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*casted_dst;
	unsigned char	*casted_src;
	size_t			i;

	i = 0;
	casted_dst = (unsigned char *)dst;
	casted_src = (unsigned char *)src;
	if (dst == 0 && src == 0)
		return (0);
	while (i < n)
	{
		*(casted_dst + i) = *(casted_src + i);
		i++;
	}
	return (dst);
}
