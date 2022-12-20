/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 22:58:36 by tasano            #+#    #+#             */
/*   Updated: 2022/12/20 15:36:07 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <stdlib.h>

t_token_lst	*token_lstnew(char *word, t_token_type type)
{
	t_token_lst	*content;

	if (!word)
		return (NULL);
	content = (t_token_lst *)malloc(sizeof(t_token_lst));
	if (!content)
		return (NULL);
	content->token = word;
	content->type = type;
	content->next = NULL;
	return (content);
}

void	token_lstfree(t_token_lst	*token)
{
	t_token_lst	*tmp;

	while (token)
	{
		tmp = token->next;
		free(token->token);
		token->token = NULL;
		free(token);
		token = NULL;
		token = tmp;
	}
	token = NULL;
}

void	token_lstadd(t_token_lst *lst, t_token_lst	*new)
{
	if (!new)
		return ;
	if (!lst)
		lst = new;
	else
	{
		new->next = lst->next;
		lst->next = new;
	}
}

t_token_lst	*token_lstlast(t_token_lst *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}


void	token_lstadd_back(t_token_lst **lst, t_token_lst	*new)
{
	if (!new)
		return ;
	if (!*lst)
		*lst = new;
	else
		token_lstlast(*lst)->next = new;
}
