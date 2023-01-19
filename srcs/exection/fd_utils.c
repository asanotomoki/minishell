/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 15:02:35 by hiroaki           #+#    #+#             */
/*   Updated: 2023/01/20 02:10:55 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	set_stdout(int pp[2])
{
	set_dup2(pp[1], STDOUT_FILENO);
	close_pipe(pp);
}

void	set_stdin(int pp[2])
{
	set_dup2(pp[0], STDIN_FILENO);
	close_pipe(pp);
}

void	set_dup2(int new_fd, int old_fd)
{
	if (dup2(new_fd, old_fd) == -1)
		perror_exit(EXIT_FAILURE, "dup2");
}
