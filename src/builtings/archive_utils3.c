/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   archive_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfuente- <mfuente-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 10:27:27 by mfuente-          #+#    #+#             */
/*   Updated: 2024/05/30 12:11:50 by mfuente-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../libft/libft.h"

static int	redirect_stdout_output(t_ast *node, int fd);
static int	redirect_stdout_input(t_ast *node, int fd);

int	redirect_stdout(t_ast *node, int fd_pipe[2], t_process_cmd type_cmd)
{
	int	fd;

	fd = 0;
	fd = redirect_stdout_input(node, fd);
	fd = redirect_stdout_output(node, fd);
	if (fd != 0 || type_cmd == SIMPLE_CMD)
		return (fd);
	if (type_cmd == ENTRY_PIPE)
		dup2(fd_pipe[WRITE], STDOUT_FILENO);
	else
		dup2(fd_pipe[READ], STDIN_FILENO);
	close(fd_pipe[WRITE]);
	close(fd_pipe[READ]);
	return (fd);
}

static int	redirect_stdout_output(t_ast *node, int fd)
{
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
	return (0);
}

static int	redirect_stdout_input(t_ast *node, int fd)
{
	if ((node->redirections != NULL)
		&& (node->redirections->redirection_type == REDIR_TERMINAL_LINES))
	{
		fd = here_doc(node->redirections->file_location);
		dup2(fd, STDIN_FILENO);
		return (0);
	}
	if ((node->redirections != NULL)
		&& (node->redirections->redirection_type == REDIR_INPUT))
	{
		fd = open(node->redirections->file_location, O_RDONLY, 0777);
		if (fd == -1)
		{
			printf("ERROR en la redireccion del archivo\n");
			return (-1);
		}
		dup2(fd, STDIN_FILENO);
		return (0);
	}
	return (0);
}

static int	ft_strstr(char *limit, char *escrito)
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

int	here_doc(char *limit)
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