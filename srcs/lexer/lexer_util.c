/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 03:46:10 by tasano            #+#    #+#             */
/*   Updated: 2023/01/17 03:58:11 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lexer.h"

int	set_quote_mode(char c, int mode)
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

t_token_type	get_token_type(char *line)
{
	t_token_type	type;

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

size_t	get_token_size(char *line)
{
	size_t	size;

	size = 1;
	if (ft_strncmp(line, ">>", 2) == 0)
		size = 2;
	else if (ft_strncmp(line, "<<", 2) == 0)
		size = 2;
	return (size);
}
