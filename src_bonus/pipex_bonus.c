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
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	child_start(char **argv, int *pipe_fd, char **envp)
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

int	child_process(int argc, char **argv, int *pipe_fd, int *pipe_fd2,
		char **envp)
{
	if (pipe_fd[0] == -1 || pipe_fd[0] == -1)
		perror("Pipe unavailable");
	close(pipe_fd[1]);
	close(pipe_fd2[0]);
	dup2(pipe_fd[0], 0);
	close(pipe_fd[0]);
	dup2(pipe_fd2[1], 1);
	close(pipe_fd[1]);
	exec_cmd(argv[argc - 3], envp);
	return (0);
}

int	child_end(int argc, char **argv, int *pipe_fd2, char **envp)
{
	int	fd;

	fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("outfile");
		exit(1);
	}
	close(pipe_fd2[1]);
	dup2(fd, 1);
	close(fd);
	dup2(pipe_fd2[0], 0);
	close(pipe_fd2[0]);
	exec_cmd(argv[argc - 2], envp);
	return (0);
}
int	pipe_setup(int argc, char **argv, char **envp)
{
	int		pipe_fd[2];
	int		pipe_fd2[2];
	pid_t	pid1;
	pid_t	pid2;
	int		status;
	int		pid3;

	if (pipe(pipe_fd) == -1)
		exit(1);
	pid1 = fork();
	if (pid1 == -1)
		exit(1);
	if (!pid1)
		child_start(argv, pipe_fd, envp);
	if (argc > 5)
	{
		if (pipe(pipe_fd2) == -1)
			exit(1);
		pid3 = fork();
		if (pid3 == -1)
			exit(1);
		if (!pid3)
			child_process(argc, argv, pipe_fd, pipe_fd2, envp);
	}
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	pid2 = fork();
	if (pid2 == -1)
		exit(1);
	if (!pid2)
		child_end(argc, argv, pipe_fd2, envp);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	close(pipe_fd2[0]);
	close(pipe_fd2[1]);
	waitpid(pid1, &status, 0);
	waitpid(pid2, &status, 0);
	waitpid(pid3, &status, 0);
	return (WEXITSTATUS(status));
}
int	main(int argc, char **argv, char **envp)
{
	int	i;

	if (argc < 5)
		return (ft_printf("Please give at least 9 args\n"), 2);
	if (ft_strncmp(argv[1], "here_doc", ft_strlen("here_doc") == 0))
	{
		i = 3;
		if (argc < 6)
			exit(1);
	}
	else
	{
	}
	pipe_setup(argc, argv, envp);
}
