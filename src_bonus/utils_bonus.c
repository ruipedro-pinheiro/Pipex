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

#include "../include/pipex_bonus.h"

int	error_handler(char *msg)
{
	perror(msg);
	exit(errno);
}

char	*get_envp(char **envp)
{
	int		i;
	int		j;
	char	*path;

	i = 0;
	j = 0;
	while (envp[i])
	{
		j = 0;
		while (envp[i][j] && envp[i][j] != '=')
			j++;
		path = ft_substr(envp[i], 0, j + 1);
		if (ft_strncmp(path, "PATH=", 5) == 0)
		{
			free(path);
			return (envp[i] + j + 1);
		}
		free(path);
		i++;
	}
	return ("");
}

char	*get_path(char *cmd, char **envp)
{
	char	**paths;
	char	*exec;
	char	*path_part;
	int		i;

	i = 0;
	paths = ft_split(get_envp(envp), ':');
	if (!paths)
		exit(0);
	while (paths[i])
	{
		path_part = ft_strjoin(paths[i], "/");
		exec = ft_strjoin(path_part, cmd);
		free(path_part);
		if (access(exec, X_OK) == 0)
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

void	exec_cmd(char *cmd, char **envp)
{
	char	**s_cmd;
	char	*path;

	s_cmd = ft_split(cmd, ' ');
	path = get_path(s_cmd[0], envp);
	if (!path)
	{
		ft_putstr_fd(s_cmd[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		ft_strfree(s_cmd);
		exit(127);
	}
	if (execve(path, s_cmd, envp) == -1)
	{
		perror(s_cmd[0]);
		free(path);
		ft_strfree(s_cmd);
		exit(126);
	}
}
