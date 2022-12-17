/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 23:54:22 by tasano            #+#    #+#             */
/*   Updated: 2022/12/17 21:48:05 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

#include <stdio.h>

typedef	enum e_token_type
{
	DABLEQUATE,
	SINGLEQUATE,
	PIPE,
	INPUT_REDIRECTION,
	HEREDOCUMENT,
	OUTPUT_REDIRECTION,
	OUTPUT_APPENDING,
	NEWLINE,
	SPACE
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


char *lexer(char *line);

#endif
