/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtings1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-est145 <juan-est145@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 14:01:57 by mfuente-          #+#    #+#             */
/*   Updated: 2024/04/27 20:12:54 by juan-est145      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../libft/libft.h"

// IMITA EL COMANDO PWD
/*int	ft_getpwd_normi(t_lst_env *temp, int len, char *string_to_search)
{
	char	**pwd_len;

	while (temp->next != NULL)
	{
		if (ft_strncmp(temp->next->text, string_to_search,
				ft_strlen(string_to_search)) == 0)
		{
			pwd_len = ft_split(temp->next->text, '=');
			len = ft_strlen(pwd_len[1]);
			free_matrix(pwd_len);
			break ;
		}
		temp = temp->next;
	}
	return (len);
}*/

void	ft_getpwd(char *text)
{
	char		*pwd;
	char		**split;

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
void	ft_cd(char *text, t_lst_env *lst_env)
{
	char	**split;

	split = ft_split(text, ' ');
	if (split[2] != NULL)
		printf("too many arguments\n");
	else
	{
		handle_cd_env(lst_env, ft_fusion_string, "export OLDPWD=");
		if (chdir(split[1]) == -1)
			printf("Couldn't change directory\n");
		handle_cd_env(lst_env, ft_fusion_string, "export PWD=");
	}
	free_matrix(split);
}
