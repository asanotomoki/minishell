/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 12:44:05 by tasano            #+#    #+#             */
/*   Updated: 2023/01/21 15:02:26 by tasano           ###   ########.fr       */
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

char	**get_env_argv(void)
{
	size_t	i;
	t_list	*lst;
	char	**res;

	lst = get_env();
	res = (char **)malloc(sizeof(char **) * ft_lstsize(lst));
	if (!res)
		return (NULL);
	i = 0;
	while (lst)
	{
		res[i] = (char *)lst->content;
		lst = lst->next;
		i++;
	}
	return (res);
}

t_list	*get_env(void)
{
	return (g_shell.env);
}

t_list	*get_env_val(char *param)
{
	t_list	*envp;
	char	*s_param;

	envp = get_env();
	s_param = ft_strjoin(param, "=");
	while (envp)
	{
		if (ft_strncmp(envp->content, s_param, ft_strlen(s_param)) == 0)
			break ;
		envp = envp->next;
	}
	free_strval(&s_param);
	return (envp);
}

int	init_env(void)
{
	size_t		i;
	extern char	**environ;
	char		**val;
	t_list		*lst;

	val = (char **)environ;
	if (!val)
		return (1);
	lst = NULL;
	i = 0;
	while (val[i])
	{
		ft_lstadd_back(&lst, ft_lstnew(ft_strdup(val[i])));
		i++;
	}
	g_shell.env = lst;
	return (0);
}
