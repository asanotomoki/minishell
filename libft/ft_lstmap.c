/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmakino <hmakino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 19:09:31 by hmakino           #+#    #+#             */
/*   Updated: 2022/06/20 08:42:06 by hmakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*lst_new;
	t_list	*pos_first;

	if (!lst)
		return (NULL);
	pos_first = NULL;
	while (lst)
	{
		lst_new = ft_lstnew((*f)(lst->content));
		if (!lst_new)
		{
			ft_lstclear(&pos_first, del);
			lst = NULL;
			return (NULL);
		}
		ft_lstadd_back(&pos_first, lst_new);
		lst = lst->next;
	}
	return (pos_first);
}
