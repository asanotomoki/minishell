/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 23:54:22 by tasano            #+#    #+#             */
/*   Updated: 2022/12/26 11:39:57 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

#include <stdio.h>
#include <unistd.h>
#include "lexer.h"

typedef struct s_redirection
{
	char                    *filename;
    t_token_type             type;
    struct s_redirection    *next;
} t_redirection;

typedef struct s_cmd
{
    t_redirection   *output;
    struct s_cmd    *piped_cmd;
    t_redirection   *input;
    char            **cmd;
    size_t          argc;
}   t_cmd;

t_cmd   *parser(t_token_lst *lst);
t_cmd	*cmd_addback(t_cmd *lst, t_cmd *new);
void	redirection_addback(t_redirection **lst, t_redirection *new);
t_redirection	*redirection_new(t_token_lst *lst);
t_cmd	*cmd_new();
#endif
