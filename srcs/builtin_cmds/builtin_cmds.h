/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cmds.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 23:54:22 by tasano            #+#    #+#             */
/*   Updated: 2023/01/16 00:58:57 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_CMDS_H
# define BUILTIN_CMDS_H

#include <stdio.h>

int		builtin_echo(char **argv);
int		builtin_exit(size_t argc, char **argv);
int		builtin_env();
int		builtin_export(char **argv);
int		builtin_pwd();
int		builtin_unset(char **argv);
int		builtin_cd(char **argv);


size_t	search_param(char **argv, char *param);
int echo_cmd(char **argv, int option);
#endif
