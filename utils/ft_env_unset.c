/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olabrahm <olabrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 19:26:20 by olabrahm          #+#    #+#             */
/*   Updated: 2022/01/15 16:31:35 by olabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_freenode(t_env_var *node)
{
	ft_free_matrix(node->both);
	free(node);
}

void	ft_lstdelone(t_state *state, t_env_var *elem)
{
	t_env_var	*current_node;
	t_env_var	*before;

	if (!(state->env) || !elem)
		return ;
	current_node = (state->env);
	before = NULL;
	while (current_node)
	{
		if (current_node == elem)
		{
			if (!before)
			{
				state->env = current_node->next;
				ft_freenode(current_node);
				ft_setup_indexes(state->env);
				return ;
			}
			before->next = current_node->next;
			ft_freenode(current_node);
			ft_setup_indexes(state->env);
			return ;
		}
		before = current_node;
		current_node = current_node->next;
	}
}

static void	ft_env_del(t_state *state, char *name)
{
	t_env_var	*var;

	var = ft_get_env(&state->env, name);
	if (!var)
		return ;
	ft_lstdelone(state, var);
}

void	ft_env_unset(t_state *state)
{
	unsigned int	i;

	i = 0;
	if (state->current_cmd.num_of_args == 1)
		return ;
	while (state->current_cmd.args[++i])
	{
		if (ft_get_env(&state->env, state->current_cmd.args[i]))
			ft_env_del(state, state->current_cmd.args[i]);
	}
}
