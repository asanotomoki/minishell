/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exection.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiroaki <hiroaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 21:06:06 by tasano            #+#    #+#             */
/*   Updated: 2023/01/13 22:06:57 by hiroaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "exec.h"
#include <fcntl.h>
#include "libft.h"

void basic_command(t_cmd *exec, char **envp)
{
	char *cmdfile;
	char *path;

	path = getenv("PATH");
	if (!path)
		error_exit(EXIT_FAILURE, "Don't get Path");
	cmdfile = get_cmdfile(exec->cmd[0], path);
	if (!cmdfile)
		error_exit(COMMAND_NOT_FOUND, "command not found");
	free(exec->cmd[0]);
	exec->cmd[0] = cmdfile;
	if (execve(exec->cmd[0], exec->cmd, envp) == -1)
		perror_exit(EXIT_FAILURE, "execve");
}

void execve_command(t_cmd *exec, char **envp)
{
	// if (check_builtins(exec))
	//	exec_builtins(exec->cmd);
	// else
	basic_command(exec, envp);
}

void execve_main(t_cmd *exec, char **envp)
{
	set_redirect(exec->redirect);
	if (exec->cmd)
		execve_command(exec, envp);
	else
		exit(0);
}

int execve_system(t_cmd *exec, char **envp)
{
	pid_t pid;
	int pp[2];

	if (!exec->piped_cmd)
		execve_main(exec, envp);
	else
	{
		set_pipe(pp);
		pid = fork();
		if (pid == -1)
			perror_exit(EXIT_FAILURE, "fork");
		else if (pid == 0)
		{
			set_dup2(pp[1], STDOUT_FILENO);
			close_pipe(pp);
			execve_system(exec->piped_cmd, envp);
		}
		else
		{
			set_dup2(pp[0], STDIN_FILENO);
			close_pipe(pp);
			execve_main(exec, envp);
		}
	}
	return (0);
}

int exection(t_cmd *cmd, char **envp)
{
	pid_t	pid;

	if (!cmd)
		return (1);
	cmd = convert_cmd(cmd);
	// if (!cmd->piped_cmd && check_builtins())
	//	execve_main(cmd, envp);
	// else
	//{
	pid = fork();
	if (pid == 0)
		execve_system(cmd, envp);
	// exitしたらダメかも？
	else if (pid == -1)
		perror_exit(EXIT_FAILURE, "fork");
	else
		set_waitpid(pid);
	//}
	cmd_lstfree(&cmd);
	return (0);
}
