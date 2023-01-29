/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiroaki <hiroaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 21:52:46 by hiroaki           #+#    #+#             */
/*   Updated: 2023/01/30 03:14:53 by hiroaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include <signal.h>

static void	set_waitpid(pid_t pid, int	*status)
{
	if (waitpid(pid, status, 0) < 0)
	{
		if (errno == EINTR)
		{
			g_shell.child_interrupted = 1;
			printf("Quit: 3\n");
			return ;
		}
		perror_exit(EXIT_FAILURE, "waitpid");
	}
}

void	create_waitpid(t_cmd *cmd)
{
	int		status;

	status = 0;
	while (cmd)
	{
		set_waitpid(cmd->pid, &status);
		if (g_shell.child_interrupted)
			return ;
		cmd = cmd->piped_cmd;
	}
	if (WIFSIGNALED(status))
	{
		status = 128 | WTERMSIG(status);
		printf("\n");
		g_shell.sig_no = 0;
	}
	else
		status = status >> 8;
	set_status(status);
}
