/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   archive_utils_cmd1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfuente- <mfuente-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:54:43 by mfuente-          #+#    #+#             */
/*   Updated: 2024/05/29 09:44:08 by mfuente-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../libft/libft.h"

void	print_pipes(int fd[2])
{
	char	*line;
	dup2(0, STDOUT_FILENO);
	if (fd[0] != 0)
	{
		line = get_next_line(fd[READ]);
		while (line != NULL)
		{
			free(line);
			line = get_next_line(fd[READ]);
		}
	}
}
