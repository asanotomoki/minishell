/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 21:53:53 by hiroaki           #+#    #+#             */
/*   Updated: 2023/01/21 06:30:23 by tasano           ###   ########.fr       */
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

int	use_system_pipe(t_list *document)
{
	int	e;
	int	herepipe[2];

	if (pipe(herepipe) < 0)
		return (-1);
	e = write_heredoc(herepipe[1], document);
	if (e != 0)
	{
		close(herepipe[0]);
		errno = e;
		return (-1);
	}
	close(herepipe[1]);
	return (herepipe[0]);
}

size_t	pipe_cnt(t_cmd *cmd)
{
	size_t	cnt;

	cnt = 0;
	while (cmd)
	{
		cnt++;
		cmd = cmd->piped_cmd;
	}
	return (cnt);
}

void	connect_io_pipe(size_t i, size_t pipe_cnt, int pp[OPEN_MAX / 2][2])
{
	if (pipe_cnt == 1)
		return ;
	if (i == 0)
		set_stdout(pp[i]);
	else if (i == pipe_cnt - 1)
		set_stdin(pp[i - 1]);
	else
	{
		set_stdout(pp[i]);
		set_stdin(pp[i - 1]);
	}
}
