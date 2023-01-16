/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiroaki <hiroaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 20:24:22 by hiroaki           #+#    #+#             */
/*   Updated: 2023/01/16 20:52:57 by hiroaki          ###   ########.fr       */
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
# include "parser.h"
# include "expansion.h"
# include "libft.h"

# define SHELL "minish"
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
void	set_redirect(t_redirect *redirect);

/* set_heredoc.c */
void	heredoc_to_fd(t_cmd *cmd);

/* get_cmdfile.c */
char	*get_cmdfile(char *cmd, char *path);

/* utils.c */
void	set_pipe(int pp[2]);
void	set_dup2(int new_fd, int old_fd);
void	set_waitpid(pid_t pid);
void	close_pipe(int pp[2]);
int		create_waitpid(t_cmd *cmd);

/* utils2.c */
size_t	pipe_cnt(t_cmd *cmd);
void	set_stdin(int pp[2]);
void	set_stdout(int pp[2]);
bool	discontinue(char *line, char *delimiter);
char	*joint_carriage_return(char *line);

/* utils3.c */
void	perror_exit(int status, char *msg);
void	error_exit(int status, char *msg);
t_cmd	*convert_cmd(t_cmd *lst);

#endif
