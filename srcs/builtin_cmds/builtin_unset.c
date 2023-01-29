/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 17:26:24 by tasano            #+#    #+#             */
/*   Updated: 2023/01/21 10:47:03 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include "builtin_cmds.h"
#include "minishell.h"

void	clear_val(t_list *val)
{
	t_list	*environ;

	environ = get_env();
	while (environ)
	{
		if (val == environ->next)
			break ;
		environ = environ->next;
	}
	if (!environ)
		return ;
	environ->next = val->next;
	ft_lstdelone(val, free);
}

int	unset_env(char *param)
{
	t_list	*val;

	if (check_param(param))
	{
		env_put_error("unset", param);
		return (1);
	}
	val = get_env_val(param);
	if (val)
		clear_val(val);
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
