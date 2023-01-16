/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 17:25:30 by tasano            #+#    #+#             */
/*   Updated: 2023/01/16 01:13:22 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void error_args(char *str1, char *str2)
{
	ft_putstr_fd("minish: exit: ", 2);
	ft_putstr_fd(str1, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(str2, 2);
}

void put_exit(char *err1, char *err2, int status)
{
	ft_putendl_fd("exit", 2);
	if (err1 && err2)
		error_args(err1, err2);
	exit(status);
}

int builtin_exit(size_t argc, char **argv)
{
	int status;
	long res;
	char *endptr;

	status = 0;
	if (2 < argc)
		ft_putendl_fd("minish: exit: too many arguments", 2);
	else if (argc == 1)
		put_exit(NULL, NULL, status);
	else
	{
		res = ft_strtol(argv[1], &endptr, 10);
		if (endptr && endptr[0])
			put_exit(argv[1], "numeric argument required", 255);
		else if (256 < res)
			put_exit(NULL, NULL, res % 256);
		else
			put_exit(NULL, NULL,(int)res);
	}
	return (0);
}