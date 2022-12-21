/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 20:38:15 by tasano            #+#    #+#             */
/*   Updated: 2022/12/21 15:58:29 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"

//static t_token_lst	*split_token(t_token_lst **lst, char *sep)
//{

//	return (*lst);
//}

static	t_token_lst *set_token(t_token_lst *lst, t_token_type type, size_t p, size_t size)
{
	t_token_lst	*tmp;

	tmp = token_lstnew(ft_substr(lst->token, 0, p), WORD);
	lst->token = lst->token + p;
	token_lstadd_back(&tmp, token_lstnew(ft_substr(lst->token, 0, size), type));
	lst->token = lst->token + size;
	if (ft_strlen(lst->token))
		token_lstadd_back(&tmp, token_lstnew(ft_strdup(lst->token), WORD));
	token_lstlast(tmp)->next = lst->next;
	//free(lst->token);
	free(lst);
	lst = tmp;
	return (lst);
}

static	t_token_lst	*split_space(char *line)
{
	t_token_lst	*lst;
	size_t	i;
	t_token_lst	*token;

	lst = NULL;
	while (*line)
	{
		i = 0;
		while (*line && ft_isspace(*line))
			line++;
		while (line[i] && !ft_isspace(line[i]))
			i++;
		token = token_lstnew(ft_substr(line, 0, i), WORD);
		token_lstadd_back(&lst, token);
		line = line + i;
	}
	return (lst);
}

t_token_lst *lexer(char *line)
{
	t_token_lst	*lst;
	if (!line)
		return (NULL);
	lst = split_space(line);
	lst->next = set_token(lst->next, PIPE, 2, 1);
	return (lst);
}