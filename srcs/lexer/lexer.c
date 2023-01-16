/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 20:38:15 by tasano            #+#    #+#             */
/*   Updated: 2023/01/17 03:47:28 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"
#include "minishell.h"

char	*set_lst(t_token_lst **lst, char *line, size_t i)
{
	if (0 < i)
	{
		if (add_lst(lst, line, i, EXPANDABLE))
		{
			token_lstfree(lst);
			perror("lexer");
			return (NULL);
		}
		line += i;
	}
	if (*line && !ft_isspace(*line))
	{
		i = get_token_size(line);
		if (add_lst(lst, line, i, get_token_type(line)))
		{
			token_lstfree(lst);
			perror("lexer");
			return (NULL);
		}
		line += i;
	}
	return (line);
}

int	nomal_tokenizer(t_token_lst **lst, char *line)
{
	size_t	i;
	int		quote_mode;

	while (*line)
	{
		while (*line && ft_isspace(*line))
			line++;
		quote_mode = 0;
		i = 0;
		while (line[i])
		{
			quote_mode = set_quote_mode(line[i], quote_mode);
			if ((ft_isspace(line[i]) || \
			ft_strchr("|<>", line[i])) && quote_mode == 0)
				break ;
			i++;
		}
		line = set_lst(lst, line, i);
		if (!line)
			return (1);
	}
	return (0);
}

int	lexer(char *line, t_token_lst **lst)
{
	if (!line)
		return (0);
	return (nomal_tokenizer(lst, line));
}
