/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 16:42:16 by tasano            #+#    #+#             */
/*   Updated: 2023/01/24 14:20:57 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_cmds.h"
#include "libft.h"
#include <stdbool.h>

static bool	n_option(char *str)
{
	if (*str != '-')
		return (false);
	str++;
	while (*str)
	{
		if (*str != 'n')
			return (false);
		str++;
	}
	return (true);
}

int	builtin_echo(char **argv)
{
	size_t	i;
	int		option;

	option = 0;
	i = 1;
	while (argv[i] && n_option(argv[i]))
	{
		option = 1;
		i++;
	}
	argv += i;
	i = 0;
	while (argv[i])
	{
		if (i != 0)
			ft_putchar_fd(' ', 1);
		ft_putstr_fd(argv[i], 1);
		i++;
	}
	if (!option)
		ft_putchar_fd('\n', 1);
	return (0);
}
