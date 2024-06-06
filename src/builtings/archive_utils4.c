/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   archive_utils4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juestrel <juestrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 16:24:16 by juestrel          #+#    #+#             */
/*   Updated: 2024/06/06 12:24:13 by juestrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../libft/libft.h"

static void	print_echo_hd(char *buffer, char limit, int fd[2], int i);
static void	middle_pipe(t_pipex *str_pipe, int array_num, int fd[2]);

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
		middle_pipe(str_pipe, array_num, fd);
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

static int	ft_contein(char limit, char *escrito)
{
	int	i;
	int	continuar;

	i = 0;
	continuar = 1;
	while (i < (int)ft_strlen(escrito))
	{
		if (limit == escrito[i])
			continuar = 0;
		i++;
	}
	return (continuar);
}

int	here_doc_echo(char limit)
{
	bool	continuar;
	char	*buffer;
	int		fd[2];

	pipe(fd);
	continuar = true;
	while (continuar == true)
	{
		ft_putstr_fd("> ", 1);
		buffer = get_next_line(0);
		if (ft_contein(limit, buffer) == 0)
		{
			print_echo_hd(buffer, limit, fd, 0);
			free(buffer);
			continuar = false;
		}
		else
		{
			write(fd[WRITE], buffer, ft_strlen(buffer));
			free(buffer);
		}
	}
	close(fd[WRITE]);
	return (fd[READ]);
}

static void	print_echo_hd(char *buffer, char limit, int fd[2], int i)
{
	while (buffer[i] != '\0')
	{
		if (limit != buffer[i])
			if ('\n' != buffer[i])
				write(fd[WRITE], &buffer[i], 1);
		i++;
	}
}

static void	middle_pipe(t_pipex *str_pipe, int array_num, int fd[2])
{
	if (fd[0] <= 0)
		dup2(str_pipe->fd_arrays[array_num - 2][READ], STDIN_FILENO);
	if (fd[1] <= 0)
		dup2(str_pipe->fd_arrays[array_num - 1][WRITE], STDOUT_FILENO);
	close(str_pipe->fd_arrays[array_num - 2][READ]);
	close(str_pipe->fd_arrays[array_num - 1][READ]);
	close(str_pipe->fd_arrays[array_num - 1][WRITE]);
}
