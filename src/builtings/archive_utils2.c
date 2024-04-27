/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   archive_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-est145 <juan-est145@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 17:00:52 by mfuente-          #+#    #+#             */
/*   Updated: 2024/04/27 20:08:16 by juan-est145      ###   ########.fr       */
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

/*int	get_pwd_cd_length(t_lst_env *lst_env, char *string_to_search)
{
	t_lst_env	*temp;
	int			len;

	len = 0;
	temp = lst_env;
	len = ft_getpwd_normi(temp, len, string_to_search);
	return (len);
}*/

void	handle_cd_env(t_lst_env *lst_env, char *f(char *s1, char *s2),
		char *export_text)
{
	char	*pwd;
	char	*aux;

	pwd = getcwd(NULL, 0);
	aux = f(export_text, pwd);
	ft_export(aux, lst_env);
	free(aux);
	free(pwd);
}
