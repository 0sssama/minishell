/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olabrahm <olabrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 15:11:20 by olabrahm          #+#    #+#             */
/*   Updated: 2022/03/09 13:51:52 by olabrahm         ###   ########.fr       */
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
	{
		free(s1[i]);
		s1[i++] = NULL;
	}
	free(s1);
	s1 = NULL;
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
	ft_free_matrix(state->envtab);
	clear_history();
	ft_lstclear(&state->env);
	exit(status);
}
