/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfuente- <mfuente-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:06:13 by juestrel          #+#    #+#             */
/*   Updated: 2024/05/31 15:46:57 by mfuente-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../libft/libft.h"

static void		segmention_path(t_lst_env **lst_env, t_pipex *str_pipes);
static char		*search_comand(t_pipex *str_pipes, char **comand);
static pid_t	process_cmd(t_ast *node, t_lst_env **lst_env, t_pipex *str_pipe,
					t_process_cmd cmd_type);

pid_t	read_cmd(t_ast *node, t_pipex *str_pipe, char *prompt,
		t_process_cmd type_cmd)
{
	if (ft_strncmp(node->args, "pwd\0", 4) == 0 || ft_strncmp(node->args,
			"pwd ", 4) == 0)
		return (ft_getpwd(node->args, node, str_pipe->fd, type_cmd));
	else if (ft_strncmp(node->args, "echo ", 4) == 0)
		return (ft_echo(node->args, node, str_pipe->fd, type_cmd));
	else if (ft_strncmp(node->args, "env\0", 4) == 0)
		return (ft_env(str_pipe->lst_env, node, str_pipe->fd, type_cmd));
	else if (ft_strncmp(node->args, "export ", 7) == 0)
		return (ft_export(node->args, str_pipe->lst_env, str_pipe, type_cmd));
	else if (ft_strncmp(node->args, "unset ", 6) == 0)
		return (ft_unset(node->args, str_pipe->lst_env, type_cmd));
	else if (ft_strncmp(node->args, "cd", 2) == 0)
		return (ft_cd(node->args, str_pipe->lst_env, type_cmd, str_pipe));
	else if (ft_strncmp(node->args, "exit", 4) == 0)
		return (ft_exit(&str_pipe->ast_head, *str_pipe->lst_env, prompt,
				type_cmd));
	else
		return (process_cmd(node, str_pipe->lst_env, str_pipe, type_cmd));
}

void	read_pipe(t_ast *node, t_lst_env **lst_env, t_pipex *str_pipe,
		char *prompt)
{
	pid_t	pid1;
	pid_t	pid2;

	(void)lst_env;
	if (str_pipe->fd[READ] == 0 && str_pipe->fd[WRITE] == 0)
		pipe(str_pipe->fd);
	pid1 = read_cmd(node->left, str_pipe, prompt, ENTRY_PIPE);
	pid2 = read_cmd(node->right, str_pipe, prompt, EXIT_PIPE);
	close(str_pipe->fd[READ]);
	close(str_pipe->fd[WRITE]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	str_pipe->fd[READ] = 0;
	str_pipe->fd[WRITE] = 0;
}

static pid_t	process_cmd(t_ast *node, t_lst_env **lst_env, t_pipex *str_pipe,
		t_process_cmd cmd_type)
{
	t_pipex	str_pipes;
	pid_t	pid;
	char	*dir_cmd;
	char	**command;
	int		fd;

	pid = fork();
	fd = 0;
	if (pid == CHILD)
	{
		fd = redirect_stdout(node, str_pipe->fd, cmd_type);
		command = ft_split(node->args, ' ');
		segmention_path(lst_env, &str_pipes);
		dir_cmd = search_comand(&str_pipes, command);
		if (execve(dir_cmd, command, (*lst_env)->env) == -1)
			exit(EXIT_FAILURE);
	}
	if (cmd_type == SIMPLE_CMD)
		waitpid(pid, NULL, 0);
	if (fd > 0)
		close(fd);
	return (pid);
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
