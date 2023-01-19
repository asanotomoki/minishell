/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiroaki <hiroaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 04:48:53 by hiroaki           #+#    #+#             */
/*   Updated: 2023/01/19 21:38:58 by hiroaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "util.h"

static void	heredoc_to_fd(t_cmd *cmd)
{
	t_list		*document;
	t_redirect	*redir;
	size_t		len;

	if (cmd == NULL)
		return ;
	redir = cmd->redirect;
	if (redir && redir->type == HEREDOCU)
	{
		len = 0;
		document = creat_document(&len, redir->filename);
		if (len == 0 || g_shell.heredoc_interrupted)
			redir->heredoc_fd = open("/dev/null", O_RDONLY);
		else if (len > HEREDOC_PIPESIZE)
			redir->heredoc_fd = use_tempfile(document);
		else
			redir->heredoc_fd = use_system_pipe(document);
		if (redir->heredoc_fd < 0)
			perror_exit(EXIT_FAILURE, "here document");
		ft_lstclear(&document, free);
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
