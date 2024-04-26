/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtings1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-est145 <juan-est145@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 14:01:57 by mfuente-          #+#    #+#             */
/*   Updated: 2024/04/26 13:11:53 by juan-est145      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../libft/libft.h"

// IMITA EL COMANDO PWD
int	ft_getpwd_normi(t_lst_env *temp, int len)
{
	char	**pwd_len;

	while (temp->next != NULL)
	{
		if (ft_strncmp(temp->next->text, "PWD", 3) == 0)
		{
			pwd_len = ft_split(temp->next->text, '=');
			len = ft_strlen(pwd_len[1]);
			free_matrix(pwd_len);
		}
		temp = temp->next;
	}
	return (len);
}

void	ft_getpwd(char *text, t_lst_env *lst_env)
{
	char		*pwd;
	char		**split;
	t_lst_env	*temp;
	int			len;

	temp = lst_env;
	len = 0;
	split = NULL;
	len = ft_getpwd_normi(temp, len);
	split = ft_split(text, ' ');
	pwd = malloc(sizeof(char) * len);
	if (split[1] != NULL)
	{
		printf("too many arguments\n");
		return ;
	}
	if (getcwd(pwd, sizeof(char) * len + 1) == NULL)
		printf("Error al obtener el pwd\n");
	printf("%s\n", pwd);
	free(pwd);
	free_matrix(split);
}

bool	ft_echo_normi(char **cmd, int i, int j, bool open)
{
	char	chr;

	chr = '\0';
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
	char	pwd[1024];
	char	*aux;

	split = ft_split(text, ' ');
	if (split[2] != NULL)
	{
		printf("too many arguments\n ");
	}
	else
	{
		getcwd(pwd, sizeof(pwd));
		aux = ft_fusion_string("export OLDPWD=", pwd);
		ft_export(aux, lst_env);
		chdir(split[1]);
		free(aux);
		getcwd(pwd, sizeof(pwd));
		aux = ft_fusion_string("export PWD=", pwd);
		ft_export(aux, lst_env);
		free(aux);
	}
	free_matrix(split);
}
