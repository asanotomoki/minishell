/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanotomoki <asanotomoki@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 00:32:44 by asanotomoki       #+#    #+#             */
/*   Updated: 2022/10/31 04:09:09 by asanotomoki      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_newstrage(char *strage);
static char	*ft_read_buf(int fd, char *strage);
char		*ft_format(char *strage);

char	*get_next_line(int fd)
{
	static char	*strage;
	char		*res;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	strage = ft_read_buf(fd, strage);
	if (strage == NULL)
		return (NULL);
	res = ft_format(strage);
	strage = ft_newstrage(strage);
	return (res);
}

static char	*ft_read_buf(int fd, char *strage)
{
	char	*buf;
	ssize_t	read_size;

	while (strage == NULL || !ft_strchr(strage, '\n'))
	{
		buf = (char *)malloc(sizeof(char) * ((size_t)BUFFER_SIZE + 1));
		if (buf == NULL)
			gnl_perror_exit("gnl", EXIT_FAILURE);
		read_size = read(fd, buf, (size_t)BUFFER_SIZE);
		if (read_size <= 0)
		{
			free(buf);
			if (read_size == 0)
				return (strage);
			gnl_perror_exit("gnl", EXIT_FAILURE);
		}
		buf[read_size] = '\0';
		strage = ft_strjoin_free(strage, buf);
		if (!strage)
			return (NULL);
		free(buf);
	}
	return (strage);
}

char	*ft_format(char *strage)
{
	char	*ch;
	char	*res;
	size_t	len;

	ch = "\n";
	len = 0;
	while (!ft_strchr(ch, strage[len]))
		len++;
	if (len == 0 && strage[0] != '\n')
		return (NULL);
	len = len + 1 + (strage[len] == '\n');
	res = (char *)malloc(sizeof(char) * len);
	if (res == NULL)
		gnl_perror_exit("gnl", EXIT_FAILURE);
	ft_strlcpy(res, strage, len);
	return (res);
}

static char	*ft_newstrage(char *strage)
{
	char	*newstrage;
	char	*ch;
	size_t	len;

	if (strage == NULL)
		return (NULL);
	if (strage[0] == '\0')
	{
		free(strage);
		return (NULL);
	}
	ch = "\n";
	len = 0;
	while (!ft_strchr(ch, strage[len]))
		len++;
	newstrage = ft_strdup(strage + len + (strage[len] == '\n'));
	free(strage);
	return (newstrage);
}
