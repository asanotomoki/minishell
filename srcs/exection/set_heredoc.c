/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiroaki <hiroaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 04:48:53 by hiroaki           #+#    #+#             */
/*   Updated: 2023/01/14 04:49:37 by hiroaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "../expansion/expansion.h"
#include <fcntl.h>
#include <readline/readline.h>
#include <sys/stat.h>

static void	write_heredoc(int fd, t_list *heredoc_list, int *heredoc_errno)
{
	ssize_t	p_len;

	errno = 0;
	while (heredoc_list)
	{
		p_len = ft_putendl_fd(heredoc_list->content, fd);
		*heredoc_errno = errno;
		if (p_len != (ssize_t)heredoc_list->len + 1)
		{
			if (*heredoc_errno == 0)
				*heredoc_errno = ENOSPC;
			return ;
		}
		heredoc_list = heredoc_list->next;
	}
}

static t_list	*creat_heredoc_list(size_t *len_ptr, char *delimiter)
{
	char	*line;
	t_list	*new;
	t_list	*heredoc_list;

	if (delimiter == NULL)
		return (NULL);
	heredoc_list = NULL;
	while (1)
	{
		line = readline("> ");
		if (ft_strcmp(line, delimiter) == 0)
			break ;
		new = ft_lstnew(heredoc_expand(line));
		if (new == NULL)
			return (NULL);
		ft_lstadd_back(&heredoc_list, new);
		*len_ptr += new->len;
	}
	return (heredoc_list);
}

static int	use_system_pipe(t_list *heredoc_list, int *heredoc_errno)
{
	int	herepipe[2];

	if (pipe(herepipe) < 0)
		return (-1);
	write_heredoc(herepipe[1], heredoc_list, heredoc_errno);
	if (*heredoc_errno != 0)
	{
		close(herepipe[0]);
		errno = *heredoc_errno;
		return (-1);
	}
	close(herepipe[1]);
	return (herepipe[0]);
}

static int	use_tempfile(t_list *heredoc_list, int *heredoc_errno)
{
	int			fd;
	int			fd2;
	struct stat	info;

	errno = 0;
	stat(HEREDOC_FILE, &info);
	if (errno != ENOENT)
	{
		*heredoc_errno = EEXIST;
		return (-1);
	}
	fd = open(HEREDOC_FILE, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	write_heredoc(fd, heredoc_list, heredoc_errno);
	fd2 = open (HEREDOC_FILE, O_RDONLY, 0600);
	close(fd);
	if (unlink(HEREDOC_FILE) < 0)
	{
		*heredoc_errno = errno;
		close (fd2);
		errno = *heredoc_errno;
		return (-1);
	}
	return (fd2);
}

int	heredoc_to_fd(char *delimiter)
{
	int		fd;
	int		heredoc_errno;
	size_t	len;
	t_list	*heredoc_list;

	len = 0;
	heredoc_errno = 0;
	heredoc_list = creat_heredoc_list(&len, delimiter);
	if (len == 0)
		fd = open("/dev/null", O_RDONLY);
	else if (len > HEREDOC_PIPESIZE)
		fd = use_tempfile(heredoc_list, &heredoc_errno);
	else
		fd = use_system_pipe(heredoc_list, &heredoc_errno);
	ft_lstclear(&heredoc_list, free);
	errno = heredoc_errno;
	return (fd);
}
