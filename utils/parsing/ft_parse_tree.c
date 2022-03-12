/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_tree.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouadel <obouadel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 19:48:56 by olabrahm          #+#    #+#             */
/*   Updated: 2022/03/12 13:43:44 by obouadel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_notkn_incmd(t_ptree_nodes *nodes, t_ptree_iters *iters, char **cmd)
{
	if (iters->file[0])
	{
		(nodes->last_cmd)->args = ft_add_arg((nodes->last_cmd)->args,
				cmd[iters->i]);
		((nodes->last_cmd)->num_of_args)++;
	}
	else if (iters->file[1])
		ft_next_arg_file(nodes, iters, cmd);
	else
	{
		(nodes->current_node)->args = ft_add_arg((nodes->current_node)->args,
				cmd[iters->i]);
		((nodes->current_node)->num_of_args)++;
	}
}

void	ft_notkn_outcmd(t_ptree_nodes *nodes, t_ptree_iters *iters, char **cmd)
{
	nodes->previous_node = (nodes->current_node);
	(nodes->current_node) = (t_cmd *) malloc(sizeof(t_cmd));
	if (nodes->previous_node)
		nodes->previous_node->next = (nodes->current_node);
	if (!(nodes->current_node))
	{
		iters->stop_tree = 1;
		return ;
	}
	if ((iters->i) == 0)
		nodes->head = (nodes->current_node);
	iters->inside_cmd = 1;
	(nodes->current_node)->name = ft_strdup(ft_lowerstr(cmd[iters->i]));
	(nodes->current_node)->num_of_args = 1;
	(nodes->current_node)->args = ft_init_args(cmd[iters->i]);
	(nodes->current_node)->file = NULL;
	(nodes->current_node)->eof = NULL;
	(nodes->current_node)->fd = 0;
	(nodes->current_node)->token = 0;
	(nodes->current_node)->next = NULL;
	nodes->last_cmd = (nodes->current_node);
}

void	ft_parse_token(t_ptree_nodes *nodes, t_ptree_iters *iters, char **cmd)
{
	nodes->previous_node = (nodes->current_node);
	(nodes->current_node) = (t_cmd *) malloc(sizeof(t_cmd));
	if (nodes->previous_node)
		nodes->previous_node->next = (nodes->current_node);
	if (!(nodes->current_node))
	{
		iters->stop_tree = 1;
		return ;
	}
	if (iters->i == 0)
		nodes->head = (nodes->current_node);
	(nodes->current_node)->name = NULL;
	(nodes->current_node)->args = NULL;
	(nodes->current_node)->num_of_args = 0;
	(nodes->current_node)->next = NULL;
	(nodes->current_node)->file = NULL;
	(nodes->current_node)->eof = NULL;
	(nodes->current_node)->fd = 0;
	(nodes->current_node)->token = ft_str_istoken(cmd[iters->i]);
	iters->inside_cmd = (ft_str_istoken(cmd[(iters->i)]) == REDOUT
			|| ft_str_istoken(cmd[iters->i]) == REDIN
			|| ft_str_istoken(cmd[iters->i]) == HEREDOC);
	iters->file[0] = 0;
	iters->file[1] = iters->inside_cmd;
}

void	ft_init_ptree(t_ptree_nodes *nodes, t_ptree_iters *iters)
{
	(iters->i) = 0;
	iters->inside_cmd = 0;
	iters->stop_tree = 0;
	iters->file[0] = 0;
	iters->file[1] = 0;
	nodes->previous_node = NULL;
	nodes->current_node = NULL;
	nodes->head = NULL;
}

t_cmd	*ft_parse_tree(char **cmd)
{
	t_ptree_nodes	nodes;
	t_ptree_iters	iters;

	ft_init_ptree(&nodes, &iters);
	while (cmd[(iters.i)] && !iters.stop_tree)
	{
		if (ft_str_istoken(cmd[(iters.i)]) == 0)
		{
			if (iters.inside_cmd)
				ft_notkn_incmd(&nodes, &iters, cmd);
			else
				ft_notkn_outcmd(&nodes, &iters, cmd);
		}
		else if (iters.inside_cmd || ft_str_istoken(cmd[(iters.i)]) == REDIN
			|| ft_str_istoken(cmd[(iters.i)]) == HEREDOC)
			ft_parse_token(&nodes, &iters, cmd);
		(iters.i)++;
	}
	
	ft_free_matrix(cmd);
	if (iters.stop_tree)
		return (NULL);
	return (nodes.head);
}
