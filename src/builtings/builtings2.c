/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtings2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfuente- <mfuente-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 16:45:34 by mfuente-          #+#    #+#             */
/*   Updated: 2024/05/01 13:05:05 by mfuente-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtings.h"
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

	temp = 	*lst_env;
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

int check_array_length(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
		i++;
	return (i);
}
