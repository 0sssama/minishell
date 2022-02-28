/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olabrahm <olabrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 15:11:20 by olabrahm          #+#    #+#             */
/*   Updated: 2022/02/26 16:13:36 by olabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix && matrix[i])
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
	clear_history();
	ft_lstclear(&state->env);
	exit(status);
}
