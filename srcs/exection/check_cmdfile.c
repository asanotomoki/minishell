/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmdfile.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiroaki <hiroaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 21:59:00 by tasano            #+#    #+#             */
/*   Updated: 2023/01/19 03:20:41 by hiroaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"

int	check_cmdfile(char	*filename, char	*param)
{
	struct stat	s_st;
	int			result;

	result = stat(filename, &s_st);
	if (result == -1)
		error_exit(COMMAND_NOT_FOUND, param, "command not found");
	if (S_ISDIR(s_st.st_mode))
	{
		free_strval(&filename);
		error_exit(126, param, "is a directory");
	}
	if ((s_st.st_mode & S_IXUSR) == 0)
	{
		free_strval(&filename);
		error_exit(126, param, "Permission denied");
	}
	return (0);
}
