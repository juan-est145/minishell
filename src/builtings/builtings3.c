/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtings3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juestrel <juestrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 17:50:30 by juestrel          #+#    #+#             */
/*   Updated: 2024/05/30 17:58:50 by juestrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../libft/libft.h"

void	echo_process(char *text, t_ast *node, int fd_pipe[2],
		t_process_cmd type_cmd)
{
	int		i;
	bool	open;
	bool	flag;
	char	delimiter;
	int		fd;

	fd = redirect_stdout(node, fd_pipe, type_cmd);
	i = 4;
	open = false;
	flag = false;
	delimiter = '\0';
	i = ignore_space(text, i) + 1;
	if (text[i] == '-' && text[i + 1] == 'n' && text[i + 2] == ' ')
	{
		flag = true;
		i += 3;
	}
	open = ft_echo_normi(text, i, open, delimiter);
	if (flag == false)
		printf("\n");
	if (fd > 0)
		close(fd);
	exit(0);
}
