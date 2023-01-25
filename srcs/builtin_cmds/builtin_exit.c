/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 17:25:30 by tasano            #+#    #+#             */
/*   Updated: 2023/01/25 23:03:07 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include "minishell.h"
#include "util.h"

static void	exit_put_error(char *str1, char *str2)
{
	ft_putstr_fd(SHELL, 2);
	ft_putstr_fd(": exit: ", 2);
	ft_putstr_fd(str1, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(str2, 2);
}

static void	put_exit(char *err1, char *err2, int status)
{
	ft_putendl_fd("exit", 2);
	if (err1 && err2)
		exit_put_error(err1, err2);
	ft_lstclear(&g_shell.env, free);
	exit(status);
}

int	builtin_exit(char **argv)
{
	long	res;
	char	*endptr;
	size_t	argc;

	argc = cnt_argc(argv);
	if (2 < argc)
	{
		ft_putendl_fd("exit", 2);
		ft_putendl_fd("minish: exit: too many arguments", 2);
		return (1);
	}
	else if (argc == 1)
		put_exit(NULL, NULL, get_status());
	else
	{
		res = ft_strtol(argv[1], &endptr, 10);
		if (endptr && endptr[0])
			put_exit(argv[1], "numeric argument required", 255);
		else if (256 < res)
			put_exit(NULL, NULL, res % 256);
		else
			put_exit(NULL, NULL, res);
	}
	return (0);
}
