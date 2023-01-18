/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiroaki <hiroaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 17:10:17 by asanotomoki       #+#    #+#             */
/*   Updated: 2023/01/19 01:23:36 by hiroaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include "minishell.h"

int	perr_msg(char *msg)
{
	ft_putstr_fd(SHELL, 2);
	ft_putstr_fd(": ", 2);
	perror(msg);
	return (1);
}

int	err_msg(char *param, char *msg, int status)
{
	ft_putstr_fd(SHELL, 2);
	ft_putstr_fd(": ", 2);
	if (param)
	{
		ft_putstr_fd(param, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(msg, 2);
	return (status);
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
