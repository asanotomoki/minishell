/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 20:38:15 by tasano            #+#    #+#             */
/*   Updated: 2022/12/13 15:23:35 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"

typedef	enum e_token_type
{
	EXPANDABLE,
	EXPANDABLE_QUOTED,
	PIPE,
	INPUT_REDIRECTION,
	HEREDOCUMENT,
	OUTPUT_REDIRECTION,
	OUTPUT_APPENDING,
	SEMICOLON,
	NEWLINE,
	SPACE,
} t_token_type;

typedef struct s_token
{
	char				*token;
	t_token_type		type;
} t_token;

typedef struct s_token_list
{
	t_token	token;
	struct s_token_list *next;
} t_token_list;


char *lexer(char *line)
{
	printf("%s", line);
	return (0);
}