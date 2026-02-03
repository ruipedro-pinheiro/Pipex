/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinheir <rpinhier@student.42Lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 18:36:58 by rpinheir          #+#    #+#             */
/*   Updated: 2026/02/03 19:39:11 by rpinheir         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	child_1(char **argv, int *pipe_fd, char **envp)
{
	int	fd;

	return (0);
}
int	child_2(char **argv, int *pipe_fd, char **envp)
{
	return (0);
}
int	main(int argc, char **argv, char **envp)
{
	int		pipe_fd[2];
	pid_t	pid1;
	pid_t	pid2;

	if (argc != 5)
		ft_printf("Please give at least 4 args ");
	if (pipe(pipe_fd) == -1)
		exit(-1);
	pid1 = fork();
	if (pid1 == -1)
		exit(-1);
	pid2 = fork();
	if (pid2 == -1)
		exit(-1);
	if (!pid1)
		child_1(argv, pipe_fd, envp);
	child_2(argv, pipe_fd, envp);
}
