/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiroaki <hiroaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 21:37:10 by hiroaki           #+#    #+#             */
/*   Updated: 2023/01/14 02:54:57 by hiroaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "exec.h"
#include "../parser/parser.h"
#include <libc.h>
#include <string.h>

typedef struct s_parse_ast
{
	pid_t				pfd[2];
	struct s_parse_ast	next_pipe;
} 	t_parse_ast;

void	ft_exit(char *msg, int status)
{
	perror(msg);
	exit(status);
}

int	creat_pipe(t_parse_ast *ast)
{
	int	i;

	i = 0;
	while (ast)
	{
		if (pipe(ast->pfd) < 0)
			ft_exit("pipe", EXIT_FAILURE);
		i++;
		ast = ast->next_pipe;
	}
	return (i);
}

t_parse_ast	*init_t_parse_ast(void)
{
	t_parse_ast	*ast;
	t_parse_ast	*new;
	t_parse_ast	*new2;

	ast = malloc(sizeof(t_parse_ast));
	new = malloc(sizeof(t_parse_ast));
	new2 = malloc(sizeof(t_parse_ast));

	ast->prev_pipe = NULL;
	ast->next_pipe = new;
	new->prev_pipe = ast;
	new->next_pipe = new2;
	new2->prev_pipe = new;
	new2->next_pipe = NULL;

	ast->cmd = malloc(sizeof(t_parse_ast *) * 2);
	ast->cmd[0] = strdup("cat");
	ast->cmd[1] = NULL;
	ast->cmd_path = strdup("/bin/cat");

	new->cmd = malloc(sizeof(t_parse_ast *) * 2);
	new->cmd[0] = strdup("ls");
	new->cmd[1] = NULL;
	new->cmd_path = strdup("/usr/bin/grep");

	new2->cmd = malloc(sizeof(t_parse_ast *) * 3);
	new2->cmd[0] = strdup("grep");
	new2->cmd[1] = strdup("p");
	new2->cmd[2] = NULL;
	new2->cmd_path = strdup("/usr/bin/grep");

	return (ast);
}

void	dup_fd_of_first_child(t_parse_ast *ast, char *envp[])
{
	if (dup2(ast->pfd[1], STDOUT_FILENO) != STDOUT_FILENO)
		ft_exit("dup2", EXIT_FAILURE);
	close(ast->pfd[0]);
	close(ast->pfd[1]);
}

void	dup_fd_of_last_child(t_parse_ast *ast, char *envp[])
{
	if (dup2(ast->prev_pipe->pfd[0], STDIN_FILENO) != STDIN_FILENO)
		ft_exit("dup2", EXIT_FAILURE);
	close(ast->prev_pipe->pfd[0]);
	close(ast->prev_pipe->pfd[1]);
}

void	dup_fd_of_mid_child(t_parse_ast *ast, char *envp[])
{
	if (dup2(ast->pfd[1], STDOUT_FILENO) != STDOUT_FILENO || \
		dup2(ast->prev_pipe->pfd[0], STDIN_FILENO) != STDIN_FILENO)
		ft_exit("dup2", EXIT_FAILURE);
	close(ast->pfd[0]);
	close(ast->pfd[1]);
	close(ast->prev_pipe->pfd[0]);
	close(ast->prev_pipe->pfd[1]);
}

void	exec_child_process(t_parse_ast *ast, char *envp[], int i, int pipe_cnt)
{
	if (i == 0)
		dup_fd_of_first_child(ast, envp);
	else if (i == pipe_cnt - 1)
		dup_fd_of_last_child(ast, envp);
	else
		dup_fd_of_mid_child(ast, envp);
	execve(ast->cmd_path, ast->cmd, envp);
}

int	exec_cmd(t_parse_ast *ast, char *envp[], int pipe_cnt)
{
	int	i;
	int	status;

	if (pipe_cnt == 0)
		return (execve(ast->cmd_path, ast->cmd, envp));
	status = 0;
	i = 0;
	while (ast)
	{
		ast->pid = fork();
		if (ast->pid < 0)
			ft_exit("fork", EXIT_FAILURE);
		if (ast->pid == 0)
			exec_child_process(ast, envp, i, pipe_cnt);
		if (i > 0)
		{
			close(ast->prev_pipe->pfd[0]);
			close(ast->prev_pipe->pfd[1]);
		}
		if (waitpid(ast->pid, NULL, 0) < 0)
			ft_exit("waitpid", EXIT_FAILURE);
		i++;
		ast = ast->next_pipe;
	}
	return (status);
}

int	main(int argc, char **argv, char *envp[])
{
	int			pipe_cnt;
	int			status;
	t_parse_ast	*ast;

	status = 0;
	ast = init_t_parse_ast();
	pipe_cnt = creat_pipe(ast);
	status = exec_cmd(ast, envp, pipe_cnt);
	return (status);
}
