/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinheir <rpinhier@student.42Lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 12:00:38 by rpinheir          #+#    #+#             */
/*   Updated: 2026/02/04 15:54:42 by rpinheir         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include <stdio.h>
#include <unistd.h>

char	*get_envp(char **envp)
{
	int		i;
	int		j;
	char	*name;
	char	*path;

	name = "PATH";
	i = 0;
	j = 0;
	while (envp[i][j])
	{
		j = 0;
		while (envp[i][j] && envp[i][j] != '=')
			j++;
		path = ft_substr(envp[i], 0, j + 1);
		if (ft_strncmp(path, name, ft_strlen(name)) == 0)
		{
			free(path);
			return (envp[i] + j + 1);
		}
		free(path);
		i++;
	}
	return (NULL);
}

char	*get_path(char *cmd, char **envp)
{
	char	**paths;
	char	*exec;
	char	*path_part;
	int		i;

	i = 0;
	paths = ft_split(get_envp(envp), ':');
	while (paths[i])
	{
		path_part = ft_strjoin(paths[i], "/");
		exec = ft_strjoin(path_part, cmd);
		free(path_part);
		if (access(exec, F_OK && X_OK) == 0)
		{
			ft_strfree(paths);
			return (exec);
		}
		free(exec);
		i++;
	}
	ft_strfree(paths);
	return (NULL);
}

void	exec(char *cmd, char **envp)
{
	char	**s_cmd;
	char	*path;

	s_cmd = ft_split(cmd, ' ');
	path = get_path(s_cmd[0], envp);
	if (execve(path, s_cmd, envp) == -1)
	{
		ft_putstr_fd(s_cmd[0], 2);
		perror("\n Command not found");
		ft_strfree(s_cmd);
		exit(0);
	}
}
