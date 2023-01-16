/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 00:42:50 by tasano            #+#    #+#             */
/*   Updated: 2023/01/17 01:38:45 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include <fcntl.h>
#include "libft.h"
#include "util.h"

void	set_pipe(int pp[2])
{
	if (pipe(pp) == -1)
		perror_exit(EXIT_FAILURE, "pipe");
}

void	close_pipe(int pp[2])
{
	close(pp[0]);
	close(pp[1]);
}

void	set_waitpid(pid_t pid)
{
	if (waitpid(pid, NULL, 0) == -1)
		perror_exit(EXIT_FAILURE, "waitpid");
}

void	set_dup2(int new_fd, int old_fd)
{
	if (dup2(new_fd, old_fd) == -1)
		perror_exit(EXIT_FAILURE, "dup2");
}

int	create_waitpid(t_cmd *cmd)
{
	int	status;

	while (cmd->piped_cmd)
	{
		set_waitpid(cmd->pid);
		cmd = cmd->piped_cmd;
	}
	if (waitpid(cmd->pid, &status, 0) == -1)
		status = 1;
	set_status(status % 255);
	return (0);
}
