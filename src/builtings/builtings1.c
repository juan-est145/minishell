/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtings1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-est145 <juan-est145@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 14:01:57 by mfuente-          #+#    #+#             */
/*   Updated: 2024/06/05 11:30:23 by juan-est145      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../libft/libft.h"

pid_t	ft_getpwd(char *text, t_ast *node, t_pipex *str_pipe,
		t_process_cmd type_cmd)
{
	pid_t	pid;

	pid = fork();
	if (pid == CHILD)
		pwd_process(text, node, str_pipe, type_cmd);
	if (type_cmd == SIMPLE_CMD)
		wait_pid_return_status(pid, str_pipe);
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
pid_t	ft_echo(char *text, t_ast *node, t_pipex *str_pipe,
		t_process_cmd type_cmd)
{
	pid_t	pid;

	pid = fork();
	if (pid == CHILD)
		echo_process(text, node, str_pipe, type_cmd);
	if (type_cmd == SIMPLE_CMD)
		wait_pid_return_status(pid, str_pipe);
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
