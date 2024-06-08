/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   archive_utils5.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfuente- <mfuente-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 12:02:46 by mfuente-          #+#    #+#             */
/*   Updated: 2024/06/08 12:18:18 by mfuente-         ###   ########.fr       */
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

void	pwd_null_error(void)
{
	printf("Error obtaining PWD\n");
	exit(EXIT_FAILURE);
}

bool	is_num(char **split, bool flag)
{
	int	i;

	i = 0;
	while (split[1][i] != '\0')
	{
		if (ft_isdigit(split[1][i]) == 0)
			flag = false;
		i++;
	}
	return (flag);
}
