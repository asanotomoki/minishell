/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 16:21:48 by tasano            #+#    #+#             */
/*   Updated: 2023/01/17 01:08:11 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include "libft.h"
#include "util.h"

char	*heredoc_expand(char *str)
{
	size_t	i;

	i = 0;
	if (str == NULL)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '$')
			str = set_parameter(str, i);
		else
			i++;
	}
	if (!str[0])
	{
		free_strval(&str);
		return (NULL);
	}
	return (str);
}

char	*expand(char *str)
{
	size_t	i;
	int		mode;

	i = 0;
	mode = 0;
	while (str[i])
	{
		mode = set_mode(str[i], mode);
		if (mode == 0 && str[i] == '$')
			str = set_parameter(str, i);
		else
			i++;
	}
	return (set_return_val(str));
}

int	redirect_expansion(t_redirect *redirect)
{
	char	*filename;

	while (redirect)
	{
		filename = expand(redirect->filename);
		if (!filename)
			return (err_msg(redirect->filename, "ambiguous redirect", 1));
		redirect->filename = filename;
		redirect = redirect->next;
	}
	return (0);
}

int	cmd_expansion(char **cmd)
{
	size_t	i;

	i = 0;
	while (cmd[i])
	{
		cmd[i] = expand(cmd[i]);
		if (!cmd[i])
			cmd = swap_cmd_null(cmd, i);
		else
			i++;
	}
	return (0);
}

int	expansion(t_cmd *cmd)
{
	while (cmd)
	{
		if (redirect_expansion(cmd->redirect))
			return (1);
		if (0 < cmd->argc)
			cmd_expansion(cmd->cmd);
		cmd = cmd->piped_cmd;
	}
	return (0);
}
