/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouadel <obouadel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 15:11:20 by olabrahm          #+#    #+#             */
/*   Updated: 2022/03/04 17:05:46 by obouadel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_temp(char **s1)
{
	int	i;

	i = 0;
	if (!s1)
		return ;
	while (s1[i])
		free(s1[i++]);
	free(s1);
}

void	ft_free_matrix(char **matrix)
{
	int	i;

	if (!matrix)
		return ;
	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		matrix[i++] = NULL;
	}
	free(matrix);
	matrix = NULL;
}

void	ft_free_cmd(t_state *state)
{
	int	i;

	i = 0;
	while (state->current_cmd.args[i])
	{
		free(state->current_cmd.args[i]);
		state->current_cmd.args[i++] = NULL;
	}
	free(state->current_cmd.args);
	state->current_cmd.args = NULL;
}

void	ft_free_exit(t_state *state, int status)
{
	write(1, "exit\n", 5);
	if (state->line)
		free(state->line);
	if (state->pwd)
		free(state->pwd);
	if (state->oldpwd)
		free(state->oldpwd);
	ft_free_tree(&state->cmd_tree);
	clear_history();
	ft_lstclear(&state->env);
	exit(status);
}
