/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juestrel <juestrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:06:13 by juestrel          #+#    #+#             */
/*   Updated: 2024/05/23 16:07:26 by juestrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../libft/libft.h"

static void	segmention_path(t_lst_env **lst_env, t_pipex *str_pipes);
static char	*search_comand(t_pipex *str_pipes, char **comand);
static void	porcess_cmd(t_ast *node, t_lst_env **lst_env, t_pipex *str_pipe);

void	read_cmd(t_ast *node, t_pipex *str_pipe, char *prompt)
{
	if (ft_strncmp(node->args, "pwd\0", 4) == 0 || ft_strncmp(node->args,
			"pwd ", 4) == 0)
		ft_getpwd(node->args, node, str_pipe->fd);
	else if (ft_strncmp(node->args, "echo ", 4) == 0)
		ft_echo(node->args, node, str_pipe->fd);
	else if (ft_strncmp(node->args, "env\0", 4) == 0)
		ft_env(str_pipe->lst_env, node->args, node, str_pipe->fd);
	else if (ft_strncmp(node->args, "export ", 7) == 0)
	{
		ft_export(node->args, str_pipe->lst_env);
		free_copie_env(str_pipe->lst_env);
		up_env(str_pipe->lst_env);
	}
	else if (ft_strncmp(node->args, "unset ", 6) == 0)
	{
		ft_unset(node->args, str_pipe->lst_env);
		free_copie_env(str_pipe->lst_env);
		up_env(str_pipe->lst_env);
	}
	else if (ft_strncmp(node->args, "cd", 2) == 0)
		ft_cd(node->args, str_pipe->lst_env);
	else if (ft_strncmp(node->args, "exit", 4) == 0)
		ft_exit(&str_pipe->ast_head, *str_pipe->lst_env, prompt);
	else
		porcess_cmd(node, str_pipe->lst_env, str_pipe);
}

void	read_pipe(t_ast *node, t_lst_env **lst_env, t_pipex *str_pipe)
{
	if (str_pipe->fd[0] == '\0')
		pipe(str_pipe->fd);
	(void)node;
	(void)lst_env;
}

static void	porcess_cmd(t_ast *node, t_lst_env **lst_env, t_pipex *str_pipe)
{
	t_pipex	str_pipes;
	pid_t	pid;
	char	*dir_cmd;
	char	**command;
	int		fd;

	pid = fork();
	fd = redirect_stdout(node, str_pipe->fd);
	if (pid == CHILD)
	{
		command = ft_split(node->args, ' ');
		segmention_path(lst_env, &str_pipes);
		dir_cmd = search_comand(&str_pipes, command);
		if (execve(dir_cmd, command, (*lst_env)->env) == -1)
			exit(EXIT_FAILURE);
	}
	if (fd > 0)
		close(fd);
	dup2(0, STDOUT_FILENO);
	waitpid(pid, NULL, CHILD);
}

static void	segmention_path(t_lst_env **lst_env, t_pipex *str_pipes)
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

static char	*search_comand(t_pipex *str_pipes, char **comand)
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
