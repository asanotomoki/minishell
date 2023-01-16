/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 23:54:22 by tasano            #+#    #+#             */
/*   Updated: 2023/01/16 01:56:20 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdio.h>
# include <unistd.h>
# include "lexer.h"

# define SYNTAXERR "minishell: syntax error near unexpected token `"

typedef struct s_heredoc
{
	int		*fd;
	char	*document;
	size_t	len;
}	t_heredoc;

typedef struct s_redirect
{
	char				*filename;
	t_token_type		type;
	t_token_type		expnad_type;
	int					heredoc_fd;
	struct s_redirect	*next;
}	t_redirect;

typedef struct s_cmd
{
   t_redirect   *redirect;
    struct s_cmd *piped_cmd;
    char         **cmd;
    size_t       argc;
    pid_t        pid;
}   t_cmd;

t_cmd		*parser(t_token_lst *lst);

//redirect lst util
void		redirection_addback(t_redirect **lst, t_redirect *new);
t_redirect	*redirection_new(t_token_lst *lst);
void		redirect_lstfree(t_redirect **lst);

//cmd lst utils
void		cmd_lstfree(t_cmd **cmd);
t_cmd		*cmd_addback(t_cmd *lst, t_cmd *new);
t_cmd		*cmd_new(void);
//utils
char		**append_args(char **args, size_t argc, char *new);
int			parse_error(t_token_lst *lst, t_cmd *cmd, t_token_lst **tmplst);
void		free_parser_lst(t_token_lst **lst);

#endif
