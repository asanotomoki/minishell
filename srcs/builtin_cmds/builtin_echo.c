/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 16:42:16 by tasano            #+#    #+#             */
/*   Updated: 2023/01/11 21:50:20 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_cmds.h"

int echo_cmd(char **argv, int option)
{
	size_t	i;

	i = 0;
	while (argv[i])
	{
		if (i != 0)
			printf(" ");
		printf("%s", argv[i]);
		i++;
	}
	if (option != N_OPTION)
		printf("\n");
	return (0);
}