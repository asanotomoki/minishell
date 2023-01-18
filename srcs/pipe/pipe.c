/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiroaki <hiroaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 15:55:18 by asanotomoki       #+#    #+#             */
/*   Updated: 2022/12/24 03:46:36 by hiroaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/time.h>
#include <readline/readline.h>
#include <readline/history.h>
# include "err.h"
# include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int	pipe_cmd(t_cmds cmd1, t_cmds cmd2, char **envp)
{
	int pp[2];
	pid_t pid1;
	pid_t pid2;

	if (pipe(pp) == -1)
		return (1);
	pid1 = fork();
	if (pid1 == -1)
		exit(1);
	else if (pid1 == 0)
		first_process(cmd1, cmd2, envp);
	pid2 = fork();
	if (pid2 == -1)
		exit(1);
	else if (pid2 == 0)
		second_process(cmd1, cmd2, envp);
	close(pp[0]);
	close(pp[1]);
	return (0);
}
