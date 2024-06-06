/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_pipes_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juestrel <juestrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 17:35:14 by juestrel          #+#    #+#             */
/*   Updated: 2024/06/05 16:25:14 by juestrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../libft/libft.h"

void	open_pipes(t_pipex *str_pipe, t_ast *node)
{
	unsigned int	array_index;

	array_index = str_pipe->fd_array_num;
	if (node->left->parse_identifier == PARSE_CMD
		|| node->right->simple_or_pipe == MIDDLE_PIPE)
	{
		pipe(str_pipe->fd_arrays[array_index]);
		str_pipe->fd_array_num++;
		array_index = str_pipe->fd_array_num;
	}
	if ((node->left->parse_identifier == PARSE_CMD
			&& node->right->parse_identifier == PARSE_CMD)
		&& node->right->simple_or_pipe != EXIT_PIPE)
	{
		pipe(str_pipe->fd_arrays[array_index]);
		str_pipe->fd_array_num++;
	}
}

void	close_pipes(t_pipex *str_pipe, t_ast *node)
{
	unsigned int	array_index;

	array_index = str_pipe->fd_array_num;
	if ((node->left->simple_or_pipe == ENTRY_PIPE
			&& node->right->simple_or_pipe != EXIT_PIPE)
		|| node->right->simple_or_pipe == MIDDLE_PIPE)
	{
		close(str_pipe->fd_arrays[array_index - 2][READ]);
		close(str_pipe->fd_arrays[array_index - 1][WRITE]);
	}
	else if (node->right->simple_or_pipe == EXIT_PIPE
		&& node->left->parse_identifier == PARSE_PIPE)
		close(str_pipe->fd_arrays[array_index - 1][READ]);
	else
	{
		close(str_pipe->fd_arrays[0][READ]);
		close(str_pipe->fd_arrays[0][WRITE]);
	}
}

void	wait_pid_return_status(pid_t pid, t_pipex *str_pipe)
{
	int	status;

	status = 0;
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		str_pipe->return_cmd_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		str_pipe->return_cmd_status = WTERMSIG(status);
	else
		str_pipe->return_cmd_status = -1;
}
