/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   archive_utils4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-est145 <juan-est145@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 12:35:10 by juan-est145       #+#    #+#             */
/*   Updated: 2024/06/04 12:37:01 by juan-est145      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../libft/libft.h"

void	dup_fd_arrays(t_process_cmd type_cmd, t_pipex *str_pipe)
{
	unsigned int	array_num;

	array_num = str_pipe->fd_array_num;
	if (type_cmd == ENTRY_PIPE)
	{
		dup2(str_pipe->fd_arrays[0][WRITE], STDOUT_FILENO);
		close(str_pipe->fd_arrays[0][READ]);
	}
	else if (type_cmd == MIDDLE_PIPE)
	{
		dup2(str_pipe->fd_arrays[array_num - 2][READ], STDIN_FILENO);
		dup2(str_pipe->fd_arrays[array_num - 1][WRITE], STDOUT_FILENO);
		close(str_pipe->fd_arrays[array_num - 2][READ]);
		close(str_pipe->fd_arrays[array_num - 1][READ]);
		close(str_pipe->fd_arrays[array_num - 1][WRITE]);
	}
	else
	{
		dup2(str_pipe->fd_arrays[array_num - 1][READ], STDIN_FILENO);
		close(str_pipe->fd_arrays[array_num - 1][READ]);
		close(str_pipe->fd_arrays[0][WRITE]);
	}
}
