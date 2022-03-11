/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_tree2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olabrahm <olabrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 21:18:09 by olabrahm          #+#    #+#             */
/*   Updated: 2022/03/11 21:22:27 by olabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_naf_helper(t_ptree_nodes *nodes, t_ptree_iters *iters, char **cmd)
{
	(nodes->current_node)->file = ft_strdup(cmd[iters->i]);
	if ((nodes->current_node)->token == REDIN)
	{
		iters->inside_cmd = 0;
		iters->file[1] = 0;
	}
	else
		iters->file[0] = 1;
	if ((nodes->current_node)->token == APPEND)
		(nodes->current_node)->fd = open((nodes->current_node)->file,
				O_CREAT | O_RDWR | O_APPEND, 0644);
	else if ((nodes->current_node)->token == REDOUT)
		(nodes->current_node)->fd = open((nodes->current_node)->file,
				O_CREAT | O_RDWR | O_TRUNC, 0644);
	else if ((nodes->current_node)->token == REDIN)
		(nodes->current_node)->fd = open((nodes->current_node)->file,
				O_RDONLY);
	if ((nodes->current_node)->fd == -1)
	{
		ft_put_error((nodes->current_node)->file,
			"No such file or directory.\n");
		iters->stop_tree = 1;
		return ;
	}
}

void	ft_next_arg_file(t_ptree_nodes *nodes, t_ptree_iters *iters, char **cmd)
{
	if ((nodes->current_node)->token == HEREDOC)
	{
		(nodes->current_node)->eof = ft_strdup(cmd[iters->i]);
		(nodes->current_node)->fd = ft_heredoc((nodes->current_node)->eof);
		if ((nodes->current_node)->fd == -1)
		{
			iters->stop_tree = 1;
			return ;
		}
		iters->inside_cmd = 0;
		iters->file[0] = 0;
		iters->file[1] = 0;
		(iters->i)++;
		return ;
	}
	ft_naf_helper(nodes, iters, cmd);
}
