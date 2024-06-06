/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juestrel <juestrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:12:32 by juestrel          #+#    #+#             */
/*   Updated: 2024/06/06 13:11:21 by juestrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

typedef enum e_errors
{
	TOKEN_MALLOC_FAILURE,
	AST_MALLOC_FAILURE,
	PWD_ERROR,
	PIPE_ERROR
}			t_errors;

void	error_msgs(t_errors error);
#endif
