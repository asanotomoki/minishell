/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 23:54:22 by tasano            #+#    #+#             */
/*   Updated: 2023/01/17 03:54:42 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stdio.h>

typedef enum e_token_type
{
	EXPANDABLE,
	PIPE,
	OUTREDIRECT,
	OUTADDITION,
	INREDIRECT,
	HEREDOCU
}	t_token_type;

typedef struct s_token_lst
{
	char				*token;
	t_token_type		type;
	struct s_token_lst	*next;
}	t_token_lst;

int				lexer(char *line, t_token_lst **lst);

t_token_lst		*token_lstnew(char *word, t_token_type type);
void			token_lstadd_back(t_token_lst **lst, t_token_lst	*new);
t_token_lst		*token_lstlast(t_token_lst *lst);
int				add_lst(t_token_lst **lst, char *line, \
						size_t size, t_token_type type);
void			token_lstfree(t_token_lst	**lst);

size_t			get_token_size(char *line);
t_token_type	get_token_type(char *line);
int				set_quote_mode(char c, int mode);

#endif
