/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiroaki <hiroaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 04:48:53 by hiroaki           #+#    #+#             */
/*   Updated: 2023/01/15 21:02:06 by hiroaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "../expansion/expansion.h"
#include <fcntl.h>
#include <readline/readline.h>
#include <sys/stat.h>

static int	write_heredoc(int fd, t_list *document)
{
	ssize_t	p_len;

	errno = 0;
	while (document)
	{
		p_len = ft_putendl_fd(document->content, fd);
		if (p_len != (ssize_t)document->len + 1)
		{
			if (errno == 0)
				errno = ENOSPC;
			return (errno);
		}
		document = document->next;
	}
	return (0);
}

bool	discontinue(char *line, char *delimiter)
{
	//if (g_shell.heredoc_interrupted)
	//	return (true);
	if (ft_strcmp(line, delimiter) == 0)
		return (true);
	return (false);
}

static t_list	*creat_document(size_t *len_ptr, char *delimiter)
{
	char	*line;
	t_list	*new;
	t_list	*document;

	if (delimiter == NULL)
		return (NULL);
	document = NULL;
	while (1)
	{
		line = readline("> ");
		if (discontinue(line, delimiter))
			break ;
		new = ft_lstnew(heredoc_expand(line));
		if (new == NULL)
			return (NULL);
		ft_lstadd_back(&document, new);
		*len_ptr += new->len;
	}
	return (document);
}

static int	use_system_pipe(t_list *document)
{
	int	e;
	int	herepipe[2];

	if (pipe(herepipe) < 0)
		return (-1);
	e = write_heredoc(herepipe[1], document);
	if (e != 0)
	{
		close(herepipe[0]);
		errno = e;
		return (-1);
	}
	close(herepipe[1]);
	return (herepipe[0]);
}

static int	use_tempfile(t_list *document)
{
	int			e;
	int			fd;
	int			fd2;
	struct stat	info;

	stat(HEREDOC_TEMPFILE, &info);
	e = errno;
	if (e != ENOENT)
	{
		errno = EEXIST;
		return (-1);
	}
	fd = open(HEREDOC_TEMPFILE, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	e = write_heredoc(fd, document);
	fd2 = open (HEREDOC_TEMPFILE, O_RDONLY, 0600);
	close(fd);
	if (e != 0 || unlink(HEREDOC_TEMPFILE) < 0)
	{
		if (e != 0)
			errno = e;
		close (fd2);
		return (-1);
	}
	return (fd2);
}

void	heredoc_to_fd(t_cmd *cmd)
{
	t_list		*document;
	t_redirect	*redir;
	size_t		len;

	if (cmd == NULL)
		return ;
	redir = cmd->redirect;
	if (redir && redir->type == HEREDOC)
	{
		len = 0;
		document = creat_document(&len, redir->filename);
		if (len == 0)
			redir->heredoc_fd = open("/dev/null", O_RDONLY);
		else if (len > HEREDOC_PIPESIZE)
			redir->heredoc_fd = use_tempfile(document);
		else
			redir->heredoc_fd = use_system_pipe(document);
		ft_lstclear(&document, free);
	}
	heredoc_to_fd(cmd->piped_cmd);
}
