/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exection.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 21:06:06 by tasano            #+#    #+#             */
/*   Updated: 2023/01/17 14:48:03 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"
#include "util.h"
#include <fcntl.h>
#include "libft.h"

int	check_cmdfile(char	*filename, char	*param)
{
	struct stat	s_st;
	int			result;

	if (!filename)
		error_exit(COMMAND_NOT_FOUND, param, "command not found");
	result = stat(filename, &s_st);
	if (result == -1)
		error_exit(COMMAND_NOT_FOUND, param, "command not found");
	if (S_ISDIR(s_st.st_mode))
	{
		free_strval(&filename);
		error_exit(126, param, "is a directory");
	}
	if ((s_st.st_mode & S_IXUSR) == 0)
	{
		free_strval(&filename);
		error_exit(126, param, "Permission denied");
	}
	return (0);
}

void	basic_command(t_cmd *exec)
{
	char	*cmdfile;

	cmdfile = get_cmdfile(exec->cmd[0], getenv("PATH"));
	check_cmdfile(cmdfile, exec->cmd[0]);
	free(exec->cmd[0]);
	exec->cmd[0] = cmdfile;
	if (execve(exec->cmd[0], exec->cmd, get_env()) == -1)
		perror_exit(EXIT_FAILURE, "execve");
}

void	execve_command(t_cmd *exec)
{
	if (check_builtin(exec))
		set_status(exec_builtin(exec));
	else
		basic_command(exec);
}

void	execve_main(t_cmd *exec)
{
	set_redirect(exec->redirect);
	if (exec->cmd)
		execve_command(exec);
	else
		exit(0);
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
		i++;
	}
	return (0);
}

int	exection(t_cmd *cmd)
{
	heredoc_to_fd(cmd);
	if (!cmd->piped_cmd && check_builtin(cmd))
		execve_main(cmd);
	else
	{
		execve_system(cmd, pipe_cnt(cmd));
		create_waitpid(cmd);
	}
	cmd_lstfree(&cmd);
	return (0);
}
