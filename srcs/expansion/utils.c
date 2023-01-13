/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 18:19:04 by tasano            #+#    #+#             */
/*   Updated: 2023/01/13 18:22:05 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include "libft.h"

char *get_parameter(char *str)
{
	size_t i;

	i = 1;
	while (str[i] && ft_isalnum(str[i]))
		i++;
	return (ft_substr(str, 0, i));
}

void free_strval(char **str)
{
	if (*str)
		free(*str);
	*str = NULL;
}


char *get_before(char *str, size_t len)
{
	if (0 < len)
		return (ft_substr(str, 0, len));
	else
		return (NULL);
}

char *get_after(char *str, size_t len)
{
	if (*str + len)
		return (ft_strdup(str + len));
	else
		return (NULL);
}

int is_expandble(char *str)
{
	return (str && str[0] == '\'');
}