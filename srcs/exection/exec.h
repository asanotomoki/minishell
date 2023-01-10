
#ifndef EXEC_H
# define EXEC_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <sys/types.h>
# include <parser.h>

typedef enum e_redir_kind {
	IN_REDIR,
	OUT_REDIR,
	HEREDOC,
}	t_redir_kind;

//typedef struct s_redirect
//{
//	char                    *filename;
//    t_token_type             type;
//    t_token_type            expnad_type;
//    struct s_redirect    *next;
//} t_redirect;

typedef struct s_parse_ast {
	pid_t				pid;
	int					pfd[2];
	char			    **cmd;
	t_redirect			*input;
	t_redirect			*output;
	struct s_parse_ast	*next_pipe;
	struct s_parse_ast	*prev_pipe;
}	t_parse_ast;

//typedef struct s_exec_data
//{
//	int	pipe_cnt;
//}	t_exec_data;

t_parse_ast	*execlst_new(t_cmd *cmd);
void 		execlst_addback(t_parse_ast **lst, t_parse_ast *new);
void		execlst_free(t_parse_ast **cmd);
int	exection(t_cmd *cmd, char **envp);
t_parse_ast *execlst_addfront(t_parse_ast **lst, t_parse_ast *new);
#endif