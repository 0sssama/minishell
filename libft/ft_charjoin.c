/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_charjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olabrahm <olabrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 09:57:51 by olabrahm          #+#    #+#             */
/*   Updated: 2022/03/01 09:50:54 by olabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_charjoin(char *s1, char c)
{
	unsigned int	i;
	char			*output;

	if (!s1)
	{
		output = (char *) malloc(2 * sizeof(char));
		if (!output)
			return (NULL);
		output[0] = c;
		output[1] = 0;
		return (output);
	}
	i = 0;
	output = (char *) malloc((ft_strlen(s1) + 2) * sizeof(char));
	if (!output)
		return (NULL);
	while (s1[i])
	{
		output[i] = s1[i];
		i++;
	}
	output[i++] = c;
	output[i] = '\0';
	free(s1);
	s1 = NULL;
	return (output);
}
