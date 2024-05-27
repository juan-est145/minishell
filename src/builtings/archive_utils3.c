/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   archive_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfuente- <mfuente-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 10:27:27 by mfuente-          #+#    #+#             */
/*   Updated: 2024/05/27 10:44:12 by mfuente-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../libft/libft.h"

int	redirect_stdout(t_ast *node, int fd_pipe[2])
{
	int	fd;

	fd = 0;
	if (node->redirections->redirection_type == REDIR_TERMINAL_LINES)
	{
		fd = here_doc(node->redirections->file_location);
		dup2(fd, STDIN_FILENO);
		return (0);
	}
	if (node->redirections != NULL && fd == 0)
	{
			if (redirected_destination(&node->redirections) == -1)
			{
				printf("ERROR en la redireccion del archivo\n");
				return (-1);
			}
			fd = redirected_destination(&node->redirections);
			dup2(fd, STDOUT_FILENO);
			return (fd);
	}
	if (fd_pipe[0] == READ && fd_pipe[1] == WRITE)
	{
		dup2(fd_pipe[WRITE], STDOUT_FILENO);
		dup2(fd_pipe[READ], STDIN_FILENO);
	}
	return (fd);
}

static int	ft_strstr(char	*limit, char *escrito)
{
	int	i;

	i = 0;
	while (i < (int)ft_strlen(limit))
	{
		if (limit[i] != escrito[i])
			return (1);
		i++;
	}
	return (0);
}
//PARA EL ECHO CREO QUE NO FUNCIONARIA
int	here_doc(char	*limit)
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
		if (ft_strstr(limit, buffer) == 0)
		{
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
