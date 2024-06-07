/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   archive_utils5.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juestrel <juestrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 12:02:46 by mfuente-          #+#    #+#             */
/*   Updated: 2024/06/07 16:19:45 by juestrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../libft/libft.h"

void	ft_echo_hd_normi(bool open, int fd, char delimiter)
{
	char	line[1];

	if (open == true)
	{
		fd = here_doc_echo(delimiter);
		printf("\n");
		while (read(fd, line, 1) > 0)
		{
			write(1, line, 1);
		}
		close(fd);
	}
}

