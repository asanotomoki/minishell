/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cmds.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiroaki <hiroaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 23:54:22 by tasano            #+#    #+#             */
/*   Updated: 2023/01/24 00:13:31 by hiroaki          ###   ########.fr       */
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

char	*set_pwd(char *path, int *status);
char	*set_oldpwd(int *status);

#endif
