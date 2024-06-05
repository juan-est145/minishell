/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtings1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfuente- <mfuente-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 14:01:57 by mfuente-          #+#    #+#             */
/*   Updated: 2024/06/05 19:27:32 by mfuente-         ###   ########.fr       */
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
		waitpid(pid, NULL, 0);
	return (pid);
}

bool	ft_echo_normi(char *text, int i, bool open, char delimiter)
{
	int		fd;
	char	line[1];

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
	{
		fd = here_doc_echo(delimiter);
		printf("\n");
		/* line = get_next_line(fd);
		while (line != NULL)
		{
			printf("%s", line);
			free(line);
			line = get_next_line(fd);
		}
		free(line); */
		
		while (read(fd, line, 1) > 0)
		{
			//printf("%s", line);
			write(1, line, 1);
			//free(line);
			//read(fd, line, 1);
		}
		
		close(fd);
	}
	//	printf("Syntax error\n");
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
		waitpid(pid, NULL, 0);
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
