/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouadel <obouadel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 12:33:14 by olabrahm          #+#    #+#             */
/*   Updated: 2022/01/19 21:47:38 by obouadel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_inset(char c, char *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char *s1, char *set)
{
	size_t	start;
	size_t	end;
	size_t	i;
	char	*output;

	if (!s1)
		return (0);
	if (!set[0])
		return (ft_strdup(s1));
	start = 0;
	while (s1[start] && ft_inset(s1[start], set))
		start++;
	if (start == ft_strlen(s1))
	{
		free(s1);
		return (ft_calloc(1, sizeof(char)));
	}
	end = ft_strlen(s1) - 1;
	while (s1[end] && ft_inset(s1[end], set))
		end--;
	output = (char *) malloc((end - start + 2) * sizeof(char));
	if (!output)
		return (0);
	i = 0;
	while (i < end - (start - i) + 1)
		output[i++] = s1[start++];
	output[i] = 0;
	free((void *) s1);
	return (output);
}
