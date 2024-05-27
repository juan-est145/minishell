/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_up.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfuente- <mfuente-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 16:20:22 by mfuente-          #+#    #+#             */
/*   Updated: 2024/05/27 16:20:23 by mfuente-         ###   ########.fr       */
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