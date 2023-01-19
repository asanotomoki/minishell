/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redirect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 15:42:52 by tasano            #+#    #+#             */
/*   Updated: 2023/01/20 04:32:34 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	set_inredirect(t_redirect *redirect)
{
	int	new_fd;

	if (redirect->type == INREDIRECT)
		new_fd = open(redirect->filename, O_RDONLY | O_CLOEXEC);
	if (redirect->type == HEREDOCU)
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
	t_redirect	*tmp;

	tmp = redirect;
	while (tmp)
	{
		if (tmp->type == OUTREDIRECT || tmp->type == OUTADDITION)
			set_outredirect(tmp);
		else if (tmp->type == INREDIRECT || tmp->type == HEREDOCU)
			set_inredirect(tmp);
		tmp = tmp->next;
	}
}
