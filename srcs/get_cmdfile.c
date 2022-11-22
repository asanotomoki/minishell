/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmdfile.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 16:55:49 by asanotomoki       #+#    #+#             */
/*   Updated: 2022/11/22 12:17:12 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**get_paths(char **envp)
{
	char	**paths;

	while (*envp && (ft_strncmp(*envp, "PATH=", 5) != 0))
		envp++;
	if (!*envp)
		err_msg("ENVP ERR");
	*envp += 5;
	paths = ft_split(*envp, ':');
	if (!paths)
		perr_msg("ft_split");
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
			perr_msg("ft_strjoin");
		cmd_path = ft_strjoin(tmp, cmd);
		if (!cmd_path)
			perr_msg("ft_strjoin");
		free(tmp);
		if (access(cmd_path, X_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		i++;
	}
	return (NULL);
}

char	*get_cmdfile(char *cmd, char **envp)
{
	char	**cmd_paths;
	char	*cmd_file;

	if (ft_strchr(cmd, '/') && !access(cmd, X_OK))
		return (ft_strdup(cmd));
	else
	{
		cmd_paths = get_paths(envp);
		cmd_file = find_cmdfile(cmd, cmd_paths);
		free_args(cmd_paths);
		return (cmd_file);
	}
}
