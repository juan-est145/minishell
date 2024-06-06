/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtings_child_process.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfuente- <mfuente-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 17:50:30 by juestrel          #+#    #+#             */
/*   Updated: 2024/06/06 10:51:52 by mfuente-         ###   ########.fr       */
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
	if (flag == false )
		printf("\n");
	if (fd > 0)
		close(fd);
	exit(0);
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
		printf("Error obtaining PWD\n");
	printf("%s\n", pwd);
	free(pwd);
	if (fd > 0)
	{
		close(fd);
		dup2(0, STDOUT_FILENO);
	}
	free_matrix(split);
	exit(0);
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
	exit(0);
}

void	cd_process(char *text, t_lst_env **lst_env, t_pipex *str_pipes)
{
	char	**split;
	char	*old_pwd;
	char	*pwd;

	split = ft_split(text, ' ');
	if (check_array_length(split) >= 3)
		printf("Too many arguments in cd\n");
	else
	{
		old_pwd = getcwd(NULL, 0);
		if (split[1] == NULL)
			cd_no_argument(old_pwd, split, lst_env, str_pipes);
		else
		{
			if (errors_cd(old_pwd, split, split,
					"Could not access directory") == 1)
				exit(EXIT_FAILURE);
			pwd = getcwd(NULL, 0);
			handle_cd_env(lst_env, "PIPES", pwd, str_pipes);
		}
		handle_cd_env(lst_env, "PIPES", old_pwd, str_pipes);
	}
	free_matrix(split);
	exit(0);
}

void	cd_parent_process(char *text, t_lst_env **lst_env, t_pipex *str_pipes)
{
	char	**split;
	char	*old_pwd;
	char	*pwd;

	split = ft_split(text, ' ');
	if (check_array_length(split) >= 3)
		printf("Too many arguments in cd\n");
	else
	{
		old_pwd = getcwd(NULL, 0);
		if (split[1] == NULL)
			cd_no_argument(old_pwd, split, lst_env, str_pipes);
		else
		{
			if (errors_cd(old_pwd, split, split,
					"Could not access directory") == 1)
				return ;
			pwd = getcwd(NULL, 0);
			handle_cd_env(lst_env, "export PWD=", pwd, str_pipes);
		}
		handle_cd_env(lst_env, "export OLDPWD=", old_pwd, str_pipes);
	}
	free_matrix(split);
}
