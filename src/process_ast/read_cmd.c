/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfuente- <mfuente-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:06:13 by juestrel          #+#    #+#             */
/*   Updated: 2024/06/08 18:47:38 by mfuente-         ###   ########.fr       */
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
	else if (ft_strncmp(node->args, "export", 6) == 0)
		return (ft_export(node, str_pipe->lst_env, str_pipe, type_cmd));
	else if (ft_strncmp(node->args, "unset ", 6) == 0)
		return (ft_unset(node->args, str_pipe->lst_env, type_cmd));
	else if (ft_strncmp(node->args, "cd", 2) == 0)
		return (ft_cd(node, str_pipe->lst_env, type_cmd, str_pipe));
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

void	read_pipe(t_ast *node, t_pipex *str_pipe, char *prompt)
{
	pid_t			pid1;
	pid_t			pid2;
	unsigned int	fd_position;

	pid1 = -1;
	pid2 = -1;
	open_pipes(str_pipe, node);
	fd_position = str_pipe->fd_array_num;
	if (node->left->simple_or_pipe == ENTRY_PIPE)
		pid1 = read_cmd(node->left, str_pipe, prompt, ENTRY_PIPE);
	if (node->left->parse_identifier == PARSE_CMD
		&& node->right->simple_or_pipe == MIDDLE_PIPE)
		close(str_pipe->fd_arrays[fd_position - 2][WRITE]);
	if (node->right->simple_or_pipe == MIDDLE_PIPE)
		pid2 = read_cmd(node->right, str_pipe, prompt, MIDDLE_PIPE);
	else if (node->right->simple_or_pipe == EXIT_PIPE)
		pid2 = read_cmd(node->right, str_pipe, prompt, EXIT_PIPE);
	close_pipes(str_pipe, node);
	if (pid1 != -1)
		wait_pid_return_status(pid1, str_pipe);
	if (pid2 != -1)
		wait_pid_return_status(pid2, str_pipe);
}

static pid_t	process_cmd(t_ast *node, t_lst_env **lst_env, t_pipex *str_pipe,
		t_process_cmd cmd_type)
{
	pid_t	pid;
	char	*dir_cmd;
	char	**command;
	int		fd;

	pid = fork();
	if (pid == -1)
		process_cmd_fork_failure(lst_env, str_pipe);
	fd = 0;
	if (pid == CHILD)
	{
		fd = redirect_stdout(node, str_pipe, cmd_type);
		command = ft_split(node->args, ' ');
		segmention_path(lst_env, str_pipe);
		dir_cmd = search_comand(str_pipe, command);
		if (execve(dir_cmd, command, (*lst_env)->env) == -1)
		{
			printf("Command %s not found\n", command[0]);
			exit(EXIT_FAILURE);
		}
	}
	(void)fd;
	if (cmd_type == SIMPLE_CMD)
		wait_pid_return_status(pid, str_pipe);
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
	char	*aux;

	i = 0;
	if (comand != NULL && comand[0] == NULL)
		exit(0);
	aux = ft_strrchr(comand[0], '/');
	if (aux != NULL && aux[1] != '\0')
		comand[0] = aux + 1;
	dir_cmd = create_path(str_pipes, comand, i);
	while (str_pipes->path_seg[i] != 0)
	{
		if (access(dir_cmd, F_OK) != -1)
			return (dir_cmd);
		i++;
		free(dir_cmd);
		if (str_pipes->path_seg[i] != 0)
			dir_cmd = create_path(str_pipes, comand, i);
		else
			dir_cmd = NULL;
	}
	return (dir_cmd);
}
