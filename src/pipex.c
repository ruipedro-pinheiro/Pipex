/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinheir <rpinhier@student.42Lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 15:51:54 by rpinheir          #+#    #+#             */
/*   Updated: 2026/02/04 15:52:15 by rpinheir         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int	child_1(char **argv, int *pipe_fd, char **envp)
{
	int	fd;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		perror("infile");
		exit(1);
	}
	close(pipe_fd[0]);
	dup2(fd, 0);
	close(fd);
	dup2(pipe_fd[1], 1);
	close(pipe_fd[1]);
	exec_cmd(argv[2], envp);
	return (0);
}

int	child_2(char **argv, int *pipe_fd, char **envp)
{
	int	fd;

	fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("outfile");
		exit(1);
	}
	close(pipe_fd[1]);
	dup2(fd, 1);
	close(fd);
	dup2(pipe_fd[0], 0);
	close(pipe_fd[0]);
	exec_cmd(argv[3], envp);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	int		pipe_fd[2];
	pid_t	pid1;
	pid_t	pid2;
	int		status;

	if (argc != 5)
		return (ft_printf("Please give at least 4 args "), 1);
	if (pipe(pipe_fd) == -1)
		exit(1);
	pid1 = fork();
	if (pid1 == -1)
		exit(1);
	if (!pid1)
		child_1(argv, pipe_fd, envp);
	pid2 = fork();
	if (pid2 == -1)
		exit(1);
	if (!pid2)
		child_2(argv, pipe_fd, envp);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(pid1, &status, 0);
	waitpid(pid2, &status, 0);
	return (WEXITSTATUS(status));
}
