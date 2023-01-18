/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiroaki <hiroaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 23:54:22 by tasano            #+#    #+#             */
/*   Updated: 2023/01/18 21:09:36 by hiroaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTIL_H
# define UTIL_H

# include <stdio.h>

int		err_msg(char *param, char *msg, int status);
int		perr_msg(char *msg);

void	free_strval(char **str);
void	free_args(char ***input);

int		get_status(void);
void	set_status(int status);
int		set_get_status(int status);

size_t	search_param(char **argv, char *param);
char	**get_env(void);
int		init_env(void);
char	*env_put_error(char *function, char *val);

int		rl_routine(void);
void	set_rl_routine(void);

void	signal_handler(int signo);
void	init_sigaction(void);
void	catch_signal(void);

#endif
