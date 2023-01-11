/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmdfile.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 00:41:21 by tasano            #+#    #+#             */
/*   Updated: 2023/01/11 15:22:28 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char **get_paths(char *path)
{
	char **paths;

	paths = ft_split(path, ':');
	if (!paths)
		return (NULL);
	return (paths);
}

static char *find_cmdfile(char *cmd, char **cmd_paths)
{
	char *tmp;
	char *cmd_path;
	size_t i;

	i = 0;
	while (cmd_paths[i])
	{
		tmp = ft_strjoin(cmd_paths[i], "/");
		if (!tmp)
			return (NULL);
		cmd_path = ft_strjoin(tmp, cmd);
		if (!cmd_path)
			return (NULL);
		free(tmp);
		if (access(cmd_path, X_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		i++;
	}
	return (NULL);
}

static char *relative_path(char *cmd)
{
	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	else
	{
		ft_putendl_fd("command not found", 2);
		return (NULL);
	}
}

static char *absolute_path(char *cmd, char *path)
{
	char **cmd_paths;
	char *cmd_file;

	cmd_paths = get_paths(path);
	if (!cmd_paths)
		return (NULL);
	cmd_file = find_cmdfile(cmd, cmd_paths);
	if (!cmd_file)
		return (NULL);
	return (cmd_file);
}

char *get_cmdfile(char *cmd, char *path)
{
	if (ft_strchr(cmd, '/'))
		return (relative_path(cmd));
	else
		return (absolute_path(cmd, path));
}