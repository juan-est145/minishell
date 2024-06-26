/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtings2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juestrel <juestrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:08:56 by juestrel          #+#    #+#             */
/*   Updated: 2024/06/10 15:56:40 by juestrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../libft/libft.h"

void	is_first(char *text, t_lst_env **lst_env)
{
	char		**name;
	int			i;
	t_lst_env	*temp;

	name = ft_split(text, ' ');
	i = 1;
	temp = NULL;
	while (name[i] != NULL)
	{
		if (ft_strncmp(name[i], (*lst_env)->text, ft_strlen(name[i])) == 0)
		{
			temp = *lst_env;
			*lst_env = (*lst_env)->next;
			free(temp->text);
			free(temp);
			i = 1;
		}
		else
			i++;
	}
	free_matrix(name);
}

char	**search_lst_env(char *text, t_lst_env **lst_env)
{
	t_lst_env	*temp;
	char		**result;

	temp = *lst_env;
	while (temp != NULL)
	{
		if (ft_strncmp(text, temp->text, ft_strlen(text)) == 0)
		{
			result = ft_split(temp->text, '=');
			return (result);
		}
		temp = temp->next;
	}
	return (NULL);
}

int	check_array_length(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
		i++;
	return (i);
}

int	errors_cd(char *old_pwd, char **dir, char **split, char *text)
{
	if (ft_strncmp(text, "HOME no set", ft_strlen(text)) == 0)
	{
		if (dir == NULL)
		{
			printf("%s\n", text);
			return (1);
		}
	}
	else
	{
		if (chdir(dir[1]) != 0)
		{
			printf("%s\n", text);
			if (split != NULL)
				free_matrix(split);
			if (old_pwd != NULL)
				free(old_pwd);
			return (1);
		}
	}
	return (0);
}

int	cd_no_argument(t_ast *node, t_str_aux aux, t_lst_env **lst_env,
		t_pipex *str_pipes)
{
	char	**dir;
	char	*fusion;

	dir = search_lst_env("HOME", lst_env);
	if (errors_cd(aux.old_pwd, dir, aux.split, "HOME no set") == 1)
		return (free_matrix(dir), clean_pwds(aux, str_pipes));
	if (errors_cd(aux.old_pwd, dir, aux.split,
			"Could not access directory") == 1)
		return (free_matrix(dir), clean_pwds(aux, str_pipes));
	fusion = ft_fusion_string("export PWD=", dir[1]);
	handle_cd_env(lst_env, fusion, str_pipes, node);
	free_matrix(dir);
	clean_pwds(aux, str_pipes);
	free(fusion);
	str_pipes->return_cmd_status = 0;
	return (0);
}
