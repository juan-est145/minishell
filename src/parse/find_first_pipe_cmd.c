/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_first_pipe_cmd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juestrel <juestrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 16:24:57 by juestrel          #+#    #+#             */
/*   Updated: 2024/06/05 16:24:58 by juestrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../libft/libft.h"

static void	fill_fd_arrays(t_pipex *str_pipe, unsigned int limit,
				bool *mem_problems);
static void	fill_fd_arrays(t_pipex *str_pipe, unsigned int limit,
				bool *mem_problems);

void	find_first_pipe_cmd(t_ast *ast_node)
{
	if (ast_node->left->parse_identifier == PARSE_CMD)
		ast_node->left->simple_or_pipe = ENTRY_PIPE;
	else
		find_first_pipe_cmd(ast_node->left);
}

t_pipex	*create_fd_arrays(t_pipex *str_pipe, t_ast *head)
{
	unsigned int	i;
	bool			mem_problems;

	i = 0;
	mem_problems = false;
	while (head->parse_identifier == PARSE_PIPE)
	{
		head = head->left;
		i++;
	}
	str_pipe->fd_arrays = malloc(sizeof(int *) * (i + 1));
	if (str_pipe->fd_arrays == NULL)
		return (NULL);
	fill_fd_arrays(str_pipe, i, &mem_problems);
	if (mem_problems == true)
		return (NULL);
	return (str_pipe);
}

static void	fill_fd_arrays(t_pipex *str_pipe, unsigned int limit,
		bool *mem_problems)
{
	unsigned int	i;

	i = 0;
	while (i < limit)
	{
		str_pipe->fd_arrays[i] = malloc(sizeof(int) * 2);
		if (str_pipe->fd_arrays[i] == NULL)
		{
			*mem_problems = true;
			free_fd_arrays(str_pipe->fd_arrays);
			return ;
		}
		i++;
	}
	str_pipe->fd_arrays[i] = NULL;
}

void	free_fd_arrays(int **fd_arrays)
{
	int	i;

	i = 0;
	if (fd_arrays == NULL)
		return ;
	while (fd_arrays[i] != NULL)
	{
		free(fd_arrays[i]);
		i++;
	}
	free(fd_arrays);
}
