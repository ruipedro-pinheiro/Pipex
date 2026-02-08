/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinheir <rpinhier@student.42Lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 18:46:52 by rpinheir          #+#    #+#             */
/*   Updated: 2026/02/04 14:49:15 by rpinheir         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_pipex
{
	char	**cmds;
	char	**envp;
	char	*infile;
	char	*outfile;
	char	*limiter;
	int		cmd_count;
	pid_t	*pids;
}			t_pipex;

void		exec_cmd(char *cmd, char **envp);
int			error_handler(char *msg);
void		child_start(t_pipex *pipex, int *pipe_fd);
void		child_process(t_pipex *pipex, int i, int prev_fd, int *pipe_fd);
void		child_end(t_pipex *pipex, int prev_fd);
int			here_doc_input(t_pipex *pipex);
int			pipe_setup(t_pipex *pipex);

#endif
