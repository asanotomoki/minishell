/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redirect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiroaki <hiroaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 15:42:52 by tasano            #+#    #+#             */
/*   Updated: 2023/01/15 17:25:34 by hiroaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include <fcntl.h>
#include <readline/readline.h>
#include <sys/stat.h>

static void	set_inredirect(t_redirect *redirect)
{
	int	new_fd;

	if (redirect->type == INREDIRECT)
		new_fd = open(redirect->filename, O_RDONLY | O_CLOEXEC);
	if (redirect->type == HEREDOC)
		new_fd = redirect->heredoc_fd;
	if (new_fd == -1)
		perror_exit(EXIT_FAILURE, redirect->filename);
	set_dup2(new_fd, STDIN_FILENO);
}

static void	set_outredirect(t_redirect *redirect)
{
	int		new_fd;
	char	*f_name;

	f_name = redirect->filename;
	if (redirect->type == OUTREDIRECT)
		new_fd = open(f_name, O_WRONLY | O_CREAT | O_TRUNC | O_CLOEXEC, 0644);
	else
		new_fd = open(f_name, O_WRONLY | O_CREAT | O_CLOEXEC | O_APPEND, 0644);
	if (new_fd == -1)
		perror_exit(EXIT_FAILURE, redirect->filename);
	set_dup2(new_fd, STDOUT_FILENO);
}

void	set_redirect(t_redirect *redirect)
{
	while (redirect)
	{
		if (redirect->type == OUTREDIRECT || redirect->type == OUTADDITION)
			set_outredirect(redirect);
		else if (redirect->type == INREDIRECT || redirect->type == HEREDOC)
			set_inredirect(redirect);
		redirect = redirect->next;
	}
}

/*
wc -l test1 < test2 > test3 < test1 < test2 < test3 |
cmd : [[wc] [-l]]
out : test1 > test3
in  : test2 < test1 < test2 < test3
*/
