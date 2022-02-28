/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_args.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olabrahm <olabrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 13:25:30 by olabrahm          #+#    #+#             */
/*   Updated: 2022/02/26 15:48:08 by olabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned int	ft_args_len(char **args)
{
	unsigned int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

char	**ft_init_args(char *init)
{
	char			**output;
	int				len;

	len = 2 - (init == NULL); // if init is null, will only allocate one for null terminator.
	output = (char **) malloc(len * sizeof(char *));
	if (!output)
		return (NULL);
	if (len == 1)
	{
		output[0] = NULL;
		return (output);
	}
	output[0] = ft_strdup(init);
	if (!output[0])
		return (NULL);
	output[1] = NULL;
	return (output);
}

char	**ft_add_arg(char **args, char *new_arg)
{
	unsigned int	i;
	unsigned int	len;
	char			**new_args;

	i = 0;
	if (!args)
		return (NULL);
	len = ft_args_len(args) + 2; // plus new arg, and null terminator
	new_args = (char **) malloc(len * sizeof(char *));
	while (args[i])
	{
		new_args[i] = ft_strdup(args[i]);
		if (!new_args[i])
			return (NULL);
		i++;
	}
	new_args[i++] = ft_strdup(new_arg);
	if (!new_args[i - 1])
		return (NULL);
	new_args[i] = NULL;
	printf("got here 1\n");
	ft_free_matrix(args);
	printf("got here 2\n");
	return (new_args);
}
