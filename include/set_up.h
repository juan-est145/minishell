/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_up.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-est145 <juan-est145@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:26:18 by juestrel          #+#    #+#             */
/*   Updated: 2024/05/24 13:14:10 by juan-est145      ###   ########.fr       */
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
#endif