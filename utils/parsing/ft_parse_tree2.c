/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_tree2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouadel <obouadel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 21:18:09 by olabrahm          #+#    #+#             */
/*   Updated: 2022/03/12 13:44:12 by obouadel         ###   ########.fr       */
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
