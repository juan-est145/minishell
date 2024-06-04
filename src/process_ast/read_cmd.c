/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-est145 <juan-est145@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:06:13 by juestrel          #+#    #+#             */
/*   Updated: 2024/06/04 11:21:32 by juan-est145      ###   ########.fr       */
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
		return (ft_getpwd(node->args, node, str_pipe, type_cmd));
	else if (ft_strncmp(node->args, "echo ", 4) == 0)
		return (ft_echo(node->args, node, str_pipe, type_cmd));
	else if (ft_strncmp(node->args, "env\0", 4) == 0)
		return (ft_env(str_pipe->lst_env, node, str_pipe, type_cmd));
	else if (ft_strncmp(node->args, "export ", 7) == 0)
		return (ft_export(node->args, str_pipe->lst_env, str_pipe, type_cmd));
	else if (ft_strncmp(node->args, "unset ", 6) == 0)
		return (ft_unset(node->args, str_pipe->lst_env, type_cmd));
	else if (ft_strncmp(node->args, "cd", 2) == 0)
		return (ft_cd(node->args, str_pipe->lst_env, type_cmd, str_pipe));
	else if (ft_strncmp(node->args, "exit", 4) == 0)
	{
		if (type_cmd == SIMPLE_CMD)
			free_fd_arrays(str_pipe->fd_arrays);
		return (ft_exit(&str_pipe->ast_head, *str_pipe->lst_env, prompt,
				type_cmd));
	}
	else
		return (process_cmd(node, str_pipe->lst_env, str_pipe, type_cmd));
}

void	read_pipe(t_ast *node, t_lst_env **lst_env, t_pipex *str_pipe,
		char *prompt)
{
	pid_t			pid1;
	pid_t			pid2;
	unsigned int	fd_position;

	(void)lst_env;
	pid1 = -1;
	pid2 = -1;
	open_pipes(str_pipe, node);
	fd_position = str_pipe->fd_array_num;
	if (node->left->simple_or_pipe == ENTRY_PIPE)
		pid1 = read_cmd(node->left, str_pipe, prompt, ENTRY_PIPE);
	if (node->left->parse_identifier == PARSE_CMD && node->right->simple_or_pipe == MIDDLE_PIPE)
		close(str_pipe->fd_arrays[fd_position - 2][WRITE]);
	if (node->right->simple_or_pipe == MIDDLE_PIPE)
		pid2 = read_cmd(node->right, str_pipe, prompt, MIDDLE_PIPE);
	else if (node->right->simple_or_pipe == EXIT_PIPE)
		pid2 = read_cmd(node->right, str_pipe, prompt, EXIT_PIPE);
	close_pipes(str_pipe, node);
	if (pid1 != -1)
		waitpid(pid1, NULL, 0);
	if (pid2 != -1)
		waitpid(pid2, NULL, 0);
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
		fd = redirect_stdout(node, str_pipe, cmd_type);
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
