/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiroaki <hiroaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 01:16:38 by hiroaki           #+#    #+#             */
/*   Updated: 2023/01/19 03:22:31 by hiroaki          ###   ########.fr       */
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
