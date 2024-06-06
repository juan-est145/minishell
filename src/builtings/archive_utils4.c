/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   archive_utils4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfuente- <mfuente-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 12:35:10 by juan-est145       #+#    #+#             */
/*   Updated: 2024/06/06 10:51:25 by mfuente-         ###   ########.fr       */
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
		if (fd[0] <= 0)
		{
			dup2(str_pipe->fd_arrays[array_num - 2][READ], STDIN_FILENO);
			//ft_putstr_fd("ENTRA EN EL ERROR 1\n", 2);
		}
		if (fd[1] <= 0)
		{
			dup2(str_pipe->fd_arrays[array_num - 1][WRITE], STDOUT_FILENO);
			//ft_putstr_fd("ENTRA EN EL ERROR 2\n", 2);
		}
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
	int		i;

	pipe(fd);
	continuar = true;
	while (continuar == true)
	{
		ft_putstr_fd("> ", 1);
		buffer = get_next_line(0);
		if (ft_contein(limit, buffer) == 0)
		{
			i = 0;
			while (buffer[i] != '\0')
			{
				if (limit != buffer[i])
					if ('\n' != buffer[i])
						write(fd[WRITE], &buffer[i], 1);
				i++;
			}
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
//	char *prueba = read_all(fd[READ]);
//	(void)prueba;
	return (fd[READ]);
}

/* static char *read_all(int fd) {
    char buffer[4096];
    char *content = NULL;
    ssize_t bytes_read;
    size_t total_size = 0;

    while ((bytes_read = read(fd, buffer, sizeof(buffer) - 1)) > 0) {
        buffer[bytes_read] = '\0';
        content = realloc(content, total_size + bytes_read + 1);
        if (!content) {
            return NULL; // realloc failed
        }
        memcpy(content + total_size, buffer, bytes_read + 1);
        total_size += bytes_read;
    }

    if (bytes_read < 0) {
        free(content);
        return NULL; // read failed
    }

    return content;
} */
