/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 16:21:48 by tasano            #+#    #+#             */
/*   Updated: 2023/01/14 02:13:24 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include "libft.h"

char *join_parameter(char *str, char *val, size_t i, size_t parameter_len)
{
	char *before;
	char *after;
	char *tmp;

	before = get_before(str, i);
	after = get_after(str, i + parameter_len);
	free_strval(&str);
	tmp = ft_strjoin(before, val);
	str = ft_strjoin(tmp, after);
	free_strval(&before);
	free_strval(&after);
	free_strval(&tmp);
	return (str);
}

char *set_parameter(char *str, size_t i)
{
	char *parameter;
	char *val;

	parameter = get_parameter(str + i);
	if (parameter)
	{
		val = getenv(parameter + 1);
		str = join_parameter(str, val, i, ft_strlen(parameter));
		free_strval(&parameter);
	}
	return (str);
}

int set_mode(char c, int mode)
{
	if (mode == 0)
	{
		if (c == '\'')
			return (1);
		if (c == '\"')
			return (2);
	}
	if ((mode == 1 && c == '\'') ||
		(mode == 2 && c == '\"'))
		return (0);
	return (mode);
}

char *remove_set_val(char *str, size_t i)
{
	char *before;
	char *tmp;

	before = ft_substr(str, 0, i);
	tmp = str;
	str = ft_strjoin(before, str + i + 1);
	free_strval(&before);
	free_strval(&tmp);
	return (str);
}

char *remove_quote(char *str)
{
	size_t i;
	int mode;
	int tmp_mode;

	i = 0;
	tmp_mode = 0;
	while (str[i])
	{
		mode = set_mode(str[i], tmp_mode);
		if (tmp_mode == 0 && mode)
			remove_set_val(str, i);
		else if (tmp_mode && mode == 0)
			remove_set_val(str, i);
		else
			i++;
		tmp_mode = mode;
	}
	return (str);
}

char *set_return_val(char *str)
{
	if (!str)
		return (NULL);
	else if (!str[0])
	{
		free_strval(&str);
		return (NULL);
	}
	else
	{
		str = remove_quote(str);
		if (!str || !str[0])
			set_return_val(str);
		return (str);
	}
}

char *expand(char *str)
{
	size_t i;
	int mode;

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

char *heredoc_expand(char *str)
{
	size_t i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			str = set_parameter(str, i);
		else
			i++;
	}
	return (str);
}

// char *remove_quote()
//{

//}
int redirect_expansion(t_redirect *redirect)
{
	while (redirect)
	{
		if (redirect->expnad_type == EXPANDABLE)
			redirect->filename = expand(redirect->filename);
		redirect = redirect->next;
	}
	return (0);
}

char **swap_cmd_null(char **cmd, size_t i)
{
	char *tmp;
	while (cmd[i + 1])
	{
		tmp = cmd[i];
		cmd[i] = cmd[i + 1];
		cmd[i + 1] = tmp;
		i++;
	}
	return (cmd);
}

int cmd_expansion(char **cmd)
{
	size_t i;

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

int expansion(t_cmd *cmd)
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