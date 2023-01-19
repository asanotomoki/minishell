/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 12:44:05 by tasano            #+#    #+#             */
/*   Updated: 2023/01/20 00:54:40 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "util.h"
#include "minishell.h"

char	*env_put_error(char *function, char *val)
{
	ft_putstr_fd(SHELL, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(function, 2);
	ft_putstr_fd(": `", 2);
	ft_putstr_fd(val, 2);
	ft_putendl_fd("': not a valid identifier", 2);
	return (NULL);
}

size_t	search_param(char **argv, char *param)
{
	size_t	param_len;
	size_t	i;

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

char	**get_env(void)
{
	extern char	**environ;
	char		**val;

	val = (char **)environ;
	return (val);
}

int	init_env(void)
{
	size_t	i;
	char	**val;

	val = get_env();
	if (!val)
		return (1);
	i = 0;
	while (val[i])
	{
		val[i] = ft_strdup(val[i]);
		if (!val[i])
		{
			free_args(&val);
			return (1);
		}
		i++;
	}
	return (0);
}
