/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiroaki <hiroaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 17:24:39 by tasano            #+#    #+#             */
/*   Updated: 2023/01/24 00:18:23 by hiroaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_cmds.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "libft.h"
#include <sys/types.h>
#include <sys/stat.h>
#include "minishell.h"

static int	cd_error_msg(char *param, char *msg)
{
	ft_putstr_fd(SHELL, 2);
	ft_putstr_fd(": cd: ", 2);
	if (param)
	{
		ft_putstr_fd(param, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(msg, 2);
	return (1);
}

static int	is_dir(char *path)
{
	struct stat	s_st;
	int			result;

	result = stat(path, &s_st);
	if (result == -1)
		return (cd_error_msg(path, "No such file or directory"));
	if (!S_ISDIR(s_st.st_mode))
		return (cd_error_msg(path, "Not a directory"));
	if ((s_st.st_mode & S_IXUSR) == 0)
		return (cd_error_msg(path, "Permission denied"));
	return (0);
}

static int	execve_chdir(char *path)
{
	int		status;
	char	*pwd;
	char	*oldpwd;

	if (is_dir(path))
		return (1);
	status = 0;
	oldpwd = set_oldpwd(&status);
	pwd = set_pwd(path, &status);
	if (status == 0)
	{
		set_env(pwd);
		set_env(oldpwd);
	}
	free(pwd);
	free(oldpwd);
	return (status);
}

static int	cd_home(void)
{
	char	*homedir;

	homedir = get_env_char("HOME");
	if (!homedir)
		return (cd_error_msg(NULL, "HOME not set"));
	execve_chdir(homedir);
	return (0);
}

int	builtin_cd(char **argv)
{
	if (!argv[0])
		return (0);
	else if (!argv[1])
		return (cd_home());
	return (execve_chdir(argv[1]));
}
