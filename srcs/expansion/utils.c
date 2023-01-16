
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 18:19:04 by tasano            #+#    #+#             */
/*   Updated: 2023/01/16 20:35:27 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include "libft.h"

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
	if (!str)
		return (NULL);
	else if (!str[0])
	{
		free_strval(&str);
		return (NULL);
	}
	else
	{
		str = remove_quote(str);
		if (!str || !str[0])
			set_return_val(str);
		return (str);
	}
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
