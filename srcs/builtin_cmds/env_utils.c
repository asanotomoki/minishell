/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 12:44:05 by tasano            #+#    #+#             */
/*   Updated: 2023/01/15 12:49:20 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t search_param(char **argv, char *param)
{
	size_t param_len;
	size_t i;

	param_len = ft_strlen(param);
	i = 0;
	while (*argv)
	{
		if (ft_strncmp(*argv, param, param_len) == 0)
			break;
		argv++;
		i++;
	}
	return (i);
}

char **get_env()
{
	extern char **environ;
	char **val;
	
	val = (char **)environ;
	return (val);
}