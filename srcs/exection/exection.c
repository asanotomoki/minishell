/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exection.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 21:06:06 by tasano            #+#    #+#             */
/*   Updated: 2023/01/21 18:27:09 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "libft.h"
#include "exec.h"
#include "util.h"
#include "minishell.h"

static void	basic_command(t_cmd *exec)
{
	char	*cmdfile;
	char	*path;

	path = get_env_char("PATH");
	if (!path)
		error_exit(127, exec->cmd[0], "No such file or directory");
	if (!exec->cmd[0][0] || exec->type == DOT)
		error_exit(COMMAND_NOT_FOUND, exec->cmd[0], "command not found");
	cmdfile = get_cmdfile(exec->cmd[0], path);
	check_cmdfile(cmdfile, exec->cmd[0]);
	free(exec->cmd[0]);
	exec->cmd[0] = cmdfile;
	if (execve(exec->cmd[0], exec->cmd, get_env_argv()) == -1)
		perror_exit(EXIT_FAILURE, exec->cmd[0]);
}

static void	execve_command(t_cmd *exec)
{
	if (check_builtin(exec))
		set_status(exec_builtin(exec));
	else
		basic_command(exec);
}

static void	execve_main(t_cmd *exec)
{
	if (set_redirect(exec->redirect))
		exit (EXIT_FAILURE);
	else if (exec->cmd)
		execve_command(exec);
	else
		exit(EXIT_SUCCESS);
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
			exit(get_status());
		}
		if (i > 0)
			close_pipe(pp[i - 1]);
		exec = exec->piped_cmd;
		i++;
	}
	return (0);
}

int	exection(t_cmd *cmd)
{
	g_shell.status = 0;
	set_heredocument(cmd);
	if (g_shell.status)
		return (1);
	if (!cmd->piped_cmd && check_builtin(cmd))
		exec_builtin_parent(cmd);
	else
	{
		execve_system(cmd, pipe_cnt(cmd));
		create_waitpid(cmd);
	}
	return (0);
}
