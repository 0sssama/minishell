/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouadel <obouadel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 19:39:52 by obouadel          #+#    #+#             */
/*   Updated: 2022/03/09 16:08:08 by obouadel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define WRITE_END 1
#define READ_END  0

static void    ft_doc_child(char *eof, int hfd[2])
{
    char    *line;
	int		fd;

	signal(SIGINT, SIG_DFL);
    line = NULL;
    fd = hfd[0];
	while (69)
    {
        line = readline("> ");
        if (!line || !ft_strncmp(line, eof, ft_strlen(eof) + 1))
            break ;
        write(hfd[WRITE_END], line, ft_strlen(line));
        write(hfd[WRITE_END], "\n", 1);
        free(line);
		line = NULL;
    }
    if (line)
        free(line);
	printf("%d from child\n", hfd[0]);
    close(hfd[WRITE_END]);
    exit(0);
}

int    ft_heredoc(char *eof) // return the fd of the file
{
    int    hfd[2];
    int    status;
    int    pid;

    if (pipe(hfd) < 0)
        return (-1);
    pid = fork();
    if (pid < 0)
        return (-1);
	signal(SIGINT, SIG_IGN);
    if (!pid)
        ft_doc_child(eof, hfd);
    close(hfd[1]);
    waitpid(pid, &status, 0);
	signal(SIGINT, SIG_DFL);
	if (status == 2)
		return (-1);
    return (hfd[0]);
}
/* 
int    ft_heredoc(char *eof) // return the fd of the file
{
	char    *line;
	int		hfd[2];

	signal(SIGINT, SIG_DFL);
    if (pipe(hfd) < 0)
        return (-1);
	line = NULL;
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
    close(hfd[WRITE_END]);
    exit(hfd[READ_END]);
	
} */