/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 23:54:22 by tasano            #+#    #+#             */
/*   Updated: 2023/01/16 02:47:02 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	LEXER_H
# define	LEXER_H

#include <stdio.h>

typedef	enum e_token_type
{
	EXPANDABLE,
	NON_EXPANDABLE,
	PIPE,
	OUTREDIRECT,
	OUTADDITION,
	INREDIRECT,
	HEREDOCU
} t_token_type;

typedef	enum e_stat
{
	DOUBLEQUOATE,
	SINGLEQUOATE,
	NOMAL
} t_stat;

typedef struct s_token_lst
{
	char				*token;
	t_token_type		type;
	struct s_token_lst *next;
} t_token_lst;

int 		lexer(char *line, t_token_lst **lst);

t_token_lst	*token_lstnew(char *word, t_token_type type);
void		token_lstadd_back(t_token_lst **lst, t_token_lst	*new);
t_token_lst	*token_lstlast(t_token_lst *lst);
int 		add_lst(t_token_lst **lst, char *line, size_t size, t_token_type type);
void		token_lstfree(t_token_lst	**lst);
#endif
