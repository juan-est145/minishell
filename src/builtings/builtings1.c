/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtings1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfuente- <mfuente-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 14:01:57 by mfuente-          #+#    #+#             */
/*   Updated: 2024/05/30 16:59:24 by mfuente-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../libft/libft.h"

pid_t	ft_getpwd(char *text, t_ast *node, int fd_pipe[2],
		t_process_cmd type_cmd)
{
	char	*pwd;
	char	**split;
	int		fd;
	pid_t	pid;

	pid = fork();
	if (pid == CHILD)
	{
		fd = redirect_stdout(node, fd_pipe, type_cmd);
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
	return(pid);
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
pid_t	ft_echo(char *text, t_ast *node, int fd_pipe[2], t_process_cmd type_cmd)
{
	int		i;
	bool	open;
	bool	flag;
	char	delimiter;
	int		fd;
	pid_t	pid;

	pid = fork();
	if (pid == CHILD)
	{
		fd = redirect_stdout(node, fd_pipe, type_cmd);
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
		exit(0);
	}
	// dup2(0, STDOUT_FILENO);
	return (pid);
}

// IMITA EL COMANDO CD
pid_t	ft_cd(char *text, t_lst_env **lst_env)
{
	char	**split;
	char	*old_pwd;
	char	*pwd;
	pid_t	pid;

	pid = fork();
	// TO DO: CHECK IF IT WORKS WITH PIPES
	if (pid == CHILD)
	{
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
					exit(EXIT_FAILURE);
				pwd = getcwd(NULL, 0);
				handle_cd_env(lst_env, ft_fusion_string, "export PWD=", pwd);
			}
			handle_cd_env(lst_env, ft_fusion_string, "export OLDPWD=", old_pwd);
		}
		free_matrix(split);
		exit(0);
	}
	return(pid);
}

void	ft_exit(t_ast **head, t_lst_env *lst_env, char *prompt)
{
	//TO DO, CHECK WHAT HAPPENS WITH PIPES AND THIS CMD
	clean_ast(*head);
	rl_clear_history();
	free_copie_env(&lst_env);
	free_lst_env(lst_env);
	free(prompt);
	exit(0);
}
