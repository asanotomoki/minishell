/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 16:21:48 by tasano            #+#    #+#             */
/*   Updated: 2023/01/16 19:51:47 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include "libft.h"
#include "util.h"


static char *get_before(char *str, size_t len)
{
	if (0 < len)
		return (ft_substr(str, 0, len));
	else
		return (NULL);
}

static char *get_after(char *str, size_t len)
{
	if (*str + len)
		return (ft_strdup(str + len));
	else
		return (NULL);
}

static char *get_parameter(char *str)
{
	size_t i;

	i = 1;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	return (ft_substr(str, 0, i));
}

static char *join_parameter(char *str, char *val, size_t i, size_t parameter_len)
{
	char *before;
	char *after;
	char *tmp;

	before = get_before(str, i);
	after = get_after(str, i + parameter_len);
	free_strval(&str);
	tmp = ft_strjoin(before, val);
	str = ft_strjoin(tmp, after);
	free_strval(&before);
	free_strval(&after);
	free_strval(&tmp);
	return (str);
}

char *set_parameter(char *str, size_t i)
{
	char *parameter;
	char *val;

	parameter = get_parameter(str + i);
	if (ft_strncmp(parameter, "$?", 3) == 0)
		str = ft_itoa(get_status());
	else if (parameter)
	{
		val = getenv(parameter + 1);
		str = join_parameter(str, val, i, ft_strlen(parameter));
		free_strval(&parameter);
	}
	return (str);
}
