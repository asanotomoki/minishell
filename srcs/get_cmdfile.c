/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmdfile.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanotomoki <asanotomoki@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 16:55:49 by asanotomoki       #+#    #+#             */
/*   Updated: 2022/11/22 21:37:05 by asanotomoki      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**get_paths(char **envp)
{
	char	**paths;

	while (*envp && (ft_strncmp(*envp, "PATH=", 5) != 0))
		envp++;
	if (!*envp)
		return (NULL);
	*envp += 5;
	paths = ft_split(*envp, ':');
	if (!paths)
		return (NULL);
	return (paths);
}

static	char	*find_cmdfile(char *cmd, char **cmd_paths)
{
	char	*tmp;
	char	*cmd_path;
	size_t	i;

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

static	char *relative_path(char *cmd)
{
	if (!access(cmd, X_OK))
		return (ft_strdup(cmd));
	else
	{
		err_msg("command not found");
		return (NULL);
	}
}

static	char *absolute_path(char *cmd, char **envp)
{
	char	**cmd_paths;
	char	*cmd_file;

	cmd_paths = get_paths(envp);
	if (!cmd_paths)
		return (NULL);
	cmd_file = find_cmdfile(cmd, cmd_paths);
	if (!cmd_file)
	{
		free_args(cmd_paths);
		return (NULL);
	}
	free_args(cmd_paths);
	return (cmd_file);
}

char	*get_cmdfile(char *cmd, char **envp)
{
	if (ft_strchr(cmd, '/'))
		return (relative_path(cmd));
	else
		return (absolute_path(cmd, envp));
}
