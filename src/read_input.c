/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juestrel <juestrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 16:20:41 by mfuente-          #+#    #+#             */
/*   Updated: 2024/06/05 16:23:54 by juestrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"

char	*read_input(char *prompt, t_lst_env **lst_env)
{
	char	*text;

	text = readline(prompt);
	if (text == NULL)
	{
		free(prompt);
		free_copie_env(lst_env);
		free_lst_env(*lst_env);
		exit(0);
	}
	add_history(text);
	return (text);
}

t_pipex	init_str_pipe(t_lst_env **lst_env)
{
	t_pipex	str_pipe;

	str_pipe.lst_env = lst_env;
	str_pipe.fd_arrays = NULL;
	str_pipe.fd_array_num = 0;
	str_pipe.return_cmd_status = 0;
	return (str_pipe);
}
