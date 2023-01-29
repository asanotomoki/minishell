/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiroaki <hiroaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 18:19:04 by tasano            #+#    #+#             */
/*   Updated: 2023/01/30 03:59:53 by hiroaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "expansion.h"
#include "libft.h"
#include "util.h"

char	**swap_cmd_null(char **cmd, size_t i)
{
	char	*tmp;

	while (cmd[i + 1])
	{
		tmp = cmd[i];
		cmd[i] = cmd[i + 1];
		cmd[i + 1] = tmp;
		i++;
	}
	return (cmd);
}

char	*set_return_val(char *str)
{
	if (str && str[0])
		str = remove_quote(str);
	if (!str)
		return (NULL);
	return (str);
}

int	set_mode(char c, int mode)
{
	if (mode == 0)
	{
		if (c == '\'')
			return (1);
		if (c == '\"')
			return (2);
	}
	if ((mode == 1 && c == '\'') || (mode == 2 && c == '\"'))
		return (0);
	return (mode);
}

char	*get_val(char *parameter)
{
	char	*val;

	if (ft_strncmp(parameter, "$?", 2) == 0)
		val = ft_itoa(get_status());
	else
	{
		val = get_env_char(parameter + 1);
		if (val)
			return (ft_strdup(val));
	}
	return (val);
}
