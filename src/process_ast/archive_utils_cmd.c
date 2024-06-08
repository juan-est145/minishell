/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   archive_utils_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juestrel <juestrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 09:50:35 by mfuente-          #+#    #+#             */
/*   Updated: 2024/06/08 18:20:50 by juestrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../libft/libft.h"

void	up_env(t_lst_env **lst_env)
{
	int			i;
	char		**copied_env;
	t_lst_env	*temp;

	i = 0;
	temp = *lst_env;
	copied_env = malloc(sizeof(char *) * (ft_lstsize_ms(temp) + 1));
	if (!copied_env)
		return ;
	while (temp)
	{
		copied_env[i++] = ft_substr(temp->text, 0, ft_strlen(temp->text));
		temp = temp->next;
	}
	copied_env[i] = NULL;
	temp = *lst_env;
	while (temp != NULL)
	{
		temp->env = copied_env;
		temp = temp->next;
	}
}

char	*create_path(t_pipex *str_pipes, char **comand, int i)
{
	char	*dir_cmd;
	char	*aux;

	dir_cmd = ft_strjoin(str_pipes->path_seg[i], "/");
	aux = dir_cmd;
	dir_cmd = ft_strjoin(dir_cmd, comand[0]);
	free(aux);
	return (dir_cmd);
}

void	free_copie_env(t_lst_env **lst)
{
	t_lst_env	*temp;

	temp = *lst;
	if (temp != NULL)
		free_matrix(temp->env);
}

void	cleanup(t_pipex *str_pipe)
{
	clean_ast(str_pipe->ast_head);
	str_pipe->fd_array_num = 0;
	free_fd_arrays(str_pipe->fd_arrays);
	str_pipe->fd_arrays = NULL;
}

void	process_cmd_fork_failure(t_lst_env **lst_env, t_pipex *str_pipe)
{
	printf("Error creating child process, exiting\n");
	free_lst_env(*lst_env);
	clean_ast(str_pipe->ast_head);
	exit(EXIT_FAILURE);
}
