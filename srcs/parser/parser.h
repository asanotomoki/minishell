/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiroaki <hiroaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 23:54:22 by tasano            #+#    #+#             */
/*   Updated: 2023/01/30 04:00:03 by hiroaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdio.h>
# include <unistd.h>
# include <stdbool.h>
# include "lexer.h"
# include "../builtin_cmds/builtin_cmds.h"

typedef struct s_redirect
{
	char				*filename;
	t_token_type		type;
	int					fd;
	int					heredoc_fd;
	bool				heredoc_quoted;
	struct s_redirect	*next;
}	t_redirect;

typedef struct s_cmd
{
	t_redirect		*redirect;
	struct s_cmd	*piped_cmd;
	char			**cmd;
	t_cmd_type		type;
	size_t			argc;
	pid_t			pid;
}	t_cmd;

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
int			parse_error(t_token_lst *lst, t_cmd **cmd, t_token_lst **head);
void		free_parser_lst(t_token_lst **lst);
int			put_parse_error(char *param);

#endif
