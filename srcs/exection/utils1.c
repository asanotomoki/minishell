/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiroaki <hiroaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 00:42:50 by tasano            #+#    #+#             */
/*   Updated: 2023/01/18 18:45:22 by hiroaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include <fcntl.h>
#include "libft.h"
#include "util.h"
#include <sys/wait.h>
#include <signal.h>

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

void	close_all_pipe(int pp[OPEN_MAX / 2][2])
{
	int	i;

	i = -1;
	while (++i < OPEN_MAX / 2)
	{
		dprintf(2, "%d", 1);
		close_pipe(pp[i]);
	}
}

int	set_waitpid(pid_t pid)
{
	int			status;

	status = 0;
	if (waitpid(pid, &status, 0) < 0)
	{
		if (errno != EINTR && errno != ECHILD)
			perror_exit(EXIT_FAILURE, "waitpid");
		if (errno == EINTR)
			return (EINTR);
	}
	return (status);
}

void	set_dup2(int new_fd, int old_fd)
{
	if (dup2(new_fd, old_fd) == -1)
		perror_exit(EXIT_FAILURE, "dup2");
}

void	create_waitpid(t_cmd *cmd)
{
	int		status;
	bool	interrupted;

	interrupted = false;
	while (cmd)
	{
		status = set_waitpid(cmd->pid);
		if (status == EINTR)
			interrupted = true;
		cmd = cmd->piped_cmd;
	}
	if (interrupted)
		g_shell.child_interrupted = 1;
	else
		set_status(status % 255);
	waitpid(cmd->pid, &status, 0);
	if (WIFSIGNALED(status))
		status = 128 + WTERMSIG(status);
	set_status(status % 255);
	return (0);
}
