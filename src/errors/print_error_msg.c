/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error_msg.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juestrel <juestrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:07:01 by juestrel          #+#    #+#             */
/*   Updated: 2024/06/06 12:44:05 by juestrel         ###   ########.fr       */
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
	exit(EXIT_FAILURE);
}
