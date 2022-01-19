/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_addfront.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olabrahm <olabrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 17:53:35 by olabrahm          #+#    #+#             */
/*   Updated: 2022/01/18 18:34:28 by olabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env_addfront(t_env_var **head, char **new)
{
	t_env_var	*var;
	char		*name;
	char		*value;
	char		*temp_value;

	name = new[0];
	name[ft_strlen(new[0]) - 1] = '\0';
	value = new[1];
	var = ft_get_env(head, name);
	if (!var)
		return ;
	temp_value = ft_strdup(value);
	free(value);
	value = ft_strjoin(var->value, temp_value);
	free(temp_value);
	free(var->value);
	free(var->name);
	free(var->both);
	var->name = name;
	var->value = value;
	var->both = new;
}
