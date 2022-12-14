/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 00:42:50 by tasano            #+#    #+#             */
/*   Updated: 2023/01/11 16:32:15 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include <fcntl.h>
#include "libft.h"

void set_pipe(int pp[2])
{
	if (pipe(pp) == -1)
		perror_exit(EXIT_FAILURE, "pipe");
}

void close_pipe(int pp[2])
{
	close(pp[0]);
	close(pp[1]);
}

void	set_waitpid(pid_t pid)
{
	if (waitpid(pid, NULL, 0) == -1)
		perror_exit(EXIT_FAILURE, "waitpid");
}

void	set_dup2(int new_fd, int old_fd)
{
	if (dup2(new_fd, old_fd) == -1)
		perror_exit(EXIT_FAILURE, "dup2");
}