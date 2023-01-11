/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redirect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 15:42:52 by tasano            #+#    #+#             */
/*   Updated: 2023/01/11 15:43:53 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "exec.h"
#include "fcntl.h"

void set_inredirect(t_redirect *redirect)
{
	int new_fd;

	while (redirect)
	{
		//heredoc追加
		if (redirect->type == INREDIRECT)
			new_fd = open(redirect->filename, O_RDONLY | O_CLOEXEC);
		if (new_fd < 0)
			perror(redirect->filename);
		set_dup2(new_fd, STDIN_FILENO);
		redirect = redirect->next;
	}
}

void set_outredirect(t_redirect *redirect)
{
	int new_fd;

	while (redirect)
	{
		if (redirect->type == OUTREDIRECT)
			new_fd = open(redirect->filename, O_WRONLY | O_CREAT | O_TRUNC | O_CLOEXEC, 0644);
		else if (redirect->type == OUTADDITION)
			new_fd = open(redirect->filename, O_WRONLY | O_CREAT | O_CLOEXEC | O_APPEND, 0644);
		if (new_fd == -1)
			perror("output file");
		set_dup2(new_fd, STDOUT_FILENO);
		redirect = redirect->next;
	}
}