/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   archive_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juestrel <juestrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 17:00:52 by mfuente-          #+#    #+#             */
/*   Updated: 2024/06/10 13:26:12 by juestrel         ###   ########.fr       */
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
	int	i;

	i = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

void	handle_cd_env(t_lst_env **lst_env, char *fusion, t_pipex *str_pipes,
		t_ast *node)
{
	char	*text;
	t_ast	*node_aux;

	text = "PIPES";
	(void)node;
	if (fusion != text)
	{
		node_aux = new_ast_node();
		node_aux->args = fusion;
		ft_export(node_aux, lst_env, str_pipes, SIMPLE_CMD);
		free(node_aux);
	}
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
