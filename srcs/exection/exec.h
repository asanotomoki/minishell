/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiroaki <hiroaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 20:24:22 by hiroaki           #+#    #+#             */
/*   Updated: 2023/01/30 03:59:06 by hiroaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <limits.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/errno.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include "libft.h"
# include "parser.h"
# include "expansion.h"
# include "minishell.h"

# define COMMAND_NOT_FOUND 127
# define HEREDOC_TEMPFILE ".heredoc_tempfile"

# ifndef OPEN_MAX
#  define OPEN_MAX 1024
# endif

# ifndef PIPESIZE
#  ifdef PIPE_BUF
#   define PIPESIZE PIPE_BUF
#  else
#   define PIPESIZE 4096
#  endif
# endif

# ifndef HEREDOC_PIPESIZE
#  define HEREDOC_PIPESIZE PIPESIZE
# endif

# if defined (HEREDOC_PIPEMAX)
#  if HEREDOC_PIPESIZE > HEREDOC_PIPEMAX
#   define HEREDOC_PIPESIZE HEREDOC_PIPEMAX
#  endif
# endif

/* exection.c */
int		exection(t_cmd *cmd);

/* set_redirect.c */
int		set_redirect(t_redirect *redirect);

/* set_heredoc.c */
void	set_heredocument(t_cmd *cmd);

/* get_cmdfile.c */
char	*get_cmdfile(char *cmd, char *path);

/* exec_builtin.c */
int		exec_builtin(t_cmd *cmd);
bool	check_builtin(t_cmd *cmd);
void	close_fd(t_redirect *redirect, int backup, int backupin);
void	exec_builtin_parent(t_cmd *cmd);

/* check_cmdfile.c */
int		check_cmdfile(char	*filename, char	*param);

/* heredoc_utils.c */
int		write_heredoc(int fd, t_list *document);
int		use_tempfile(t_list *document);
t_list	*creat_document(size_t *len_ptr, char *delimiter, bool is_quoted);
bool	discontinue(char *line, char *delimiter);
char	*joint_carriage_return(char *line);

/* pipe_utils.c */
void	set_pipe(int pp[2]);
void	close_pipe(int pp[2]);
int		use_system_pipe(t_list *document);
size_t	pipe_cnt(t_cmd *cmd);
void	connect_io_pipe(size_t i, size_t pipe_cnt, int pp[OPEN_MAX / 2][2]);

/* wait_utils.c */
void	create_waitpid(t_cmd *cmd);

/* fd_utils.c */
void	set_stdin(int pp[2]);
void	set_stdout(int pp[2]);
void	set_dup2(int new_fd, int old_fd);

#endif
