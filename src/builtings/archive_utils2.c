/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   archive_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfuente- <mfuente-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 17:00:52 by mfuente-          #+#    #+#             */
/*   Updated: 2024/05/27 16:07:02 by mfuente-         ###   ########.fr       */
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

int	ft_lstsize_ms(t_lst_env *lst)
{
	int		i;

	i = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		i++;
	}
	return (i);
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

int	redirected_destination(t_redirections **node)
{
	t_redirections	*temp;
	int				fd;

	temp = *node;
	fd = -2;
	while (temp != NULL)
	{
		if (temp->redirection_type == REDIR_INSERT)
			fd = open(temp->file_location, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (temp->redirection_type == REDIR_APPEND)
			fd = open(temp->file_location, O_WRONLY | O_CREAT | O_APPEND, 0777);
		if (fd == -1)
			break ;
		temp = temp->next;
	}
	return (fd);
}
