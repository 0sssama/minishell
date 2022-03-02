/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouadel <obouadel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 18:48:22 by obouadel          #+#    #+#             */
/*   Updated: 2022/03/02 19:19:02 by obouadel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_free_pipes(t_state *state)
{
	int	i;

	i = 0;
	if (state->pipes == 0)
		return ;
	while (i < state->pipes)
		free(state->fds[i++]);
	free(state->fds);
	free(state->pids);
}

t_cmd	*ft_redirect(t_cmd *cmd)
{
	if (cmd->token == REDOUT)
	{
		while (cmd->next && (cmd->next->token == REDOUT || \
		cmd->next->token == APPEND))
			cmd = cmd->next;
		if (cmd)
			dup2(cmd->fd, 1);
	}
	else if (cmd->token == REDIN)
	{
		while (cmd->next && cmd->next->token == REDIN)
			cmd = cmd->next;
		if (cmd)
			dup2(cmd->fd, 0);
	}
	return (cmd);
}

void	ft_execute_pipeline(t_state *state, t_cmd *cmd, t_cmd *sv)
{
	t_cmd	*save;

	save = sv;
	if (!cmd || cmd->token == PIPE)
	{
		if (!save)
			state->status = 0;
		else
			ft_execute(state, save);
		return ;
	}
	else if (cmd->token == 0)
		save = cmd;
	else if (cmd->token == REDOUT || cmd->token == APPEND)
		cmd = ft_redirect(cmd);
	else if (cmd->token == REDIN)
		cmd = ft_redirect(cmd);
	if (!cmd)
		return ;
	ft_execute_pipeline(state, cmd->next, save);
}

void	ft_exec_cmd(t_state *state, t_cmd *cmd)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		ft_free_exit(state, 1);
	if (!pid)
	{
		ft_execute_pipeline(state, cmd, NULL);
		exit(state->status);
	}
	waitpid(pid, &state->status, 0);
}

void	ft_execution(t_state *state)
{
	int		i;
	t_cmd	*current_node;

	i = 0;
	current_node = state->cmd_tree;
	state->pipes = ft_get_pipes(&state->cmd_tree);
	if (state->pipes == 0)
	{
		ft_exec_cmd(state, current_node);
		return ;
	}
	ft_setup_pipe(state);
	ft_loop_pipe(state, current_node);
	ft_close(state);
	while (i < state->pipes + 1)
		waitpid(state->pids[i++], &state->status, 0);
	ft_free_pipes(state);
}
