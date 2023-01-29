/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiroaki <hiroaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 00:55:39 by hiroaki           #+#    #+#             */
/*   Updated: 2023/01/30 00:05:48 by hiroaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"

int	write_heredoc(int fd, t_list *document)
{
	ssize_t	p_len;

	errno = 0;
	while (document)
	{
		p_len = ft_putstr_fd((char *)document->content, fd);
		if (p_len != (ssize_t)document->len)
		{
			if (errno == 0)
				errno = ENOSPC;
			return (errno);
		}
		document = document->next;
	}
	return (0);
}

t_list	*creat_document(size_t *len_ptr, char *delimiter, bool is_quoted)
{
	char	*line;
	t_list	*new;
	t_list	*document;

	document = NULL;
	while (1)
	{
		line = readline("> ");
		if (discontinue(line, delimiter))
		{
			free(line);
			break ;
		}
		line = joint_carriage_return(line);
		if (is_quoted)
			new = ft_lstnew(line);
		else
			new = ft_lstnew(heredoc_expand(line));
		if (new == NULL)
			return (NULL);
		ft_lstadd_back(&document, new);
		*len_ptr += new->len;
	}
	return (document);
}

int	use_tempfile(t_list *document)
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
	fd2 = open(HEREDOC_TEMPFILE, O_RDONLY, 0600);
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

bool	discontinue(char *line, char *delimiter)
{
	if (g_shell.heredoc_interrupted)
		return (true);
	if (ft_strcmp(line, delimiter) == 0)
		return (true);
	return (false);
}

char	*joint_carriage_return(char *line)
{
	char	*new_line;

	new_line = ft_strjoin(line, "\n");
	free(line);
	if (new_line == NULL)
		return (NULL);
	return (new_line);
}
