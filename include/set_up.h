/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_up.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juestrel <juestrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 16:20:22 by mfuente-          #+#    #+#             */
/*   Updated: 2024/06/05 16:31:29 by juestrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_UP_H
# define SET_UP_H
# ifndef _POSIX_C_SOURCE
#  define _POSIX_C_SOURCE 200809L
# endif

# include <signal.h>

char	*initial_print(char **env);
void	print_swamp(void);
void	prepare_signals(void);
void	signal_handler(int signum);
char	*read_input(char *prompt, t_lst_env **lst_env);
t_pipex	init_str_pipe(t_lst_env **lst_env);
#endif