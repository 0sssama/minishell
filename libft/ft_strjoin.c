/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olabrahm <olabrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 12:25:24 by olabrahm          #+#    #+#             */
/*   Updated: 2022/03/09 11:54:18 by olabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*output;
	size_t	j;
	size_t	i;
	size_t	final_len;
	int		should_free;

	if (!s2)
		return (ft_strdup(s1));
	should_free = !s1;
	if (!s1)
		s1 = ft_strdup("");
	final_len = ft_strlen(s1) + ft_strlen(s2);
	output = (char *) malloc((final_len + 1) * sizeof(char));
	if (!output)
		return (0);
	i = 0;
	j = 0;
	while (s1[j])
		output[i++] = s1[j++];
	j = 0;
	while (s2[j])
		output[i++] = s2[j++];
	output[i] = 0;
	if (should_free)
		free(s1);
	return (output);
}
