/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olabrahm <olabrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 19:39:52 by obouadel          #+#    #+#             */
/*   Updated: 2022/03/07 18:05:40 by olabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define WRITE_END 1
#define READ_END  0

int	ft_heredoc(char *eof) // return the fd of the file
{
	char	*line;
	int		hfd[2];

	line = NULL;
	if (pipe(hfd) == -1)
		return (-1);
	while (69)
	{
		line = readline("> ");
		if (!line || !ft_strncmp(line, eof, ft_strlen(eof) + 1))
			break ;
		write(hfd[WRITE_END], line, ft_strlen(line));
		write(hfd[WRITE_END], "\n", 1);
		free(line);
	}
	if (line)
		free(line);
	return ((close(hfd[WRITE_END]), hfd[READ_END]));
}
