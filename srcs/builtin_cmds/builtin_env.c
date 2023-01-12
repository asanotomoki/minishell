/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 17:25:12 by tasano            #+#    #+#             */
/*   Updated: 2023/01/16 01:39:11 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
int builtin_env()
{
	extern char **environ;
	char **val;
	size_t i;

	val = (char **)environ;
	i = 0;
	while (val[i])
	{
		printf("%s\n", val[i]);
		i++;
	}
	return (0);
}