/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 17:26:24 by tasano            #+#    #+#             */
/*   Updated: 2023/01/16 22:26:28 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include "builtin_cmds.h"
#include "minishell.h"

void	clear_val(char **environ, size_t i)
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

int	unset_env(char *param)
{
	char	*param_search;
	char	**environ;
	size_t	i;

	environ = get_env();
	if (check_param(param))
	{
		env_put_error("unset", param);
		return (1);
	}
	param_search = ft_strjoin(param, "=");
	i = search_param(environ, param_search);
	if (environ[i])
		clear_val(environ, i);
	free(param_search);
	param_search = NULL;
	return (0);
}

int	builtin_unset(char **argv)
{
	int	status;

	argv++;
	if (!*argv)
		return (0);
	while (*argv)
	{
		status = unset_env(*argv);
		argv++;
	}
	return (status);
}
