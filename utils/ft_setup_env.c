/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setup_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olabrahm <olabrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 11:14:14 by olabrahm          #+#    #+#             */
/*   Updated: 2022/01/18 17:20:32 by olabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static unsigned int	ft_count_smaller(t_env_var *head, t_env_var *node)
{
	t_env_var		*current_node;
	unsigned int	smaller;

	smaller = 0;
	current_node = head;
	while (current_node)
	{
		if (current_node == node)
		{
			current_node = current_node->next;
			continue ;
		}
		if (ft_strcmp(current_node->name, node->name) < 0)
			smaller++;
		current_node = current_node->next;
	}
	return (smaller);
}

void	ft_setup_indexes(t_env_var *head)
{
	t_env_var	*current_node;

	current_node = head;
	while (current_node)
	{
		current_node->sort_index = ft_count_smaller(head, current_node);
		current_node = current_node->next;
	}
}

t_env_var	*ft_setup_env(char **env)
{
	t_env_var		*env_lst;
	t_env_var		*new_var;
	char			**new_env;
	unsigned int	i;

	/* 
		!-- This function still needs protection from malloc --!
	*/
	i = 0;
	if (!env || !env[i])
		return (NULL);
	new_env = ft_split_env(env[i], '=');
	if (!new_env)
		return (NULL);
	env_lst = ft_lstnew(new_env);
	env_lst->index = i++;
	while (env[i])
	{
		new_env = ft_split_env(env[i], '=');
		new_var = ft_lstnew(new_env);
		new_var->index = i++;
		ft_lstadd_back(&env_lst, new_var);
	}
	ft_setup_indexes(env_lst);
	return (env_lst);
}
