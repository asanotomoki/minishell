/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 21:13:24 by tasano            #+#    #+#             */
/*   Updated: 2023/01/16 21:21:51 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include "builtin_cmds.h"

int exec_builtin(t_cmd *cmd)
{
	if (!cmd->cmd)
		return (0);
	if (ft_strncmp(cmd->cmd[0], "echo", 5) == 0)
		return (builtin_echo(cmd->cmd));
	else if (ft_strncmp(cmd->cmd[0], "cd", 3) == 0)
		return (builtin_cd(cmd->cmd));
	else if (ft_strncmp(cmd->cmd[0], "pwd", 4) == 0)
		return (builtin_pwd());
	else if (ft_strncmp(cmd->cmd[0], "export", 7) == 0)
		return (builtin_export(cmd->cmd));
	else if (ft_strncmp(cmd->cmd[0], "unset", 5) == 0)
		return (builtin_unset(cmd->cmd));
	else if (ft_strncmp(cmd->cmd[0], "env", 4) == 0)
		return (builtin_env());
	else if (ft_strncmp(cmd->cmd[0], "exit", 5) == 0)
		return (builtin_exit(cmd->argc, cmd->cmd));
	return (0);
}

int check_builtin(t_cmd *cmd)
{
	if (!cmd->cmd)
		return (0);
	if (ft_strncmp(cmd->cmd[0], "echo", 5) == 0)
		return (1);
	else if (ft_strncmp(cmd->cmd[0], "cd", 3) == 0)
		return (1);
	else if (ft_strncmp(cmd->cmd[0], "pwd", 4) == 0)
		return (1);
	else if (ft_strncmp(cmd->cmd[0], "export", 7) == 0)
		return (1);
	else if (ft_strncmp(cmd->cmd[0], "unset", 5) == 0)
		return (1);
	else if (ft_strncmp(cmd->cmd[0], "env", 4) == 0)
		return (1);
	else if (ft_strncmp(cmd->cmd[0], "exit", 5) == 0)
		return (1);
	return (0);
}