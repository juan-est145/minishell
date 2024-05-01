/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtings1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfuente- <mfuente-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 14:01:57 by mfuente-          #+#    #+#             */
/*   Updated: 2024/05/01 13:16:58 by mfuente-         ###   ########.fr       */
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
		printf("too many arguments\n");
		return ;
	}
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		printf("Error al obtener el pwd\n");
	printf("%s\n", pwd);
	free(pwd);
	free_matrix(split);
}

bool	ft_echo_normi(char **cmd, int i, int j, bool open)
{
	static char	chr = '\0';

	if ((cmd[i][j] == '\"' || cmd[i][j] == '\'') && open == false)
	{
		open = true;
		chr = cmd[i][j];
	}
	else
	{
		if (cmd[i][j] == chr && open == true)
		{
			open = false;
			chr = '\0';
		}
		else
			printf("%c", cmd[i][j]);
	}
	return (open);
}

// IMITA LA FUNCION ECHO
void	ft_echo(char **cmd)
{
	int		i;
	int		j;
	bool	open;

	i = 1;
	open = false;
	if (ft_strncmp(cmd[1], "-n\0", 3) == 0)
		i = 2;
	while (cmd[i] != 0)
	{
		j = 0;
		while (cmd[i][j] != '\0')
		{
			open = ft_echo_normi(cmd, i, j, open);
			j++;
		}
		i++;
		if (cmd[i] != 0)
			printf(" ");
	}
	if (ft_strncmp(cmd[1], "-n\0", 3) != 0)
		printf("\n");
	free_matrix(cmd);
}

// IMITA EL COMANDO CD
void	ft_cd(char *text, t_lst_env **lst_env)
{
	char	**split;
	char	**dir;
	char	*old_pwd;
	char	*pwd;

	split = ft_split(text, ' ');
	if (check_array_length(split) == 3)
		printf("too many arguments\n");
	else
	{
		old_pwd = getcwd(NULL, 0);
		if (split[1] == NULL)
		{
			dir = search_lst_env("HOME", lst_env);
			handle_cd_env(lst_env, ft_fusion_string, "export OLDPWD=", old_pwd);
			if (dir == NULL)
			{
				printf("HOME no set\n");
				free_matrix(dir);
				free_matrix(split);
				free(old_pwd);
				return ;
			}
			else
			{
				if (chdir(dir[1]) != 0)
				{
					printf("Could not access directory\n");
					free_matrix(dir);
					free_matrix(split);
					free(old_pwd);
					return ;
				}
				handle_cd_env(lst_env, ft_fusion_string, "export PWD=", dir[1]);
				free(dir[0]);
				free(dir);
			}
		}
		else
		{
			if (chdir(split[1]) != 0)
			{
				printf("Could not access directory\n");
				free_matrix(split);
				free(old_pwd);
				return ;
			}
			pwd = getcwd(NULL, 0);
			handle_cd_env(lst_env, ft_fusion_string, "export OLDPWD=", old_pwd);
			handle_cd_env(lst_env, ft_fusion_string, "export PWD=", pwd);
		}
	}
	free_matrix(split);
}

void	ft_exit(t_ast **head, t_lst_env *lst_env, char *prompt)
{
	clean_ast(*head);
	rl_clear_history();
	free_lst_env(lst_env);
	free(prompt);
	exit(0);
}
