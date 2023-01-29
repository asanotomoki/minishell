/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiroaki <hiroaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 12:44:05 by tasano            #+#    #+#             */
/*   Updated: 2023/01/30 02:58:02 by hiroaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
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

char	*set_shlvl(char *shlvl)
{
	long	n;
	char	*str_val;
	char	*ret;

	n = ft_strtol(&shlvl[6], NULL, 10);
	if (n < 0 || n == LONG_MAX)
		return (ft_strdup("SHLVL=1"));
	n++;
	if (n >= 1000)
	{
		printf(\
			"minish: warning: shell level (%ld) too high, resetting to 1\n", n);
		return (ft_strdup("SHLVL=1"));
	}
	str_val = ft_itoa(n);
	ret = ft_strjoin("SHLVL=", str_val);
	free(str_val);
	return (ret);
}

t_list	*make_env_lst(char **val, t_list *lst)
{
	size_t		i;
	bool		has_shlvl;
	t_list		*new;

	i = 0;
	has_shlvl = false;
	while (val[i])
	{
		if (ft_strncmp(val[i], "SHLVL=", 6) == 0)
		{
			has_shlvl = true;
			new = ft_lstnew(set_shlvl(val[i]));
		}
		else
			new = ft_lstnew(ft_strdup(val[i]));
		ft_lstadd_back(&lst, new);
		i++;
	}
	if (!has_shlvl)
		ft_lstadd_back(&lst, ft_lstnew(ft_strdup("SHLVL=1")));
	return (lst);
}

int	init_env(void)
{
	char		**val;
	extern char	**environ;
	t_list		*lst;

	if (environ == NULL)
		return (1);
	val = (char **)environ;
	lst = NULL;
	g_shell.env = make_env_lst(val, lst);
	return (0);
}
