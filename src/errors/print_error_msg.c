/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error_msg.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juestrel <juestrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:07:01 by juestrel          #+#    #+#             */
/*   Updated: 2024/06/06 13:11:57 by juestrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../libft/libft.h"

void	error_msgs(t_errors error)
{
	if (error == TOKEN_MALLOC_FAILURE)
		printf("Error with malloc in token list, exiting program\n");
	else if (error == AST_MALLOC_FAILURE)
		printf("Error with malloc in AST, exiting program\n");
	else if (error == PWD_ERROR)
		printf("Error obtaining PWD\n");
	else if (error == PIPE_ERROR)
		printf("Error creating pipe\n");
	exit(EXIT_FAILURE);
}
