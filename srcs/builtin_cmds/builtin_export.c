/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 17:26:11 by tasano            #+#    #+#             */
/*   Updated: 2023/01/16 15:36:47 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include "builtin_cmds.h"

int set_env_join(char **environ, char *s, char *param)
{
	char *value;
	char *key;
	char *tmp;
	size_t index;

	key = get_key(param);
	value = s + ft_strlen(param);
	index = search_param(environ, key);
	if (!environ[index])
	{
		environ[index] = ft_strdup(s);
		environ[index + 1] = NULL;
	}
	else
	{
		tmp = ft_strjoin(environ[index], value);
		free(environ[index]);
		environ[index] = tmp;
	}
	free(param);
	free(key);
	param = NULL;
	key = NULL;
	return (0);
}

int set_env_val(char **environ, char *s, char *param)
{
	size_t index;

	index = search_param(environ, param);
	if (!environ[index])
	{
		environ[index] = ft_strdup(s);
		environ[index + 1] = NULL;
	}
	if (environ[index])
	{
		free(environ[index]);
		environ[index] = ft_strdup(s);
	}
	free(param);
	param = NULL;
	return (0);
}

int set_env(char *s)
{
	char *param;

	if (!ft_strchr(s, '='))
		return (0);
	param = get_param(s);
	if (!param)
		return (1);
	else if (ft_strchr(param, '+'))
		return (set_env_join(get_env(), s, param));
	else
		return (set_env_val(get_env(), s, param));
	return (0);
}

int put_env_declare()
{
	char **environ;

	environ = get_env();
	while (*environ)
	{
		printf("declare -x %s\n", *environ);
		environ++;
	}
	return (0);
}

int builtin_export(char **argv)
{
	int status;

	argv++;
	if (!*argv)
		return (put_env_declare());
	while (*argv)
	{
		status = set_env(*argv);
		argv++;
	}
	return (status);
}