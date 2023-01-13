/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exection.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 21:06:06 by tasano            #+#    #+#             */
/*   Updated: 2023/01/14 04:18:17 by tasano           ###   ########.fr       */
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

void set_stdout(int pp[2])
{
	set_dup2(pp[1], STDOUT_FILENO);
	close_pipe(pp);
}
void set_stdin(int pp[2])
{
	set_dup2(pp[0], STDIN_FILENO);
	close_pipe(pp);
}

int execve_system(t_cmd *exec, size_t len, char **envp)
{
	int		pp[len][2];
	size_t	i;

	i = 0;
	while (i < len && len != 0)
	{
		if (i != len)
			set_pipe(pp[i]);
		exec->pid = fork();
		if (exec->pid == -1)
			perror_exit(EXIT_FAILURE, "fork");
		else if (exec->pid == 0)
		{
			if (i == 0)
				set_stdout(pp[i]);
			else if (i == len - 1)
				set_stdin(pp[i - 1]);
			else if (i != 0 && i != len - 1)
			{
				set_stdout(pp[i]);
				set_stdin(pp[i - 1]);
			}
			execve_main(exec, envp);
		}
		if (i > 0)
			close_pipe(pp[i - 1]);
		exec = exec->piped_cmd;
		i ++;
	}
	return (0);
}

int exection(t_cmd *cmd, char **envp)
{
	//pid_t pid
	//cmd = convert_cmd(cmd);
	//// if (!cmd->piped_cmd && check_builtins())
	////	execve_main(cmd, envp);
	//// else
	////{
	//pid = fork();
	//if (pid == 0)
	//	execve_system(cmd, envp);
	//// exitしたらダメかも？
	//else if (pid == -1)
	//	perror_exit(EXIT_FAILURE, "fork");
	//else
	//	set_waitpid(pid);
	////}
	//cmd_lstfree(&cmd);

	execve_system(cmd, pipe_cnt(cmd), envp);
	create_waitpid(cmd);
	cmd_lstfree(&cmd);
	return (0);
}
