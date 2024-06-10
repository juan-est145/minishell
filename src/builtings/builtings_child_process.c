/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtings_child_process.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juestrel <juestrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 17:50:30 by juestrel          #+#    #+#             */
/*   Updated: 2024/06/10 16:00:14 by juestrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../libft/libft.h"

void	echo_process(char *text, t_ast *node, t_pipex *str_pipe,
		t_process_cmd type_cmd)
{
	int		i;
	bool	open;
	bool	flag;
	char	delimiter;
	int		fd;

	fd = redirect_stdout(node, str_pipe, type_cmd);
	i = 4;
	open = false;
	flag = false;
	delimiter = '\0';
	i = ignore_space(text, i) + 1;
	if (text[i] == '-' && text[i + 1] == 'n' && text[i + 2] == ' ')
	{
		flag = true;
		i += 3;
	}
	open = ft_echo_normi(text, i, open, delimiter);
	if (flag == false)
		printf("\n");
	if (fd > 0)
		close(fd);
	exit(EXIT_SUCCESS);
}

void	pwd_process(char *text, t_ast *node, t_pipex *str_pipe,
		t_process_cmd type_cmd)
{
	char	*pwd;
	char	**split;
	int		fd;

	fd = redirect_stdout(node, str_pipe, type_cmd);
	split = ft_split(text, ' ');
	if (split[1] != NULL)
	{
		printf("Too many arguments with PWD command\n");
		free_matrix(split);
		exit(EXIT_FAILURE);
	}
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		error_msgs(PWD_ERROR);
	printf("%s\n", pwd);
	free(pwd);
	if (fd > 0)
	{
		close(fd);
		dup2(0, STDOUT_FILENO);
	}
	free_matrix(split);
	exit(EXIT_SUCCESS);
}

void	env_process(t_lst_env **lst_env, t_ast *node, t_pipex *str_pipe,
		t_process_cmd cmd_type)
{
	char		**split;
	t_lst_env	*temp;
	int			fd;

	fd = redirect_stdout(node, str_pipe, cmd_type);
	temp = *lst_env;
	split = ft_split(node->args, ' ');
	if (split[1] != NULL)
	{
		free_matrix(split);
		printf("Too many arguments\n");
		exit(EXIT_FAILURE);
	}
	while (temp != NULL)
	{
		printf("%s\n", temp->text);
		temp = temp->next;
	}
	if (fd > 0)
		close(fd);
	free_matrix(split);
	exit(EXIT_SUCCESS);
}

void	cd_process(t_ast *node, t_lst_env **lst_env, t_pipex *str_pipes)
{
	t_str_aux	aux;

	aux = init_str_aux();
	aux.split = ft_split(node->args, ' ');
	if (check_array_length(aux.split) >= 3)
		cd_process_args_error(aux.split);
	aux.old_pwd = getcwd(NULL, 0);
	if (aux.split[1] == NULL)
		cd_no_argument(node, aux, lst_env, str_pipes);
	else
	{
		if (errors_cd(aux.old_pwd, aux.split, aux.split,
				"Could not access directory") == 1)
			exit(EXIT_FAILURE);
		aux.pwd = getcwd(NULL, 0);
		handle_cd_env(lst_env, "PIPES", str_pipes, node);
	}
	handle_cd_env(lst_env, "PIPES", str_pipes, node);
	free_matrix(aux.split);
	exit(EXIT_SUCCESS);
}

int	cd_parent_process(t_ast *node, t_lst_env **lst_env, t_pipex *str_pipes)
{
	char		*fusion;
	t_str_aux	aux;

	aux = init_str_aux();
	aux.split = ft_split(node->args, ' ');
	if (check_array_length(aux.split) >= 3)
		return (cd_too_many_arguments(aux.split, str_pipes));
	aux.old_pwd = getcwd(NULL, 0);
	if (aux.split[1] == NULL)
		return (cd_no_argument(node, aux, lst_env, str_pipes));
	if (errors_cd(aux.old_pwd, aux.split, aux.split,
			"Could not access directory") == 1)
	{
		str_pipes->return_cmd_status = 1;
		return (1);
	}
	aux.pwd = getcwd(NULL, 0);
	if (aux.pwd == NULL && errno == ENOMEM)
		error_msgs(PWD_ERROR);
	else if (aux.pwd == NULL)
		return (free_matrix(aux.split), old_pwd_failure(str_pipes));
	fusion = update_env_cd_parent(aux, lst_env, str_pipes, node);
	cd_parent_cleanup(fusion, &aux);
	return (0);
}
