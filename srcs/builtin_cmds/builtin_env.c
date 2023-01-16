/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 17:25:12 by tasano            #+#    #+#             */
/*   Updated: 2023/01/16 15:51:39 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "builtin_cmds.h"

int	builtin_env(void)
{
	char	**val;
	size_t	i;

	val = get_env();
	i = 0;
	while (val[i])
	{
		printf("%s\n", val[i]);
		i++;
	}
	return (0);
}
