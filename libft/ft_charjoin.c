/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_charjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouadel <obouadel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 09:57:51 by olabrahm          #+#    #+#             */
/*   Updated: 2022/01/16 15:40:58 by obouadel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_charjoin(char *s1, char c)
{
	unsigned int	i;
	char			*output;

	if (!s1)
		return (NULL);
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
