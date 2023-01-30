/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiroaki <hiroaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 12:44:05 by tasano            #+#    #+#             */
/*   Updated: 2023/01/30 02:58:06 by hiroaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "util.h"
#include "minishell.h"

t_list	*get_env(void)
{
	return (g_shell.env);
}

char	*get_env_char(char *param)
{
	t_list	*envp;
	size_t	size;

	size = ft_strlen(param) + 1;
	envp = get_env_val(param);
	if (!envp)
		return (NULL);
	return ((char *)envp->content + size);
}

char	**get_env_argv(void)
{
	size_t	i;
	t_list	*lst;
	char	**res;

	lst = get_env();
	res = (char **)malloc(sizeof(char **) * ft_lstsize(lst) + 1);
	if (!res)
		return (NULL);
	i = 0;
	while (lst)
	{
		res[i] = (char *)lst->content;
		lst = lst->next;
		i++;
	}
	res[i] = NULL;
	return (res);
}
