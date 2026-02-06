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

// pipe_fd is the original pipe, if needed more pipes will be added
typedef struct t_pipex
{
	int		*pipe_fd;
	char	**argv;
	char	**envp;
}			t_pipex;

void		exec_cmd(char *cmd, char **envp);
int			error_handler(char *msg);

#endif
