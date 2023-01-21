/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 15:33:08 by tasano            #+#    #+#             */
/*   Updated: 2023/01/21 12:11:41 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "builtin_cmds.h"

int	check_param(char *param)
{
	while (*param)
	{
		if (!ft_isalnum(*param) && *param != '_')
			return (1);
		param++;
	}
	return (0);
}

char	*get_param(char *val)
{
	size_t	i;
	char	*param;

	i = 0;
	while (val[i] && val[i] != '=')
	{
		if (!ft_isalnum(val[i]) && val[i] != '_' && \
			ft_strncmp(val + i, "+=", 2))
			return (env_put_error("export", val));
		i++;
	}
	if (i == 0)
		return (env_put_error("export", val));
	param = ft_substr(val, 0, i);
	return (param);
}

char	*get_key(char *param)
{
	size_t	key_len;
	char	*key;

	key_len = ft_strlen(param);
	key = ft_substr(param, 0, key_len - 1);
	if (!key)
		return (NULL);
	return (key);
}
