/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiroaki <hiroaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 21:59:00 by tasano            #+#    #+#             */
/*   Updated: 2023/01/18 21:11:39 by hiroaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"

int	check_cmdfile(char *filename, char *param)
{
	struct stat	s_st;
	int			result;

	result = stat(filename, &s_st);
	if (result == -1)
		error_exit(COMMAND_NOT_FOUND, param, "command not found");
	if (S_ISDIR(s_st.st_mode))
	{
		free_strval(&filename);
		error_exit(126, param, "is a directory");
	}
	if ((s_st.st_mode & S_IXUSR) == 0)
	{
		free_strval(&filename);
		error_exit(126, param, "Permission denied");
	}
	return (0);
}

void	perror_exit(int status, char *msg)
{
	ft_putstr_fd(SHELL, 2);
	ft_putstr_fd(": ", 2);
	perror(msg);
	exit(status);
}

void	error_exit(int status, char *param, char *msg)
{
	ft_putstr_fd(SHELL, 2);
	ft_putstr_fd(": ", 2);
	if (param)
	{
		ft_putstr_fd(param, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(msg, 2);
	exit(status);
}

void	connect_io_pipe(size_t i, size_t pipe_cnt, int pp[OPEN_MAX / 2][2])
{
	if (pipe_cnt == 1)
		return ;
	if (i == 0)
		set_stdout(pp[i]);
	else if (i == pipe_cnt - 1)
		set_stdin(pp[i - 1]);
	else
	{
		set_stdout(pp[i]);
		set_stdin(pp[i - 1]);
	}
}

int	rl_heredoc_event(void)
{
	if (g_shell.sig_no == 0)
		return (0);
	g_shell.sig_no = 0;
	g_shell.status = 1;
	g_shell.heredoc_interrupted = 1;
	rl_done = 1;
	return (0);
}
