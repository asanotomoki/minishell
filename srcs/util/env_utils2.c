/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiroaki <hiroaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 12:44:05 by tasano            #+#    #+#             */
/*   Updated: 2023/01/30 04:00:28 by hiroaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "util.h"
#include "minishell.h"

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
