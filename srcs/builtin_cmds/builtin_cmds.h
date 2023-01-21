/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cmds.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 23:54:22 by tasano            #+#    #+#             */
/*   Updated: 2023/01/21 13:43:09 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_CMDS_H
# define BUILTIN_CMDS_H

# include <stdio.h>
# include <stddef.h>

typedef enum e_cmd_type
{
	MINI_ECHO = 1,
	MINI_CD,
	MINI_PWD,
	MINI_EXPORT,
	MINI_UNSET,
	MINI_ENV,
	MINI_EXIT,
	DOT
}	t_cmd_type;

int		builtin_echo(char **argv);
int		builtin_exit(char **argv);
int		builtin_env(void);
int		builtin_export(char **argv);
int		builtin_pwd(void);
int		builtin_unset(char **argv);
int		builtin_cd(char **argv);

int		set_env(char *s);
char	*export_put_error(char *val);

char	*get_param(char *val);
char	*get_key(char *param);
int		check_param(char *param);

#endif
