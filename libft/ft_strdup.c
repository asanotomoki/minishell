/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiroaki <hiroaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 23:29:51 by asanotomoki       #+#    #+#             */
/*   Updated: 2023/01/25 23:30:16 by hiroaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*t;
	size_t	length;

	if (!s1)
		return (NULL);
	length = ft_strlen(s1);
	t = (char *)malloc(sizeof(char) * (length + 1));
	if (t == NULL)
		return (NULL);
	ft_strlcpy(t, s1, length + 1);
	return (t);
}
