/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 17:26:11 by tasano            #+#    #+#             */
/*   Updated: 2023/01/17 00:18:04 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include "builtin_cmds.h"
#include "util.h"

static int	set_env_join(char **environ, char *s, char *param)
{
	char	*value;
	char	*key;
	char	*tmp;
	size_t	index;

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
	free_strval(&param);
	free_strval(&key);
	return (0);
}

static int	set_env_val(char **environ, char *s, char *param)
{
	size_t	index;

	index = search_param(environ, param);
	if (!environ[index])
	{
		environ[index] = ft_strdup(s);
		environ[index + 1] = NULL;
	}
	if (environ[index])
	{
		free_strval(&environ[index]);
		environ[index] = ft_strdup(s);
	}
	free_strval(&param);
	return (0);
}

int	set_env(char *s)
{
	char	*param;

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

static int	put_env_declare(void)
{
	char	**environ;

	environ = get_env();
	while (*environ)
	{
		printf("declare -x %s\n", *environ);
		environ++;
	}
	return (0);
}

int	builtin_export(char **argv)
{
	int	status;
	int	res;

	argv++;
	res = 0;
	if (!*argv)
		return (put_env_declare());
	while (*argv)
	{
		status = set_env(*argv);
		if (status != 0)
			res = status;
		argv++;
	}
	return (res);
}
