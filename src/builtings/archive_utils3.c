/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   archive_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfuente- <mfuente-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 10:27:27 by mfuente-          #+#    #+#             */
/*   Updated: 2024/05/16 13:18:35 by mfuente-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../libft/libft.h"

int	redirect_stdout(t_ast *node)
{
	int	fd;

	fd = 0;
	if (node->redirections != NULL)
	{
		if (redirected_destination(&node->redirections) == -1)
		{
			printf("ERROR en la redireccion del archivo\n");
			return (-1);
		}
		else
		{
			fd = redirected_destination(&node->redirections);
			dup2(fd, STDOUT_FILENO);
		}
	}
	return (fd);
}
