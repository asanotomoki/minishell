/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 23:54:22 by tasano            #+#    #+#             */
/*   Updated: 2022/12/18 17:38:57 by tasano           ###   ########.fr       */
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
	char				*word;
	t_token_type		type;
} t_token;

typedef struct s_token_list
{
	t_token	*token;
	struct s_token_list *next;
} t_token_list;


char *lexer(char *line);


//token lst operation
t_token			*token_new(char *word, t_token_type type);
t_token_list	*token_lstnew(t_token *token);
void			token_free(t_token *token);
void			token_list_free(t_token_list	*token);
#endif
