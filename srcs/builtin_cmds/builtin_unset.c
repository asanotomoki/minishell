/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 17:26:24 by tasano            #+#    #+#             */
/*   Updated: 2023/01/16 01:40:58 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include "builtin_cmds.h"

void clear_val(char **environ, size_t i)
{
	if (!environ[i])
		return ;
	free(environ[i]);
	environ[i] = NULL;
	while (environ[i + 1])
	{
		environ[i] = environ[i + 1];
		environ[i + 1] = NULL;
		i++;
	}
}

int check_param(char *param)
{
	while (*param)
	{
		if (!ft_isalnum(*param) && *param != '_')
			return (1);
		param++;
	}
	return (0);
}

int unset_env(char **environ, char *param)
{
	char *param_search;
	size_t	i;

	if (check_param(param))
		ft_putendl_fd("not a valid identifier" ,2);
	param_search = ft_strjoin(param, "=");
	i = search_param(environ, param_search);
	if (environ[i])
		clear_val(environ, i);
	free(param_search);
	param_search = NULL;
	return (0);
}

int builtin_unset(char **argv)
{
	extern char **environ;
	char **val;
	int status;

	argv++;
	val = (char **)environ;
	if (!*argv)
		return (0);
	while (*argv)
	{
		status = unset_env(val, *argv);
		argv++;
	}
	return (status);
}