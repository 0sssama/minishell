/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouadel <obouadel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 18:16:32 by obouadel          #+#    #+#             */
/*   Updated: 2022/02/18 20:21:13 by obouadel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_is_valid(char c)
{
	if (c == '_')
		return (1);
	if (c >= 'a' && c <= 'z')
		return (1);
	if (c >= 'A' && c <= 'Z')
		return (1);
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

static int	ft_replace_line(t_state *state, int start, int end, t_env_var *var)
{
	int		i;
	int		j;
	int		len;
	char	*newline;

	i = -1;
	j = 0;
	len = (ft_strlen(state->line) - (end - start));
	if (var)
		len = len + ft_strlen(var->value);
	newline = ft_calloc(len + 1, sizeof(char));
	if (!newline)
		ft_free_exit(state, 12);
	while (++i < start)
		newline[i] = state->line[i];
	while (var && var->value[j])
		newline[i++] = var->value[j++];
	start = i;
	while (state->line[end])
		newline[i++] = state->line[end++];
	free(state->line);
	state->line = newline;
	return (start);
}

void	ft_get_vars(t_state *state, int *i)
{
	int			l;
	char		*name;
	t_env_var	*var;

	l = (*i) + 1;
	while (ft_is_valid(state->line[l]) && state->line[l])
		l++;
	name = ft_substr(state->line, (*i) + 1, (l - (*i) - 1));
	if (!name)
		ft_free_exit(state, 12);
	var = ft_get_env(&state->env, name);
	free(name);
	*i = ft_replace_line(state, *i, l, var);
}
