/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouadel <obouadel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 19:39:52 by obouadel          #+#    #+#             */
/*   Updated: 2022/03/05 18:23:55 by obouadel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
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

/* int main(void)
{
	int	fd;
	fd = ft_heredoc("EOF");
	if (fd == -1)
		return (perror("fd"), 1);
	printf("fd is %d\n", fd);
	dup2(fd, 0);
	close(fd);
	execlp("cat", "cat", NULL);
	return (0);
} */