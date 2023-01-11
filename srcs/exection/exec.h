
#ifndef EXEC_H
# define EXEC_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <sys/types.h>
# include <parser.h>

int	exection(t_cmd *cmd, char **envp);


char *get_cmdfile(char *cmd, char *path);

t_cmd *convert_cmd(t_cmd *lst);

void set_outredirect(t_redirect *redirect);
void set_inredirect(t_redirect *redirect);
void close_pipe(int pp[2]);
void set_dup2(int new_fd, int old_fd);
void set_pipe(int pp[2]);
void set_waitpid(pid_t pid);
#endif