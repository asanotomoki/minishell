/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 17:26:11 by tasano            #+#    #+#             */
/*   Updated: 2023/01/15 06:34:03 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char *get_param(char *val)
{
	size_t i;
	char *param;

	i = 0;
	while (val[i] && val[i] != '=')
	{
		if (!ft_isalnum(val[i]) &&  val[i] != '_' && ft_strncmp(val + i, "+=", 2))
		{
			ft_putendl_fd("not a valid identifier", 2);
			return (NULL);
		}
		i++;
	}
	param = ft_substr(val, 0, i + 1);
	if (!param)
		perror("malloc");
	return (param);
}

size_t search_param(char **argv, char *param)
{
	size_t param_len;
	size_t i;

	param_len = ft_strlen(param);
	i = 0;
	while (*argv)
	{
		if (ft_strncmp(*argv, param, param_len) == 0)
			break ;
		argv++;
		i++;
	}
	return (i);
}

char *set_key(char *param)
{
	size_t key_len;
	char	*key;

	key_len = ft_strlen(param);
	key = (char *)malloc(sizeof(char) * key_len);
	ft_bzero(key, key_len * sizeof(char));
	if (!key)
		return (NULL);
	ft_strlcpy(key, param, key_len - 1);
	key[key_len - 2] = '=';
	return (key);
}

int set_env_join(char **environ, char *s, char *param)
{
	char *value;
	char *key;
	char *tmp;
	size_t	index;


	key = set_key(param);
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
	size_t	index;

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

int set_env(char **environ, char *s)
{
	char *param;

	param = get_param(s);
	if (!ft_strchr(s, '='))
		return (0);
	if (!param)
		return(1);
	else if (ft_strchr(param, '+'))
		return (set_env_join(environ, s, param));
	else
		return (set_env_val(environ, s, param));
	return (0);
}

int put_env_declare(char **environ)
{
	while (*environ)
	{
		printf("declare -x %s\n", *environ);
		environ++;
	}
	return (0);
}

int builtin_export(char **argv)
{
	extern char **environ;
	char **val;
	int status;

	argv++;
	val = (char **)environ;
	if (!*argv)
		return (put_env_declare(val));
	while (*argv)
	{
		status = set_env(val, *argv);
		argv++;
	}
	return (status);
}