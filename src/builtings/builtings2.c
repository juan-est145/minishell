/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtings2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfuente- <mfuente-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 16:45:34 by mfuente-          #+#    #+#             */
/*   Updated: 2024/04/30 16:51:59 by mfuente-         ###   ########.fr       */
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
		if (name[i] == (*lst_env)->text)
		{
			temp = *lst_env;
			*lst_env = (*lst_env)->next;
			free(temp->text);
			free(temp);
			i = 1;
		}
		i++;
	}
	free_matrix(name);
}
