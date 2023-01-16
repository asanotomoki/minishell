/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiroaki <hiroaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 21:03:48 by hiroaki           #+#    #+#             */
/*   Updated: 2023/01/13 18:44:15 by hiroaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*node_new;

	node_new = (t_list *)malloc(sizeof(t_list));
	if (!node_new)
		return (NULL);
	node_new->len = ft_strlen(content);
	node_new->content = content;
	node_new->next = NULL;
	return (node_new);
}
