/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 16:52:32 by asanotomoki       #+#    #+#             */
/*   Updated: 2022/11/22 12:18:03 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_cmds
{
	char *cmd_file;
	char **cmds;
}	t_cmds;


static int get_cmd(char	*cmd, char **envp, t_cmds *cmds)
{
	cmds->cmds = ft_split(cmd, ' ');
	if (!cmds->cmds || !cmds->cmds[0])
		return (err_msg("Error"));
	cmds->cmd_file = get_cmdfile(cmds->cmds[0], envp);
	if (!cmds->cmd_file)
		return (err_msg("no such file"));
	return (0);
}

int	basic_cmd(char *cmd, char **envp)
{
	pid_t pid;
	t_cmds cmds;

	get_cmd(cmd, envp, &cmds);
	pid = fork();
	if (pid == 0)
	{
		if (execve(cmds.cmd_file, cmds.cmds, envp) == -1)
		return (perr_msg("execve"));
	}
	free(cmds.cmd_file);
	free_args(cmds.cmds);
	if (waitpid(pid, NULL, 0) == -1)
		return (perr_msg("waitpid"));
	return (0);
}