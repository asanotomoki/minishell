/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiroaki <hiroaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 16:42:16 by tasano            #+#    #+#             */
/*   Updated: 2023/01/19 02:09:26 by hiroaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_cmds.h"
#include "libft.h"

int	builtin_echo(char **argv)
{
	size_t	i;
	int		option;

	option = 0;
	i = 1;
	if (argv[i] && ft_strncmp(argv[i], "-n", 3) == 0)
		option = 1;
	argv += i + option;
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
