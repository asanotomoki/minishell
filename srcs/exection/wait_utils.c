/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiroaki <hiroaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 21:52:46 by hiroaki           #+#    #+#             */
/*   Updated: 2023/01/19 21:53:03 by hiroaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	set_waitpid(pid_t pid)
{
	if (waitpid(pid, NULL, 0) < 0)
	{
		if (errno != EINTR && errno != ECHILD)
			perror_exit(EXIT_FAILURE, "waitpid");
	}
}

void	create_waitpid(t_cmd *cmd)
{
	bool	interrupted;

	errno = 0;
	interrupted = false;
	while (cmd)
	{
		set_waitpid(cmd->pid);
		if (errno == EINTR)
			interrupted = true;
		cmd = cmd->piped_cmd;
	}
	if (interrupted)
		g_shell.child_interrupted = 1;
}
