/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 22:58:36 by tasano            #+#    #+#             */
/*   Updated: 2023/01/16 02:49:32 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"
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

void	token_lstfree(t_token_lst	**lst)
{
	t_token_lst	*tmp;

	tmp = *lst;
	while (tmp)
	{
		*lst = tmp->next;
		free(tmp->token);
		tmp->token = NULL;
		free(tmp);
		tmp = NULL;
		tmp = *lst;
	}
}

int add_lst(t_token_lst **lst, char *line, size_t size, t_token_type type)
{
	char *word;
	t_token_lst *tmp;

	word = ft_substr(line, 0, size);
	if (!word)
	{
		perror("lexer");
		return (1);
	}
	tmp = token_lstnew(word, type);
	if (!tmp)
	{
		free(word);
		return (1);
	}
	token_lstadd_back(lst, tmp);
	return (0);
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
	if (!lst || !*lst)
		*lst = new;
	else
		token_lstlast(*lst)->next = new;
}
