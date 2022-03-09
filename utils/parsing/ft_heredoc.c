/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olabrahm <olabrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 19:39:52 by obouadel          #+#    #+#             */
/*   Updated: 2022/03/09 14:28:19 by olabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define WRITE_END 1
#define READ_END  0

static void    ft_doc_child(char *eof, int hfd[2])
{
    char    *line;

	signal(SIGINT, SIG_DFL);
    line = NULL;
    if (pipe(hfd) == -1)
        exit (-1);
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
}

int    ft_heredoc(char *eof) // return the fd of the file
{
    int    hfd[2];
    int    fd;
    int    pid;

    if (pipe(hfd) < 0)
        return (-1);
    pid = fork();
    if (pid < 0)
        return (-1);
    if (!pid)
        ft_doc_child(eof, hfd);
    close(hfd[1]);
    close(hfd[0]);
    waitpid(pid, &fd, 0);
    return (WEXITSTATUS(fd));
}