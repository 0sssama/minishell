/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olabrahm <olabrahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 08:38:46 by olabrahm          #+#    #+#             */
/*   Updated: 2021/11/08 14:10:04 by olabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*casted_s1;
	unsigned char	*casted_s2;
	size_t			i;

	if (n == 0)
		return (0);
	casted_s1 = (unsigned char *) s1;
	casted_s2 = (unsigned char *) s2;
	i = 0;
	while (casted_s1[i] == casted_s2[i] && i < n - 1)
		i++;
	return (casted_s1[i] - casted_s2[i]);
}
