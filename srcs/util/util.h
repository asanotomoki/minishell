/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiroaki <hiroaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 23:54:22 by tasano            #+#    #+#             */
/*   Updated: 2023/01/30 04:00:48 by hiroaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTIL_H
# define UTIL_H

# include "libft.h"

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
int		init_env(void);
t_list	*get_env(void);
t_list	*get_env_val(char *param);
char	**get_env_argv(void);
char	*get_env_char(char *param);

/* signal_utils.c */
void	sigint_handler(int sig_no);
void	ignore_signal(int sig_no);

/* signal_utils2.c */
void	catch_signal(void);

/* readline_utils.c */
int		rl_routine(void);
void	set_rl_routine(void);
int		rl_heredoc_event(void);
void	set_rl_heredoc_event(void);

/* args_utils */
size_t	cnt_argc(char **argv);
char	**append_args(char **args, size_t argc, char *new);

#endif
