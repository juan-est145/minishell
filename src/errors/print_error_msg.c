/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error_msg.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-est145 <juan-est145@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 14:31:50 by juan-est145       #+#    #+#             */
/*   Updated: 2024/04/30 15:04:33 by juan-est145      ###   ########.fr       */
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
	exit(1);
}
