
#ifndef EXEC_H
# define EXEC_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <errno.h>
# include <sys/errno.h>
# include <sys/types.h>
# include "parser.h"
# include "libft.h"
# define SHELL "minish"
# define COMMAND_NOT_FOUND 127

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

# define HEREDOC_TEMPFILE ".heredoc_tempfile"

int		exection(t_cmd *cmd, char **envp);
char	*get_cmdfile(char *cmd, char *path);
t_cmd	*convert_cmd(t_cmd *lst);
void	set_redirect(t_redirect *redirect);
void	close_pipe(int pp[2]);
void	set_dup2(int new_fd, int old_fd);
void	set_pipe(int pp[2]);
void	set_waitpid(pid_t pid);
void	heredoc_to_fd(t_cmd *cmd);
void	perror_exit(int status, char *msg);
void	error_exit(int status, char *msg);
#endif
