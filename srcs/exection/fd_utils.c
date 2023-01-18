/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiroaki <hiroaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 15:02:35 by hiroaki           #+#    #+#             */
/*   Updated: 2023/01/19 03:22:17 by hiroaki          ###   ########.fr       */
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
