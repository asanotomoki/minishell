/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 00:11:51 by hiroaki           #+#    #+#             */
/*   Updated: 2023/01/25 21:53:19 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_cmds.h"
#include "libft.h"
#include "util.h"

char	*set_pwd(char *path, int *status)
{
	char	*pwd;
	char	*dir;

	*status = chdir(path);
	dir = getcwd(NULL, 0);
	if (dir == NULL)
	{
		*status = 1;
		return (NULL);
	}
	pwd = ft_strjoin("PWD=", dir);
	free_strval(&dir);
	if (pwd == NULL)
	{
		*status = 1;
		return (NULL);
	}
	return (pwd);
}

char	*set_oldpwd(int *status)
{
	char	*oldpwd;
	char	*olddir;

	olddir = getcwd(NULL, 0);
	if (olddir == NULL)
	{
		*status = 1;
		return (NULL);
	}
	oldpwd = ft_strjoin("OLDPWD=", olddir);
	free_strval(&olddir);
	if (oldpwd == NULL)
	{
		*status = 1;
		return (NULL);
	}
	return (oldpwd);
}
