/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiroaki <hiroaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 23:54:22 by tasano            #+#    #+#             */
/*   Updated: 2023/01/19 01:44:43 by hiroaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTIL_H
# define UTIL_H

/* error_utils.c */
int		err_msg(char *param, char *msg, int status);
int		perr_msg(char *msg);
void	perror_exit(int status, char *msg);
void	error_exit(int status, char *param, char *msg);

/* free_utils.c */
void	free_strval(char **str);
void	free_args(char ***input);

/* status_utils.c */
int		get_status(void);
void	set_status(int status);
int		set_get_status(int status);

/* env_utils.c */
char	*env_put_error(char *function, char *val);
size_t	search_param(char **argv, char *param);
int		init_env(void);
char	**get_env(void);

/* signal_utils.c */
void	ignore_signal(int sig_no);
void	signal_handler(int sig_no);
void	init_sigaction(void);
void	catch_signal(void);

/* set_readline.c */
int		rl_routine(void);
void	set_rl_routine(void);
int		rl_heredoc_event(void);
void	set_rl_heredoc_event(void);

#endif
