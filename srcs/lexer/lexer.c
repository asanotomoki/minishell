/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 20:38:15 by tasano            #+#    #+#             */
/*   Updated: 2022/12/19 16:16:39 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"

t_token_lst *lexer(char *line)
{
	t_token_lst	*lst;
	size_t	end;
	unsigned int start;

	lst = NULL;
	end = 0;
	start = 0;
	while (line[end])
	{
		if (line[end] == '|')
		{
			token_lstadd_back(&lst, token_lstnew(ft_substr(line, start, end - start), WORD));
			token_lstadd_back(&lst, token_lstnew(ft_strdup("|"), PIPE));
			start = end + 1;
		}
		end++;
	}
	token_lstadd_back(&lst, token_lstnew(ft_substr(line, start, end), WORD));

	return (lst);
}