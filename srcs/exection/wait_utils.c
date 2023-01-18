/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiroaki <hiroaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 01:16:38 by hiroaki           #+#    #+#             */
/*   Updated: 2023/01/19 01:17:14 by hiroaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

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
}
