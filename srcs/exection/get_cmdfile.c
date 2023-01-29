/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmdfile.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 00:41:21 by tasano            #+#    #+#             */
/*   Updated: 2023/01/27 00:01:07 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "util.h"

static char	**get_paths(char *path)
{
	char	**paths;

	paths = ft_split(path, ':');
	if (!paths)
		perror_exit(EXIT_FAILURE, "malloc");
	return (paths);
}

static char	*find_cmdfile(char *cmd, char **cmd_paths)
{
	char	*tmp;
	char	*cmd_path;
	size_t	i;

	i = 0;
	while (cmd_paths[i])
	{
		tmp = ft_strjoin(cmd_paths[i], "/");
		if (!tmp)
			perror_exit(EXIT_FAILURE, "malloc");
		cmd_path = ft_strjoin(tmp, cmd);
		if (!cmd_path)
			perror_exit(EXIT_FAILURE, "malloc");
		free(tmp);
		if (access(cmd_path, F_OK) == 0)
		{
			free_args(&cmd_paths);
			return (cmd_path);
		}
		free(cmd_path);
		i++;
	}
	return (NULL);
}

static char	*relative_path(char *cmd)
{
	if (access(cmd, F_OK) == 0)
		return (ft_strdup(cmd));
	else
		error_exit(127, cmd, "No such file or directory");
	return (NULL);
}

static char	*absolute_path(char *cmd, char *path)
{
	char	**cmd_paths;

	if (!path)
		error_exit(127, cmd, "No such file or directory");
	cmd_paths = get_paths(path);
	if (!cmd_paths)
		perror_exit(EXIT_FAILURE, "malloc");
	return (find_cmdfile(cmd, cmd_paths));
}

char	*get_cmdfile(char *cmd, char *path)
{
	if (ft_strchr(cmd, '/'))
		return (relative_path(cmd));
	else
		return (absolute_path(cmd, path));
}
