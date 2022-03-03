/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouadel <obouadel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 19:25:13 by olabrahm          #+#    #+#             */
/*   Updated: 2022/02/16 15:34:10 by obouadel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* static char	*ft_realloc(char *old_str, int new_size)
{
	char	*new_str;
	int		old_str_len;

	old_str_len = ft_strlen(old_str);
	new_str = (char *) malloc((new_size + 1) * sizeof(char));
	if (!new_str)
	{
		free(old_str);
		return (NULL);
	}
	ft_strlcpy(new_str, old_str, old_str_len);
	free(old_str);
	old_str = NULL;
	return (new_str);
}
 */
void	ft_pwd(t_state *state)
{
	if (state->pwd == NULL)
		state->pwd = getcwd(NULL, PATH_MAX);
	if (state->pwd == NULL && errno == ENOENT)
		state->pwd = getcwd(state->pwd, PATH_MAX);
	state->status = 0;
	printf("%s\n", state->pwd);
}