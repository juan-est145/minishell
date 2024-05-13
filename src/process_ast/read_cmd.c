/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfuente- <mfuente-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 11:57:33 by juan-est145       #+#    #+#             */
/*   Updated: 2024/05/13 18:32:02 by mfuente-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../libft/libft.h"

void	segmention_path(t_lst_env **lst_env, t_pipex *str_pipes);
char	*search_comand(t_pipex *str_pipes, char **comand);
void	porcess_cmd(t_ast *node, t_lst_env **lst_env);

void	read_cmd(t_ast *node, t_lst_env **lst_env, t_ast **head, char *prompt)
{
	if (ft_strncmp(node->args, "pwd\0", 4) == 0 || ft_strncmp(node->args,
			"pwd ", 4) == 0)
		ft_getpwd(node->args);
	else if (ft_strncmp(node->args, "echo ", 4) == 0)
		ft_echo(node->args);
	else if (ft_strncmp(node->args, "env\0", 4) == 0)
		ft_env(lst_env, node->args);
	else if (ft_strncmp(node->args, "export ", 7) == 0)
	{
		ft_export(node->args, lst_env);
		free_copie_env(lst_env);
		up_env(lst_env);
	}
	else if (ft_strncmp(node->args, "unset ", 6) == 0)
	{
		ft_unset(node->args, lst_env);
		free_copie_env(lst_env);
		up_env(lst_env);
	}
	else if (ft_strncmp(node->args, "cd", 2) == 0)
		ft_cd(node->args, lst_env);
	else if (ft_strncmp(node->args, "exit", 4) == 0)
		ft_exit(head, *lst_env, prompt);
	else
		porcess_cmd(node, lst_env);
}

void	porcess_cmd(t_ast *node, t_lst_env **lst_env)
{
	t_pipex	str_pipes;
	pid_t	pid;
	char	*dir_cmd;
	char	**command;

	pid = fork();
	if (pid == CHILD)
	{
		command = ft_split(node->args, ' ');
		segmention_path(lst_env, &str_pipes);
		dir_cmd = search_comand(&str_pipes, command);
		if (execve(dir_cmd, command, (*lst_env)->env) == -1)
			exit(EXIT_FAILURE);
	}
	waitpid(pid, NULL, CHILD);
}

void	segmention_path(t_lst_env **lst_env, t_pipex *str_pipes)
{
	t_lst_env	*temp;

	temp = *lst_env;
	while (temp != NULL)
	{
		if (ft_strncmp(temp->text, "PATH=", 5) == 0)
			str_pipes->path_seg = ft_split((temp->text + 5), ':');
		temp = temp->next;
	}
}

char	*search_comand(t_pipex *str_pipes, char **comand)
{
	int		i;
	char	*dir_cmd;

	i = 0;
	dir_cmd = create_path(str_pipes, comand, i);
	while (str_pipes->path_seg[i] != 0)
	{
		if (access(dir_cmd, F_OK) != -1)
			return (dir_cmd);
		i++;
		free(dir_cmd);
		if (str_pipes->path_seg[i] != 0)
		{
			dir_cmd = create_path(str_pipes, comand, i);
		}
		else
			dir_cmd = NULL;
	}
	return (dir_cmd);
}

void	read_pipe(t_ast *node, t_lst_env **lst_env)
{
	(void)node;
	(void)lst_env;
}
