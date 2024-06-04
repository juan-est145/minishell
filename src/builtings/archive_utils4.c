/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   archive_utils4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfuente- <mfuente-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 12:35:10 by juan-est145       #+#    #+#             */
/*   Updated: 2024/06/04 18:01:09 by mfuente-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../libft/libft.h"

void	dup_fd_arrays(t_process_cmd type_cmd, t_pipex *str_pipe, int fd[2])
{
	unsigned int	array_num;

	array_num = str_pipe->fd_array_num;
	if (type_cmd == ENTRY_PIPE)
	{
		if (fd[1] > 0)
			return ;
		dup2(str_pipe->fd_arrays[0][WRITE], STDOUT_FILENO);
		close(str_pipe->fd_arrays[0][READ]);
	}
	else if (type_cmd == MIDDLE_PIPE)
	{
		if (fd[0] == 0)
			dup2(str_pipe->fd_arrays[array_num - 2][READ], STDIN_FILENO);
		if (fd[1] == 0)
			dup2(str_pipe->fd_arrays[array_num - 1][WRITE], STDOUT_FILENO);
		close(str_pipe->fd_arrays[array_num - 2][READ]);
		close(str_pipe->fd_arrays[array_num - 1][READ]);
		close(str_pipe->fd_arrays[array_num - 1][WRITE]);
	}
	else
	{
		if (fd[0] != 0)
			return ;
		dup2(str_pipe->fd_arrays[array_num - 1][READ], STDIN_FILENO);
		close(str_pipe->fd_arrays[array_num - 1][READ]);
		close(str_pipe->fd_arrays[0][WRITE]);
	}
}
