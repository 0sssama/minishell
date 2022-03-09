/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_update_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olabrahm <olabrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 13:38:10 by olabrahm          #+#    #+#             */
/*   Updated: 2022/03/09 13:46:58 by olabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_update_pwd(t_state *state)
{
	char	*env_str;
	char	**new_env;
	char	*tmp;

	tmp = ft_strdup("PWD=");
	env_str = ft_strjoin(tmp, state->pwd);
	free(tmp);
	new_env = ft_split_env(env_str, '=');
	ft_env_update(&state->env, new_env);
}

static void	ft_update_oldpwd(t_state *state)
{
	char	*env_str;
	char	**new_env;
	char	*tmp;

	tmp = ft_strdup("OLDPWD=");
	env_str = ft_strjoin(tmp, state->oldpwd);
	free(tmp);
	new_env = ft_split_env(env_str, '=');
	ft_env_update(&state->env, new_env);
}

void	ft_update_env(t_state *state)
{
	ft_update_pwd(state);
	ft_update_oldpwd(state);
}