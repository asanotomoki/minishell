/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 02:17:05 by tasano            #+#    #+#             */
/*   Updated: 2023/01/14 02:26:37 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "expansion.h"

static char *remove_set_val(char *str, size_t i)
{
	char *before;
	char *tmp;

	before = ft_substr(str, 0, i);
	tmp = str;
	str = ft_strjoin(before, str + i + 1);
	free_strval(&before);
	free_strval(&tmp);
	return (str);
}

char *remove_quote(char *str)
{
	size_t i;
	int mode;
	int tmp_mode;

	i = 0;
	tmp_mode = 0;
	while (str[i])
	{
		mode = set_mode(str[i], tmp_mode);
		if (tmp_mode == 0 && mode)
			str = remove_set_val(str, i);
		else if (tmp_mode && mode == 0)
			str = remove_set_val(str, i);
		else
			i++;
		tmp_mode = mode;
	}
	return (str);
}