/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 15:33:08 by tasano            #+#    #+#             */
/*   Updated: 2023/01/16 15:44:42 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

char *export_put_error(char *val)
{
	ft_putstr_fd(PROMPT ,2);
	ft_putstr_fd(": export: `" ,2);
	ft_putstr_fd(val ,2);
	ft_putstr_fd("': not a valid identifier" ,2);
	return (NULL);
}

char *get_param(char *val)
{
	size_t i;
	char *param;

	i = 0;
	while (val[i] && val[i] != '=')
	{
		if (!ft_isalnum(val[i]) && val[i] != '_' && \
			ft_strncmp(val + i, "+=", 2))
			return (export_put_error(val));
		i++;
	}
	if (i == 0)
		return (export_put_error(val));
	param = ft_substr(val, 0, i + 1);
	return (param);
}

char *get_key(char *param)
{
	size_t key_len;
	char *key;

	key_len = ft_strlen(param);
	key = (char *)malloc(sizeof(char) * key_len);
	ft_bzero(key, key_len * sizeof(char));
	if (!key)
		return (NULL);
	ft_strlcpy(key, param, key_len - 1);
	key[key_len - 2] = '=';
	return (key);
}