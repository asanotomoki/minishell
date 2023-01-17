/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiroaki <hiroaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 15:02:35 by hiroaki           #+#    #+#             */
/*   Updated: 2023/01/18 00:13:55 by hiroaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

size_t	pipe_cnt(t_cmd *cmd)
{
	size_t	cnt;

	cnt = 0;
	while (cmd)
	{
		cnt ++;
		cmd = cmd->piped_cmd;
	}
	return (cnt);
}

void	set_stdout(int pp[2])
{
	set_dup2(pp[1], STDOUT_FILENO);
	close_pipe(pp);
}

void	set_stdin(int pp[2])
{
	set_dup2(pp[0], STDIN_FILENO);
	close_pipe(pp);
}

bool	discontinue(char *line, char *delimiter)
{
	if (g_shell.heredoc_sig_flag)
	{
		rl_cleanup_after_signal();
		rl_free_line_state();
		return (true);
	}
	if (ft_strcmp(line, delimiter) == 0)
		return (true);
	return (false);
}

char	*joint_carriage_return(char *line)
{
	char	*new_line;

	new_line = ft_strjoin(line, "\n");
	free(line);
	if (new_line == NULL)
		return (NULL);
	return (new_line);
}
