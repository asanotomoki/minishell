/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 21:13:24 by tasano            #+#    #+#             */
/*   Updated: 2023/01/21 08:11:42 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include "libft.h"
#include "parser.h"
#include "builtin_cmds.h"
#include "exec.h"
#include "../../includes/minishell.h"

int	exec_builtin(t_cmd *cmd)
{
	if (!cmd->cmd)
		return (0);
	if (cmd->type == MINI_ECHO)
		return (builtin_echo(cmd->cmd));
	if (cmd->type == MINI_CD)
		return (builtin_cd(cmd->cmd));
	if (cmd->type == MINI_PWD)
		return (builtin_pwd());
	if (cmd->type == MINI_EXPORT)
		return (builtin_export(cmd->cmd));
	if (cmd->type == MINI_UNSET)
		return (builtin_unset(cmd->cmd));
	if (cmd->type == MINI_ENV)
		return (builtin_env());
	if (cmd->type == MINI_EXIT)
		return (builtin_exit(cmd->argc, cmd->cmd));
	return (0);
}

bool	check_builtin(t_cmd *cmd)
{
	if (!cmd->cmd)
		return (false);
	if (ft_strcmp(cmd->cmd[0], "echo") == 0)
		cmd->type = MINI_ECHO;
	else if (ft_strcmp(cmd->cmd[0], "cd") == 0)
		cmd->type = MINI_CD;
	else if (ft_strcmp(cmd->cmd[0], "pwd") == 0)
		cmd->type = MINI_PWD;
	else if (ft_strcmp(cmd->cmd[0], "export") == 0)
		cmd->type = MINI_EXPORT;
	else if (ft_strcmp(cmd->cmd[0], "unset") == 0)
		cmd->type = MINI_UNSET;
	else if (ft_strcmp(cmd->cmd[0], "env") == 0)
		cmd->type = MINI_ENV;
	else if (ft_strcmp(cmd->cmd[0], ".") == 0 || \
			ft_strcmp(cmd->cmd[0], "..") == 0)
		cmd->type = DOT;
	else if (ft_strcmp(cmd->cmd[0], "exit") == 0)
		cmd->type = MINI_EXIT;
	if (cmd->type != 0 && cmd->type != DOT)
		return (true);
	return (false);
}

void	close_fd(t_redirect *redirect, int backup, int backupin)
{
	t_redirect	*tmp;

	tmp = redirect;
	while (tmp)
	{
		if (tmp->fd != -1)
			close(tmp->fd);
		tmp = tmp->next;
	}
	dup2(backup, 1);
	close(backup);
	dup2(backupin, STDIN_FILENO);
	close(backupin);
}

void	exec_builtin_parent(t_cmd *cmd)
{
	int	backup_out;
	int	backup_in;

	backup_out = dup(STDOUT_FILENO);
	backup_in = dup(STDIN_FILENO);
	if (set_redirect(cmd->redirect))
	{
		close_fd(cmd->redirect, backup_out, backup_in);
		return ;
	}
	set_status(exec_builtin(cmd));
	close_fd(cmd->redirect, backup_out, backup_in);
}
