/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtings.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:12:06 by user42            #+#    #+#             */
/*   Updated: 2024/04/24 16:55:10 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../../include/minishell.h"

//IMITA EL COMANDO PWD
void ft_getpwd(char *text, t_lst_env *lst_env)
{
    char *pwd;
	char **split;
	t_lst_env *temp;
	int len;

	temp = lst_env;
	while (temp->next != NULL)
	{
 		if (ft_strncmp(temp->next->text, "PWD", 3) == 0)
		{
			split = ft_split(temp->next->text, '=');
			len = ft_strlen(split[1]);
		}
		temp = temp->next;
	}	
	free_matrix(split);
	split = ft_split(text, ' ');
	pwd = malloc(sizeof(char) * len);
	if (split[1] != NULL)
	{
		printf("too many arguments\n");
		return ;
	}
    if (getcwd(pwd, sizeof(char) * len+1) == NULL)
		printf("Error al obtener el pwd\n");
    printf("%s\n", pwd);
	free(pwd);
	free_matrix(split);
}

//IMITA LA FUNCION ECHO
void ft_echo(char **cmd)
{
    int i = 1;
    int j = 0;
	char chr;
	bool open ;

	open = false;
    if (ft_strncmp(cmd[1], "-n\0", 3) == 0)
        i = 2;
    while (cmd[i] != 0)
    {
        j = 0;
        while (cmd[i][j] != '\0')
        {
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
//IMITA EL COMANDO ENV
void ft_env(t_lst_env *lst_env, char *text)
{
	(void)text;
	while (lst_env != NULL)
    {
		if (lst_env->next != NULL)
        	printf("%s\n", lst_env->next->text);
		lst_env = lst_env->next;
    }
}
//IMITA EL COMANDO EXPORT
void ft_export(char *new, t_lst_env *lst_env)
{	
	t_lst_env *copia;
	char **split = ft_split(new, ' ');
	int i = 0;
	while (split[i])
	{
		if (ft_contain(split[i], '=') == 0 && ft_strlen(split[i]) > 2)
		{
 			if (ft_lst_contain_change(&lst_env, split[i]) == 0)
			{
				
			}
			else
			{
				copia = ft_lstnew_ms(split[i]);
				printf("%s\n", copia->text);
				ft_lstadd_back(&lst_env, copia);
			}
		}

		i++;
	}
	free_matrix(split);
}
//IMITA EL COMANDO UNSET
bool ft_unset_normi(t_lst_env *temp, bool flag)
{
	t_lst_env *aux;

	if (temp->next->next != NULL)
	{
		aux = temp->next;
		temp->next = temp->next->next;
		free(aux);
	}	
	else
	{
		aux = temp->next;
		temp->next = NULL;
		free(aux);
		flag = true;
		return (flag);
//		break;
	}
	return (flag);
}

void ft_unset(char *text, t_lst_env *lst_env)
{
	t_lst_env	*temp;
	int i;
	bool flag;
	char **name;
	char **split;

	temp = lst_env;
	flag = false;
	split = ft_split(text, ' ');
	while (temp->next != NULL)
	{
		name = ft_split(temp->next->text, '=');
		i = 1;
		while (split[i])
		{
			if (ft_strncmp(name[0], split[i], ft_strlen(name[0])) == 0)
			{
/* 				if (temp->next->next != NULL)
					temp->next = temp->next->next;
				else
				{
					temp->next = NULL;
					flag = true;
					break;
				} */
				flag = ft_unset_normi(temp, flag);
				if (flag == true)
					break;
			}
			i++;
		}
		free_matrix(name);
		if (flag == true)
			break;
		temp = temp->next;
	}
	free_matrix(split);
}

//IMITA EL COMANDO CD
void ft_cd(char *text, t_lst_env *lst_env)
{
	char **split;
	char pwd[1024];
	char *aux;
	
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
