/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanotomoki <asanotomoki@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 15:43:45 by asanotomoki       #+#    #+#             */
/*   Updated: 2022/11/25 16:04:17 by asanotomoki      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include "err.h"
# include "libft.h"

typedef struct s_cmds
{
	char *cmd_file;
	char **cmds;
} t_cmds;


char	*get_cmdfile(char *cmd, char **envp);
int		basic_cmd(char *cmd, char **envp);

//utils
int		perr_msg(char *msg);
int		err_msg(char *msg);
void free_args(char **cmd_paths);

#endif
