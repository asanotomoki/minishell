/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 12:44:05 by tasano            #+#    #+#             */
/*   Updated: 2023/01/21 13:10:34 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "util.h"
#include "minishell.h"

char	*get_env_char(char *param)
{
	t_list	*envp;
	char	*s_param;
	size_t	len;

	envp = get_env();
	s_param = ft_strjoin(param, "=");
	len = ft_strlen(s_param);
	while (envp)
	{
		if (ft_strncmp(envp->content, s_param, len) == 0)
			break ;
		envp = envp->next;
	}
	free_strval(&s_param);
	if (!envp)
		return (NULL);
	return ((char *)envp->content + len);
}
