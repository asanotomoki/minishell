/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 13:43:22 by tasano            #+#    #+#             */
/*   Updated: 2022/12/18 17:45:11 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lexer.h"

t_token	*token_new(char *word, t_token_type type)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->word = word;
	token->type = type;
	return (token);
}

t_token_list	*token_lstnew(t_token *token)
{
	t_token_list	*content;

	if (!token)
		return (NULL);
	content = (t_token_list *)malloc(sizeof(t_token_list));
	if (!token)
		return (NULL);
	content->token = token;
	content->next = NULL;
	return (content);
}

void	token_free(t_token *token)
{
	free(token->word);
	token->word = NULL;
	free(token);
	token = NULL;
}

void	token_list_free(t_token_list	*token)
{
	t_token_list	*tmp;

	while (token)
	{
		tmp = token->next;
		token_free(token->token);
		free(token);
		token = tmp;
	}
}
