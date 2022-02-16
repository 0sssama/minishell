/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouadel <obouadel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 19:25:48 by olabrahm          #+#    #+#             */
/*   Updated: 2022/02/16 15:44:25 by obouadel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env_var	*ft_get_env(t_env_var **head, char *name)
{
	t_env_var	*current_node;
	int			adding;

	if (!head || !(*head))
		return (NULL);
	adding = 0;
	if (name[ft_strlen(name) - 1] == '+')
	{
		adding = 1;
		name[ft_strlen(name) - 1] = '\0';
	}
	current_node = *head;
	while (current_node)
	{
		if (!ft_strcmp(current_node->name, name))
		{
			if (adding)
				name[ft_strlen(name)] = '+';
			return (current_node);
		}
		current_node = current_node->next;
	}
	if (adding)
		name[ft_strlen(name)] = '+';
	return (NULL);
}

static void	ft_print_env(t_state *state)
{
	t_env_var	*current_node;

	current_node = state->env;
	while (current_node)
	{
		printf("%s=%s\n", current_node->name, current_node->value);
		current_node = current_node->next;
	}
}

void	ft_env(t_state *state)
{
	if (state->current_cmd.num_of_args == 1)
	{
		ft_print_env(state);
		state->status = 0;
	}
}
