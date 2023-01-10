/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exection.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 21:06:06 by tasano            #+#    #+#             */
/*   Updated: 2023/01/11 00:36:05 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "exec.h"
#include <fcntl.h>
#include "libft.h"

static char **get_paths(char *path)
{
	char **paths;

	paths = ft_split(path, ':');
	if (!paths)
		return (NULL);
	return (paths);
}

static char *find_cmdfile(char *cmd, char **cmd_paths)
{
	char *tmp;
	char *cmd_path;
	size_t i;

	i = 0;
	while (cmd_paths[i])
	{
		tmp = ft_strjoin(cmd_paths[i], "/");
		if (!tmp)
			return (NULL);
		cmd_path = ft_strjoin(tmp, cmd);
		if (!cmd_path)
			return (NULL);
		free(tmp);
		if (access(cmd_path, X_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		i++;
	}
	return (NULL);
}

static char *relative_path(char *cmd)
{
	if (!access(cmd, X_OK))
		return (ft_strdup(cmd));
	else
	{
		printf("command not found");
		return (NULL);
	}
}

static char *absolute_path(char *cmd, char *path)
{
	char **cmd_paths;
	char *cmd_file;

	cmd_paths = get_paths(path);
	if (!cmd_paths)
		return (NULL);
	cmd_file = find_cmdfile(cmd, cmd_paths);
	if (!cmd_file)
	{
		// free_args(cmd_paths);
		return (NULL);
	}
	// free_args(cmd_paths);
	return (cmd_file);
}

char *get_cmdfile(char *cmd, char *path)
{
	if (ft_strchr(cmd, '/'))
		return (relative_path(cmd));
	else
		return (absolute_path(cmd, path));
}

t_parse_ast *convert_cmd(t_cmd *cmd)
{
	t_parse_ast *content;
	t_parse_ast *execlst;

	execlst = NULL;
	while (cmd)
	{
		content = execlst_new(cmd);
		if (!content)
			return (NULL);
		execlst = execlst_addfront(&execlst, content);
		cmd = cmd->piped_cmd;
	}
	return (execlst);
}

void set_inredirect(t_redirect *redirect)
{
	int new_fd;

	while (redirect)
	{
		new_fd = open(redirect->filename, O_RDONLY | O_CLOEXEC);
		if (new_fd < 0)
			perror("in redirect");
		// error修正
		if (dup2(new_fd, STDIN_FILENO) == -1)
			exit(1);
		redirect = redirect->next;
	}
}

void set_outredirect(t_redirect *redirect)
{
	int new_fd;

	while (redirect)
	{
		if (redirect->type == OUTREDIRECT)
			new_fd = open(redirect->filename, O_WRONLY | O_CREAT | O_TRUNC | O_CLOEXEC, 0644);
		else if (redirect->type == OUTADDITION)
			new_fd = open(redirect->filename, O_WRONLY | O_CREAT | O_CLOEXEC | O_APPEND, 0644);
		// error部分修正必須
		if (new_fd == -1)
			perror("output file");
		if (dup2(new_fd, STDOUT_FILENO) == -1)
			exit(1);
		redirect = redirect->next;
	}
}

void set_pipe(int pp[2])
{
	// if (exec->next_pipe)
	//{
	if (pipe(pp) == -1)
		perror("pipe");
	//}
}

void close_pipe(int pp[2])
{
	close(pp[0]);
	close(pp[1]);
}

void execve_command(t_parse_ast *exec, char **envp)
{
	char *cmdfile;
	char *path;

	// if (check_builtins(exec))
	//	exec_builtins(exec->cmd);
	path = getenv("PATH");
	// error改善
	if (!path)
		exit(1);
	cmdfile = get_cmdfile(exec->cmd[0], path);
	if (!cmdfile)
		exit(1);
	free(exec->cmd[0]);
	exec->cmd[0] = cmdfile;
	if (execve(exec->cmd[0], exec->cmd, envp) == -1)
		perror("execve");
}

void execve_main(t_parse_ast *exec, char **envp)
{
	set_inredirect(exec->input);
	set_outredirect(exec->output);
	if (exec->cmd)
		execve_command(exec, envp);
	exit(0);
}

int execve_system(t_parse_ast *exec, char **envp)
{
	pid_t pid;
	int pp[2];

	if (!exec->next_pipe)
		execve_main(exec, envp);
	else
	{
		if (pipe(pp) == -1)
			perror("pipe");
		pid = fork();
		if (pid == -1)
			exit(1);
		else if (pid == 0)
		{
			if (dup2(pp[1], STDOUT_FILENO) == -1)
				perror("out dup");
			close_pipe(pp);
			execve_system(exec->next_pipe, envp);
		}
		else
		{
			if (dup2(pp[0], STDIN_FILENO) == -1)
				perror("IN dup");
			close_pipe(pp);
			execve_main(exec, envp);
		}
	}
	// waitpid(pid, NULL, 0);
	return (0);
}

int exection(t_cmd *cmd, char **envp)
{
	t_parse_ast *execlst;
	pid_t pid;

	execlst = convert_cmd(cmd);
	if (!execlst)
		return (1);
	//if (!execlst->next_pipe)
	//	execve_main(execlst, envp);
	else
	{
		pid = fork();
		if (pid == 0)
			execve_system(execlst, envp);
		else if (pid == -1)
			exit(1);
		else
			waitpid(pid, NULL, 0);
	}
	// freelst();
	return (0);
}
