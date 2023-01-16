/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cmds.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 23:54:22 by tasano            #+#    #+#             */
/*   Updated: 2023/01/16 16:46:59 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_CMDS_H
# define BUILTIN_CMDS_H

# include <stdio.h>
# include <stddef.h>

int		builtin_echo(char **argv);
int		builtin_exit(size_t argc, char **argv);
int		builtin_env(void);
int		builtin_export(char **argv);
int		set_env(char *s);
char	*export_put_error(char *val);
char	*get_param(char *val);
char	*get_key(char *param);

int		builtin_pwd(void);
int		builtin_unset(char **argv);
int		builtin_cd(char **argv);

size_t	search_param(char **argv, char *param);
char	**get_env(void);
int		init_env(void);
char	*env_put_error(char *function, char *val);

#endif
