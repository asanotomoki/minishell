/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 21:59:00 by tasano            #+#    #+#             */
/*   Updated: 2023/01/16 23:13:19 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "exec.h"
#include <stdlib.h>
#include "libft.h"

size_t	pipe_cnt(t_cmd *cmd)
{
	size_t	len;

	len = 0;
	while (cmd)
	{
		len ++;
		cmd = cmd->piped_cmd;
	}
	return (len);
}

void perror_exit(int status, char *msg)
{
	ft_putstr_fd(SHELL, 2);
	ft_putstr_fd(": " , 2);
	perror(msg);
	exit (status);
}

void error_exit(int status, char *msg)
{
	ft_putstr_fd(SHELL, 2);
	ft_putstr_fd(": " , 2);
	ft_putendl_fd(msg, 2);
	exit (status);
}

t_cmd *convert_cmd(t_cmd *lst)
{
	t_cmd *content;
	t_cmd *init;
	t_cmd *top;

	init = lst;
	top = lst;
	while (init->piped_cmd)
	{
		content = init->piped_cmd;
		init->piped_cmd = content->piped_cmd;
		content->piped_cmd = top;
		top = content;
	}
	return (top);
}