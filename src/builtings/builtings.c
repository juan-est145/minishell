/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtings.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfuente- <mfuente-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:12:06 by user42            #+#    #+#             */
/*   Updated: 2024/04/30 15:38:03 by mfuente-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../libft/libft.h"

// IMITA EL COMANDO ENV
void	ft_env(t_lst_env **lst_env, char *text)
{
	char		**split;
	t_lst_env	*temp;

	temp = *lst_env;
	split = ft_split(text, ' ');
	if (split[1] != NULL)
	{
		free_matrix(split);
		printf("Too many arguments\n");
		return ;
	}
	while (temp != NULL)
	{
		printf("%s\n", temp->text);
		temp = temp->next;
	}
	free_matrix(split);
}

// IMITA EL COMANDO EXPORT
void	ft_export(char *new, t_lst_env **lst_env)
{
	t_lst_env	*node;
	char		*new_env;
	char		**split;
	int			i;

	i = 0;
	split = ft_split(new, ' ');
	while (split[i])
	{
		if (ft_contain(split[i], '=') == 0 && (ft_strlen(split[i]) > 2))
		{
			if (ft_lst_contain_change(lst_env, split[i]) == 0)
				;
			else
			{
				new_env = ft_substr(split[i], 0, ft_strlen(split[i]));
				node = ft_lstnew_ms(new_env);
				ft_lstadd_back_ms(lst_env, node);
			}
		}
		i++;
	}
	free_matrix(split);
}

// IMITA EL COMANDO UNSET
bool	ft_unset_normi(t_lst_env *temp, bool flag, t_lst_env *previous)
{
	t_lst_env	*aux;

	if (temp->next != NULL)
	{
		aux = temp;
		previous->next = temp->next;
//		temp = temp->next;
		free(aux->text);
		free(aux);
	}
	else
	{
		aux = temp;
		previous->next = NULL;
//		temp = NULL;
		free(aux);
		flag = true;
		return (flag);
	}
	return (flag);
}

static bool	ft_unset_normi2(char **split, t_lst_env *previous, bool flag,
		t_lst_env *temp)
{
	int		i;
	char	**name;

	i = 1;
	name = ft_split(temp->text, '=');
	while (split[i])
	{
		if (ft_strncmp(name[0], split[i], ft_strlen(name[0])) == 0)
		{
			flag = ft_unset_normi(temp, flag, previous);
			if (flag == true)
				break ;
		}
		i++;
	}
	return (flag);
}

void	ft_unset(char *text, t_lst_env **lst_env)
{
	t_lst_env	*temp;
	t_lst_env	*previous;
	bool		flag;
	char		**split;

	temp = *lst_env;
	flag = false;
	split = ft_split(text, ' ');
	previous = temp;
	while (temp != NULL)
	{
		flag = ft_unset_normi2(split, previous, flag, temp);
		if (flag == true)
			break ;
		previous = temp;
		temp = temp->next;
	}
	free_matrix(split);
}
