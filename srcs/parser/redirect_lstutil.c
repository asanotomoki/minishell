/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_lstutil.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiroaki <hiroaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 09:35:13 by tasano            #+#    #+#             */
/*   Updated: 2023/01/30 04:00:10 by hiroaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdlib.h>
#include "parser.h"
#include "util.h"
#include "libft.h"

t_redirect	*redirection_new(t_token_lst *lst)
{
	t_redirect	*content;

	errno = 0;
	content = (t_redirect *)malloc(sizeof(t_redirect));
	if (!content)
		return (NULL);
	if (lst->next && lst->next->type == EXPANDABLE)
		content->filename = ft_strdup(lst->next->token);
	content->type = lst->type;
	content->fd = -1;
	content->next = NULL;
	return (content);
}

void	redirection_addback(t_redirect **lst, t_redirect *new)
{
	t_redirect	*tmp;

	if (!new)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		tmp = *lst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	redirect_lstfree(t_redirect **lst)
{
	t_redirect	*tmp;

	tmp = *lst;
	while (tmp)
	{
		*lst = tmp->next;
		free_strval(&tmp->filename);
		free(tmp);
		tmp = *lst;
	}
}
