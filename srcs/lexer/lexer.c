/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 20:38:15 by tasano            #+#    #+#             */
/*   Updated: 2023/01/16 01:33:58 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"
#include "minishell.h"

static int set_quote_mode(char c, int mode)
{
	if (mode == 0 && c == '\"')
		return (2);
	else if (mode == 2 && c == '\"')
		return (0);
	else if (mode == 0 && c == '\'')
		return (1);
	else if (mode == 1 && c == '\'')
		return (0);
	return (mode);
}

t_token_type get_token_type(char *line)
{
	t_token_type type;
	
	if (*line == '|')
		type = PIPE;
	else if (ft_strncmp(line, ">>", 2) == 0)
		type = OUTADDITION;
	else if (ft_strncmp(line, "<<", 2) == 0)
		type = HEREDOCU;
	else if (*line == '>')
		type = OUTREDIRECT;
	else
		type = INREDIRECT;
	return (type);
}

size_t get_token_size(char *line)
{
	size_t size;

	size = 1;
	if (ft_strncmp(line, ">>", 2) == 0)
		size = 2;
	else if (ft_strncmp(line, "<<", 2) == 0)
		size = 2;
	return (size);
}

int nomal_tokenizer(t_token_lst **lst, char *line)
{
	size_t i;
	int quote_mode;

	while (*line)
	{
		while (*line && ft_isspace(*line))
			line++;
		quote_mode = 0;
		i = 0;
		while (line[i])
		{
			quote_mode = set_quote_mode(line[i], quote_mode);
			if ((ft_isspace(line[i]) || ft_strchr("|<>", line[i])) && quote_mode == 0)
				break;
			i++;
		}
		if (0 < i)
		{
			add_lst(lst, line, i, EXPANDABLE);
			line += i;
		}
		if (*line && !ft_isspace(*line))
		{
			i = get_token_size(line);
			if (add_lst(lst, line, i, get_token_type(line)))
			{
				token_lstfree()
			}
			line += i;
		}
	}
	return (0);
}

t_token_lst *lexer(char *line)
{
	t_token_lst *lst;
	int			status;

	if (!line)
		return (NULL);
	lst = NULL;
	status = nomal_tokenizer(&lst, line);
	printf("%d", status);
	return (lst);
}
