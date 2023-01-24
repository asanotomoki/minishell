/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 17:26:11 by tasano            #+#    #+#             */
/*   Updated: 2023/01/24 14:01:06 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include "builtin_cmds.h"
#include "util.h"
#include "minishell.h"

static int	set_env_join(t_list *head, char *s, char *param)
{
	char	*value;
	char	*key;
	char	*tmp;
	t_list	*lst;

	key = get_key(param);
	value = s + ft_strlen(param) + 1;
	lst = get_env_val(key);
	if (!lst)
	{
		tmp = ft_strjoin(key, "=");
		s = ft_strjoin(tmp, value);
		free_strval(&tmp);
		ft_lstadd_back(&head, ft_lstnew(s));
	}
	else
	{
		tmp = ft_strjoin(lst->content, value);
		free(lst->content);
		lst->content = tmp;
	}
	free_strval(&param);
	free_strval(&key);
	return (0);
}

static int	set_env_val(t_list *head, char *s, char *param)
{
	t_list	*lst;

	lst = get_env_val(param);
	if (!lst)
	{
		lst = ft_lstnew(ft_strdup(s));
		ft_lstadd_back(&head, lst);
	}
	else
	{
		free(lst->content);
		lst->content = ft_strdup(s);
	}
	free_strval(&param);
	return (0);
}

int	set_env(char *s)
{
	char	*param;

	param = get_param(s);
	if (!param)
		return (1);
	if (!ft_strchr(s, '='))
	{
		free_strval(&param);
		return (0);
	}
	else if (ft_strchr(param, '+'))
		return (set_env_join(get_env(), s, param));
	else
		return (set_env_val(get_env(), s, param));
	return (0);
}

static int	put_env_declare(void)
{
	t_list	*environ;

	environ = get_env();
	while (environ)
	{
		printf("declare -x %s\n", (char *)environ->content);
		environ = environ->next;
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
