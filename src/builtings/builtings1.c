/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtings1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfuente- <mfuente-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 14:01:57 by mfuente-          #+#    #+#             */
/*   Updated: 2024/05/31 13:21:17 by mfuente-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../libft/libft.h"

pid_t	ft_getpwd(char *text, t_ast *node, int fd_pipe[2],
		t_process_cmd type_cmd)
{
	pid_t	pid;

	pid = fork();
	if (pid == CHILD)
		pwd_process(text, node, fd_pipe, type_cmd);
	return (pid);
}

bool	ft_echo_normi(char *text, int i, bool open, char delimiter)
{
	while (text[i] != '\0')
	{
		if (open == false)
			i = ignore_space(text, i);
		if ((text[i] == '\"' || text[i] == '\'') && open == false)
		{
			open = true;
			delimiter = text[i];
			i++;
			continue ;
		}
		if (text[i] == delimiter && open == true)
		{
			open = false;
			delimiter = '\0';
			i++;
			continue ;
		}
		printf("%c", text[i]);
		i++;
	}
	if (open == true)
		printf("Syntax error\n");
	return (open);
}

// IMITA LA FUNCION ECHO
pid_t	ft_echo(char *text, t_ast *node, int fd_pipe[2], t_process_cmd type_cmd)
{
	pid_t	pid;

	pid = fork();
	if (pid == CHILD)
		echo_process(text, node, fd_pipe, type_cmd);
	return (pid);
}

// IMITA EL COMANDO CD
pid_t	ft_cd(char *text, t_lst_env **lst_env, t_process_cmd type_cmd,
		t_pipex *str_pipes)
{
	pid_t	pid;

	pid = -1;
	if (type_cmd == SIMPLE_CMD)
	{
		cd_parent_process(text, lst_env, str_pipes);
		return (pid);
	}
	pid = fork();
	if (pid == CHILD)
		cd_process(text, lst_env, str_pipes);
	return (pid);
}

pid_t	ft_exit(t_ast **head, t_lst_env *lst_env, char *prompt,
		t_process_cmd type_cmd)
{
	pid_t	pid;

	pid = -1;
	if (type_cmd == SIMPLE_CMD)
	{
		exit_process(head, lst_env, prompt);
		return (pid);
	}
	pid = fork();
	if (pid == CHILD)
		exit_process(head, lst_env, prompt);
	return (pid);
}
