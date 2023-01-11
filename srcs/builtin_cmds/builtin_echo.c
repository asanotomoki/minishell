/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 16:42:16 by tasano            #+#    #+#             */
/*   Updated: 2023/01/12 00:33:38 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_cmds.h"
#include "libft.h"

int builtin_echo(char **argv)
{
	size_t	i;
	int		option;

	option = 0;
	if (argv[1] && ft_strncmp(argv[1], "-n", 3) == 0)
		option = 1;
	argv += 1 + option;
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