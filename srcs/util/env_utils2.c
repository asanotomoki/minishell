/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 12:44:05 by tasano            #+#    #+#             */
/*   Updated: 2023/01/24 13:29:49 by tasano           ###   ########.fr       */
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
	return ((char *)envp->content + size);
}
