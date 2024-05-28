/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtings1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfuente- <mfuente-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 14:01:57 by mfuente-          #+#    #+#             */
/*   Updated: 2024/05/28 18:59:22 by mfuente-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../libft/libft.h"

void	ft_getpwd(char *text, t_ast *node, int fd_pipe[2])
{
	char	*pwd;
	char	**split;
	int		fd;

	fd = redirect_stdout(node, fd_pipe);
	split = ft_split(text, ' ');
	if (split[1] != NULL)
	{
		printf("Too many arguments with PWD command\n");
		free_matrix(split);
		return ;
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
void	ft_echo(char *text, t_ast *node, int fd_pipe[2])
{
	int		i;
	bool	open;
	bool	flag;
	char	delimiter;
	int		fd;

	fd = redirect_stdout(node, fd_pipe);
	i = 4;
	open = false;
	flag = false;
	delimiter = '\0';
	i = ignore_space(text, i) + 1;
	if (text[i] == '-' && text[i + 1] == 'n'
		&& text[i + 2] == ' ')
	{
		flag = true;
		i += 3;
	}
	open = ft_echo_normi(text, i, open, delimiter);
	if (flag == false)
		printf("\n");
	if (fd > 0)
		close(fd);
	dup2(0, STDOUT_FILENO);
}

// IMITA EL COMANDO CD
void	ft_cd(char *text, t_lst_env **lst_env)
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
			cd_no_argument(old_pwd, split, lst_env);
		else
		{
			if (errors_cd(old_pwd, split, split,
					"Could not access directory") == 1)
				return ;
			pwd = getcwd(NULL, 0);
			handle_cd_env(lst_env, ft_fusion_string, "export PWD=", pwd);
		}
		handle_cd_env(lst_env, ft_fusion_string, "export OLDPWD=", old_pwd);
	}
	free_matrix(split);
}

void	ft_exit(t_ast **head, t_lst_env *lst_env, char *prompt)
{
	clean_ast(*head);
	rl_clear_history();
	free_copie_env(&lst_env);
	free_lst_env(lst_env);
	free(prompt);
	exit(0);
}
