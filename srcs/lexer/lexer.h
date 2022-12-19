/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 23:54:22 by tasano            #+#    #+#             */
/*   Updated: 2022/12/19 13:17:11 by tasano           ###   ########.fr       */
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

typedef struct s_token_lst
{
	char				*token;
	t_token_type		type;
	struct s_token_lst *next;
} t_token_lst;


char *lexer(char *line);


//token lst operation
t_token_lst	*token_lstnew(char *word, t_token_type type);
void		token_lstadd_back(t_token_lst **lst, t_token_lst	*new);
t_token_lst	*token_lstlast(t_token_lst *lst);
void		token_lstadd(t_token_lst *lst, t_token_lst	*new);
void		token_lstfree(t_token_lst	*token);
#endif
