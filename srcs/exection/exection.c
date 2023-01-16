/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exection.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiroaki <hiroaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 21:06:06 by tasano            #+#    #+#             */
/*   Updated: 2023/01/16 20:46:02 by hiroaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	basic_command(t_cmd *exec)
{
	extern char	**environ;
	char		*cmdfile;
	char		*path;

	path = getenv("PATH");
	if (!path)
		error_exit(EXIT_FAILURE, "Don't get Path");
	cmdfile = get_cmdfile(exec->cmd[0], path);
	if (!cmdfile)
		error_exit(COMMAND_NOT_FOUND, "command not found");
	free(exec->cmd[0]);
	exec->cmd[0] = cmdfile;
	if (execve(exec->cmd[0], exec->cmd, environ) == -1)
		perror_exit(EXIT_FAILURE, "execve");
}

static void	execve_command(t_cmd *exec)
{
	// if (check_builtins(exec))
	//	exec_builtins(exec->cmd);
	// else
	basic_command(exec);
}

static void	execve_main(t_cmd *exec)
{
	set_redirect(exec->redirect);
	if (exec->cmd)
		execve_command(exec);
	else
		exit(0);
}

static void	\
	connect_io_pipe(size_t i, size_t pipe_cnt, int pp[OPEN_MAX / 2][2])
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

static int	execve_system(t_cmd *exec, size_t cnt)
{
	size_t	i;
	int		pp[OPEN_MAX / 2][2];

	i = 0;
	if (cnt > OPEN_MAX / 2)
		perror_exit(EXIT_FAILURE, "pipe");
	while (i < cnt && cnt != 0)
	{
		if (i != cnt)
			set_pipe(pp[i]);
		exec->pid = fork();
		if (exec->pid == -1)
			perror_exit(EXIT_FAILURE, "fork");
		if (exec->pid == 0)
		{
			connect_io_pipe(i, cnt, pp);
			execve_main(exec);
		}
		if (i > 0)
			close_pipe(pp[i - 1]);
		exec = exec->piped_cmd;
		i ++;
	}
	return (0);
}

int	exection(t_cmd *cmd)
{
	heredoc_to_fd(cmd);
	execve_system(cmd, pipe_cnt(cmd));
	create_waitpid(cmd);
	cmd_lstfree(&cmd);
	return (0);
}
