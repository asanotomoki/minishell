/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanotomoki <asanotomoki@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 17:22:12 by asanotomoki       #+#    #+#             */
/*   Updated: 2022/11/28 00:24:14 by asanotomoki      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int get_cmd(char *cmd, char **envp, t_cmds *cmds)
{
	cmds->cmds = ft_split(cmd, ' ');
	if (!cmds->cmds || !cmds->cmds[0])
		return (err_msg("Error"));
	cmds->cmd_file = get_cmdfile(cmds->cmds[0], envp);
	if (!cmds->cmd_file)
	{
		free_args(cmds->cmds);
		return (1);
	}
	return (0);
}

int basic_cmd(char *cmd, char **envp)
{
	pid_t pid;
	t_cmds cmds;

	pid = fork();
	if (pid == 0)
	{
		if (get_cmd(cmd, envp, &cmds))
			return (1);
		if (execve(cmds.cmd_file, cmds.cmds, envp) == -1)
		{
			free_args(cmds.cmds);
			free(cmds.cmd_file);
			return (perr_msg("execve"));
		}
		free_args(cmds.cmds);
		free(cmds.cmd_file);
	}
	if (waitpid(pid, NULL, 0) == -1)
		return (perr_msg("waitpid"));
	return (0);
}
