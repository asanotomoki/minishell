/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 21:52:46 by hiroaki           #+#    #+#             */
/*   Updated: 2023/01/21 08:09:17 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	set_waitpid(pid_t pid, int	*status)
{
	if (waitpid(pid, status, 0) < 0)
		perror_exit(EXIT_FAILURE, "waitpid");
}

void	create_waitpid(t_cmd *cmd)
{
	int		status;

	status = 0;
	while (cmd)
	{
		set_waitpid(cmd->pid, &status);
		cmd = cmd->piped_cmd;
	}
	if (WIFSIGNALED(status))
		status = 128 + WTERMSIG(status);
	else
		status = status >> 8;
	set_status(status);
}
