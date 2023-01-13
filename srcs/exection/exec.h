
#ifndef EXEC_H
# define EXEC_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <sys/types.h>
# include "parser.h"
# define SHELL "minish"
# define COMMAND_NOT_FOUND 127

# define HEREDOC_PIPESIZE = 4096
# define HEREDOC_FILE = ".heredoc_tempfile"

int		exection(t_cmd *cmd, char **envp);
char	*get_cmdfile(char *cmd, char *path);
t_cmd	*convert_cmd(t_cmd *lst);
void	set_redirect(t_redirect *redirect);
void	write_heredoc(int fd, t_list *heredoc_list, int *heredoc_errno);
void	close_pipe(int pp[2]);
void	set_dup2(int new_fd, int old_fd);
void	set_pipe(int pp[2]);
void	set_waitpid(pid_t pid);
void	perror_exit(int status, char *msg);
void	error_exit(int status, char *msg);
#endif

#endif
