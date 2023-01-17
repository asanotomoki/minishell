/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiroaki <hiroaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 21:13:24 by tasano            #+#    #+#             */
/*   Updated: 2023/01/17 18:01:07 by hiroaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include "builtin_cmds.h"
#include "../../includes/minishell.h"
#include <errno.h>

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
