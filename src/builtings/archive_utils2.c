/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   archive_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfuente- <mfuente-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 17:00:52 by mfuente-          #+#    #+#             */
/*   Updated: 2024/05/02 11:13:04 by mfuente-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../libft/libft.h"

void	ft_lstadd_back_ms(t_lst_env **lst, t_lst_env *new)
{
	t_lst_env	*temp;

	if (!*lst)
		*lst = new;
	else
	{
		temp = *lst;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}
}

void	handle_cd_env(t_lst_env **lst_env, char *f(char *s1, char *s2),
		char *export_text, char *pwd)
{
	char	*aux;

	aux = f(export_text, pwd);
	ft_export(aux, lst_env);
	free(aux);
	free(pwd);
}

int	ignore_space(char *text, int i)
{
	while (text[i] == ' ' && text[i + 1] == ' ')
		i++;
	return (i);
}
