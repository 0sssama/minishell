/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouadel <obouadel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 19:25:13 by olabrahm          #+#    #+#             */
/*   Updated: 2022/03/01 18:24:08 by obouadel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(t_state *state)
{
	if (state->pwd == NULL)
		state->pwd = getcwd(NULL, PATH_MAX);
	if (state->pwd == NULL && errno == ENOENT)
		state->pwd = getcwd(state->pwd, PATH_MAX);
	state->status = 0;
	printf("%s\n", state->pwd);
}
