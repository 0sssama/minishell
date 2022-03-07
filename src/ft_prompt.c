/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olabrahm <olabrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 15:07:26 by olabrahm          #+#    #+#             */
/*   Updated: 2022/03/07 18:01:09 by olabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_empty_line(char *str)
{
	int	i;

	i = -1;
	if (str[0] == 0)
		return (1);
	while (str[++i])
		if (str[i] != ' ' && str[i] != DELIMIT)
			return (0);
	return (1);
}

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
		printf("-	EOF : %s -\n", current_node->eof);
		printf("-	TOKEN : %d -\n", current_node->token);
		current_node = current_node->next;
	}
	printf("-------------------------\n");
}

static void	ft_parse(t_state *state)
{
	char	**cmd;

	add_history(state->line);
	cmd = ft_clean_args(state); // tokenizer
	if (!cmd && state->man_err)
		return ;
	state->cmd_tree = ft_parse_tree(cmd);
	ft_print_tree(state->cmd_tree);
}

void	ft_prompt(t_state *state)
{
	signal(SIGINT, ft_handle_sigint);
	signal(SIGQUIT, ft_handle_sigquit);
	while (1)
	{
		state->cmd_tree = NULL;
		state->man_err = 0;
		state->pid = -1;
		state->sig = 0;
		state->line = readline("\033[1mminishell-1.5$> \033[m");
		rl_on_new_line();
		if (!state->line)
			break ;
		if (ft_empty_line(state->line))
		{
			state->status = 0;
			free(state->line);
			continue ;
		}
		ft_parse(state);
		if (state->man_err)
		{
			state->status = 258;
			free(state->line);
			continue ;
		}
		// ft_execute(state);
		free(state->line);
		ft_free_tree(&state->cmd_tree);
	}
}
