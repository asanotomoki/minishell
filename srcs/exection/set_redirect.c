/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redirect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 15:42:52 by tasano            #+#    #+#             */
/*   Updated: 2023/01/21 08:09:06 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	set_inredirect(t_redirect *redirect)
{
	if (redirect->type == INREDIRECT)
		redirect->fd = open(redirect->filename, O_RDONLY | O_CLOEXEC);
	if (redirect->type == HEREDOCU)
		redirect->fd = redirect->heredoc_fd;
	if (redirect->fd == -1)
		return (perr_msg(redirect->filename));
	set_dup2(redirect->fd, STDIN_FILENO);
	return (0);
}

static int	set_outredirect(t_redirect *redirect)
{
	char	*f_name;

	f_name = redirect->filename;
	if (redirect->type == OUTREDIRECT)
		redirect->fd = \
		open(f_name, O_WRONLY | O_CREAT | O_TRUNC | O_CLOEXEC, 0644);
	else
		redirect->fd = \
		open(f_name, O_WRONLY | O_CREAT | O_CLOEXEC | O_APPEND, 0644);
	if (redirect->fd == -1)
		return (perr_msg(redirect->filename));
	set_dup2(redirect->fd, STDOUT_FILENO);
	return (0);
}

int	set_redirect(t_redirect *redirect)
{
	t_redirect	*tmp;
	int			status;

	tmp = redirect;
	status = 0;
	while (tmp)
	{
		if (tmp->type == OUTREDIRECT || tmp->type == OUTADDITION)
			status = set_outredirect(tmp);
		else if (tmp->type == INREDIRECT || tmp->type == HEREDOCU)
			status = set_inredirect(tmp);
		if (status)
			break ;
		tmp = tmp->next;
	}
	if (status)
		set_status(status);
	return (status);
}
