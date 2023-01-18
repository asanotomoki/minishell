/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiroaki <hiroaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 11:29:12 by hiroaki           #+#    #+#             */
/*   Updated: 2022/12/30 15:18:55 by hiroaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <sys/types.h>

typedef enum e_token_type
{
	EXPANDABLE,
	NON_EXPANDABLE,
	PIPE,
	OUTREDIRECT,
	OUTADDITION,
	INREDIRECT,
	HEREDOCU
}	t_token_type;

typedef struct s_redirect
{
	char				*filename;
	t_token_type		type;
	t_token_type		expand_type;
	struct s_redirect	*next;
}	t_redirect;

typedef struct s_parse_ast {
	pid_t				pid;
	int					pfd[2];
	char				*cmd_path;
	char				**cmd;
	t_redirect			*imput;
	t_redirect			*output;
	struct s_parse_ast	*next_pipe;
	struct s_parse_ast	*prev_pipe;
}	t_parse_ast;

#endif
