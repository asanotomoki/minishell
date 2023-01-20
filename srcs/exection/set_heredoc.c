/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiroaki <hiroaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 04:48:53 by hiroaki           #+#    #+#             */
/*   Updated: 2023/01/21 01:21:20 by hiroaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "util.h"

int	set_hiredoc_fd(t_redirect *redirect)
{
	t_list	*document;
	size_t	len;

	len = 0;
	document = creat_document(&len, redirect->filename);
	if (len == 0 || g_shell.heredoc_interrupted)
		redirect->heredoc_fd = open("/dev/null", O_RDONLY);
	else if (len > HEREDOC_PIPESIZE)
		redirect->heredoc_fd = use_tempfile(document);
	else
		redirect->heredoc_fd = use_system_pipe(document);
	if (redirect->heredoc_fd < 0)
		perror_exit(EXIT_FAILURE, "here document");
	ft_lstclear(&document, free);
	return (redirect->heredoc_fd);
}

static void	heredoc_to_fd(t_cmd *cmd)
{
	t_redirect	*tmp;

	if (cmd == NULL)
		return ;
	tmp = cmd->redirect;
	while (tmp)
	{
		if (tmp->type == HEREDOCU)
			tmp->heredoc_fd = set_hiredoc_fd(tmp);
		tmp = tmp->next;
	}
	if (!g_shell.heredoc_interrupted)
		return (heredoc_to_fd(cmd->piped_cmd));
}

void	set_heredocument(t_cmd *cmd)
{
	set_rl_heredoc_event();
	heredoc_to_fd(cmd);
	set_rl_routine();
	if (g_shell.heredoc_interrupted)
		g_shell.heredoc_interrupted = 0;
}
