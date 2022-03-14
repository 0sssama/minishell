/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olabrahm <olabrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 15:07:26 by olabrahm          #+#    #+#             */
/*   Updated: 2022/03/14 11:20:18 by olabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_print_tree(t_cmd *head)
{
	unsigned int	i;
	t_cmd			*current_node;

	if (!head)
		return ;
	i = 0;
	current_node = head;
	while (current_node)
	{
		printf("-------------------------\n");
		printf("-	NAME : %s -\n", current_node->name);
		printf("-	ARGS : ");
		i = 0;
		while (current_node->args && current_node->args[i])
			printf("[%s] ", current_node->args[i++]);
		printf("-\n");
		printf("-	NUM_OF_ARGS : %d -\n", current_node->num_of_args);
		printf("-	FILE : %s -\n", current_node->file);
		printf("-	FILE DESCRIPTOR : %d -\n", current_node->fd);
		printf("-	TOKEN : %d -\n", current_node->token);
		current_node = current_node->next;
	}
	printf("-------------------------\n");
}

static void	ft_parse(t_state *state)
{
	char	**cmd;

	add_history(state->line);
	cmd = ft_clean_args(state);
	if (!cmd && state->man_err)
		return ;
	state->cmd_tree = ft_parse_tree(cmd);
	if (!state->cmd_tree)
	{
		state->status = 1;
		state->man_err = 1;
	}
	ft_print_tree(state->cmd_tree);
}

static void	ft_init_loop(t_state *state)
{
	state->cmd_tree = NULL;
	state->man_err = 0;
	state->pid = -1;
	state->sig = 0;
	state->line = readline("\033[1mminishell-2.0$> \033[m");
	rl_on_new_line();
}

static void	ft_set_status(t_state *state, int status)
{
	state->status = status;
	free(state->line);
}

static void	ft_reset(t_state *state)
{
	free(state->line);
	ft_free_tree(&state->cmd_tree);
	ft_reset_io(state);
	ft_update_env(state);
}

void	ft_prompt(t_state *state)
{
	while (69)
	{
		signal(SIGINT, ft_handle_sigint_parent);
		signal(SIGQUIT, SIG_IGN);
		ft_init_loop(state);
		if (!state->line)
			break ;
		if (ft_empty_line(state->line))
		{
			ft_set_status(state, 0);
			continue ;
		}
		ft_parse(state);
		if (state->man_err)
		{
			free(state->line);
			continue ;
		}
		signal(SIGINT, SIG_IGN);
		ft_save_io(state);
		ft_execution(state);
		ft_reset(state);
	}
}
