/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olabrahm <olabrahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:30:04 by olabrahm          #+#    #+#             */
/*   Updated: 2021/11/04 17:11:20 by olabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*casted_dst;
	unsigned char	*casted_src;

	casted_dst = (unsigned char *)dst;
	casted_src = (unsigned char *)src;
	if (dst > src && dst < src + len)
	{
		while (len--)
			*(casted_dst + len) = *(casted_src + len);
	}
	else
		ft_memcpy(dst, src, len);
	return (dst);
}
