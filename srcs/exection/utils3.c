/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 21:59:00 by tasano            #+#    #+#             */
/*   Updated: 2023/01/17 04:05:40 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"

void	perror_exit(int status, char *msg)
{
	ft_putstr_fd(SHELL, 2);
	ft_putstr_fd(": ", 2);
	perror(msg);
	exit (status);
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
	exit (status);
}

void	\
connect_io_pipe(size_t i, size_t pipe_cnt, int pp[OPEN_MAX / 2][2])
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
