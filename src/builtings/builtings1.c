/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtings1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfuente- <mfuente-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 14:01:57 by mfuente-          #+#    #+#             */
/*   Updated: 2024/05/16 12:43:01 by mfuente-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../libft/libft.h"

void	ft_getpwd(char *text)
{
	char	*pwd;
	char	**split;

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
	return (open);
}

// IMITA LA FUNCION ECHO
// NOTA FALTA EL CLOSE AL FINAL DE LA FUNCION
void	ft_echo(char *text, t_ast *node)
{
	int		i;
	bool	open;
	bool	flag;
	char	delimiter;

	redirect_stdout(node);
	i = 4;
	open = false;
	flag = false;
	delimiter = '\0';
	i = ignore_space(text, i);
	i++;
	if (text[i] == '-' && text[i + 1] == 'n'
		&& text[i + 2] == ' ')
	{
		flag = true;
		i += 3;
	}
	open = ft_echo_normi(text, i, open, delimiter);
	if (open == true)
		printf("%c Syntax error\n", delimiter);
	if (flag == false)
		printf("\n");
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
