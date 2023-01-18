/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiroaki <hiroaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 21:37:10 by hiroaki           #+#    #+#             */
/*   Updated: 2022/12/30 15:17:57 by hiroaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	duplicate_fd(t_parse_ast *ast, int i, int pipe_cnt)
{
	if (i == pipe_cnt)
	{
		if (dup2(ast->prev_pipe->pfd[0], STDIN_FILENO) != STDIN_FILENO)
			exit(2);
		close(ast->prev_pipe->pfd[0]);
		close(ast->prev_pipe->pfd[1]);
	}
	else
	{
		if (dup2(ast->prev_pipe->pfd[0], STDIN_FILENO) != STDIN_FILENO)
			exit(3);
		if (dup2(ast->pfd[1], STDOUT_FILENO) != STDOUT_FILENO)
			exit(4);
		close(ast->pfd[0]);
		close(ast->pfd[1]);
		close(ast->prev_pipe->pfd[0]);
		close(ast->prev_pipe->pfd[1]);
	}
}
#include <string.h>

void	exec_pipe(t_parse_ast *ast, int i, int pipe_cnt, char *envp[])
{
	duplicate_fd(ast, i, pipe_cnt);
	execve(ast->cmd_path, ast->cmd, envp);
}

void	connect_pipe(t_parse_ast *ast, int pipe_cnt, char *envp[])
{
	int			i;
	extern int	errno;
	pid_t		pid;

	i = 0;
	while (ast)
	{
		if (i < pipe_cnt && pipe(ast->pfd) < 0)
			exit(5);
		pid = fork();
		if (pid == -1)
			exit(6);
		if (pid != 0)
			dprintf(2, "%d\n", pid);
		if (pid == 0)
		{
			exec_pipe(ast, i, pipe_cnt, envp);
			dprintf(2, "errno = %d\n", errno);
			exit(EXIT_SUCCESS);
		}
		waitpid(pid, NULL, -1);
		ast = ast->next_pipe;
		i++;
	}
}

int	main(int argc, char **argv, char *envp[])
{
	(void)argc;
	(void)argv;
	int			i;
	int			pipe_cnt;
	char		buf[100];
	t_parse_ast	*ast;
	t_parse_ast	*head;
	t_parse_ast	*new;

	i = 0;
	pipe_cnt = 1;

	ast = malloc(sizeof(t_parse_ast));
	ast->prev_pipe = NULL;
	ast->next_pipe = NULL;
	head = ast;

	while (i < pipe_cnt)
	{
		new = malloc(sizeof(t_parse_ast));
		new->prev_pipe = ast;
		ast->next_pipe = new;
		new->next_pipe = NULL;
		if (i == 0)
		{
			ast->cmd_path = "/bin/echo";
			ast->cmd[0] = "echo";
			ast->cmd[1] = "a\nb\n";
			ast->cmd[2] = NULL;
		}
		if (i == 1)
		{
			ast->cmd_path = "/bin/grep";
			ast->cmd[0] = "grep";
			ast->cmd[1] = "b";
			ast->cmd[2] = NULL;
		}

		ast = ast->next_pipe;
		i++;
	}
	connect_pipe(head, pipe_cnt, envp);
	return (7);
}
