/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 20:38:15 by tasano            #+#    #+#             */
/*   Updated: 2022/12/24 12:00:41 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"

static t_stat set_stat(char c, t_stat stat)
{
	if (stat == NOMAL && c == '\"')
		return (DOUBLEQUOATE);
	else if (stat == DOUBLEQUOATE && c == '\"')
		return (NOMAL);
	else if (stat == NOMAL && c == '\'')
		return (SINGLEQUOATE);
	else if (stat == SINGLEQUOATE && c == '\'')
		return (NOMAL);
	return (NOMAL);
}

size_t add_lst_token(t_token_lst **lst, char *line)
{
	t_token_type type;
	size_t size;

	size = 1;
	if (*line == '|')
		type = PIPE;
	else if (!ft_strncmp(line, ">>", 2))
	{
		type = OUTADDITION;
		size = 2;
	}
	else if (!ft_strncmp(line, "<<", 2))
	{
		type = HEREDOCU;
		size = 2;
	}
	else if (*line == '>')
		type = OUTREDIRECT;
	else
		type = INREDIRECT;
	return (add_lst(lst, line, size, type));
}

char  *nomal_tokenizer(t_token_lst **lst, char *line)
{
	size_t i;

	i = 0;
	while (*line && ft_isspace(*line))
		line++;
	while (line[i] && !ft_isspace(line[i]) && !ft_strchr("|<>", line[i]))
		i++;
	if (0 < i)
		line += add_lst(lst, line, i, EXPANDABLE);
	if (*line && !ft_isspace(*line))
		line += add_lst_token(lst, line);
	return (line);
}

char	*quote_tokenizer(t_token_lst **lst, char *line, char quote, t_token_type type)
{
	size_t	i;

	i = 0;
	while (line[i])
	{
		if (i != 0 && line[i] == quote )
			break ;
		i++;
	}
	line += add_lst(lst, line, i + (line[i] == quote), type);
	return (line);
}

t_token_lst *lexer(char *line)
{
	t_token_lst *lst;
	t_stat stat;

	if (!line)
		return (NULL);
	lst = NULL;
	stat = NOMAL;
	while (*line)
	{
		stat = set_stat(*line, stat);
		if (stat == NOMAL)
			line = nomal_tokenizer(&lst, line);
		else if (stat == DOUBLEQUOATE)
				line = quote_tokenizer(&lst, line, '\"', EXPANDABLE);
		else if (stat == SINGLEQUOATE)
				line = quote_tokenizer(&lst, line, '\'', NON_EXPANDABLE);
		stat = NOMAL;
	}
	return (lst);
}
