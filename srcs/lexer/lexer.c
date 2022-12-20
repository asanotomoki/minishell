/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 20:38:15 by tasano            #+#    #+#             */
/*   Updated: 2022/12/20 15:42:24 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"

//static t_token_lst	*split_token(t_token_lst **lst, char *sep)
//{
//	t_token_lst	*tmp;
//	size_t		i;
	
//	tmp = *lst;
//	while (tmp)
//	{
//		i = 0;
//		while (tmp->token[i])
//		{
//			if (ft_strchr(sep, tmp->token[i]))
//			{
//				;
//			}
//			printf("%s\n", ft_strchr(tmp->token, '|'));
//			i++;
//		}
//		tmp = tmp->next;
//	}
//	return (*lst);
//}

t_token_lst	*split_space(char *line)
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
	return (lst);
}