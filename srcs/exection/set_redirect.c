/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redirect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiroaki <hiroaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 15:42:52 by tasano            #+#    #+#             */
/*   Updated: 2023/01/13 21:49:28 by hiroaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "../exec.h"
#include "../expansion/expansion.h"
#include <fcntl.h>
#include <string.h>
#include <readline/readline.h>
#include <sys/stat.h>
#include "../../libft/includes/libft.h"

void	write_heredoc(int fd, t_list *heredoc_list, int *heredoc_errno)
{
	ssize_t	w_len;

	errno = 0;
	while (heredoc_list)
	{
		w_len = write(fd, heredoc_list->content, heredoc_list->len);
		*heredoc_errno = errno;
		if (w_len != heredoc_list->len)
		{
			if (*heredoc_errno == 0)
				*heredoc_errno = ENOSPC;
			return ;
		}
		heredoc_list = heredoc_list->next;
	}
}

char	*expand_heredoc(char *line)
{
	return (line);
}

t_list	*creat_heredoc_list(size_t *len_ptr, char *delimiter)
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
		new = ft_lstnew(expand_heredoc(line));
		free(line);
		if (new == NULL)
			return (NULL);
		ft_lstadd_back(heredoc_list, new);
		*len_ptr += new->len;
	}
	return (heredoc_list);
}

int	use_system_pipe(t_list *heredoc_list, int *heredoc_errno)
{
	int	herepipe[2];

	if (pipe(herepipe) < 0)
		return (-1);
	write_heredoc(herepipe[1], heredoc_errno);
	if (*heredoc_errno != 0)
	{
		close(herepipe[0]);
		errno = *heredoc_errno;
		return (-1);
	}
	return (herepipe[0]);
}

int	use_tempfile(t_list *heredoc_list, int *heredoc_errno)
{
	int			fd;
	struct stat	*info;

	if (stat(HEREDOC_FILE, &info) != 0)
	{
		*heredoc_errno = EEXIST;
		return (-1);
	}
	fd = open(HEREDOC_FILE, O_CREAT | O_WRONLY, 0644);
	write_heredoc(fd, heredoc_list, heredoc_errno);
	return (fd);
}

int	heredoc_to_fd(char *delimiter)
{
	int		fd;
	int		*heredoc_errno;
	size_t	*len_ptr;
	t_list	*heredoc_list;

	*len_ptr = 0;
	*heredoc_errno = 0;
	heredoc_list = creat_heredoc_list(len_ptr, delimiter);
	if (heredoc_list == NULL)
		return (-1);
	if (*len_ptr == 0)
		fd = open("/dev/null", O_RDONLY);
	else if (*len_ptr > HEREDOC_PIPESIZE)
		fd = use_tempfile(heredoc_list, heredoc_errno);
	else
		fd = use_system_pipe(heredoc_list, heredoc_errno);
	ft_lstclear(heredoc_list, free());
	errno = heredoc_errno;
	return (fd);
}

static void	set_inredirect(t_redirect *redirect)
{
	int	new_fd;

	if (redirect->type == INREDIRECT)
		new_fd = open(redirect->filename, O_RDONLY | O_CLOEXEC);
	else if (redirect->type == HEREDOC)
	else
		new_fd = 0;
	if (new_fd < 0)
		perror_exit(EXIT_FAILURE, redirect->filename);
	set_dup2(new_fd, STDIN_FILENO);
}

static void	set_outredirect(t_redirect *redirect)
{
	int	new_fd;

	if (redirect->type == OUTREDIRECT)
		new_fd = open(redirect->filename, O_WRONLY | O_CREAT | O_TRUNC | O_CLOEXEC, 0644);
	else
		new_fd = open(redirect->filename, O_WRONLY | O_CREAT | O_CLOEXEC | O_APPEND, 0644);
	if (new_fd == -1)
		perror_exit(EXIT_FAILURE, redirect->filename);
	set_dup2(new_fd, STDOUT_FILENO);
}

void set_redirect(t_redirect *redirect)
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
