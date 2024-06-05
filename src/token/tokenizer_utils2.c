/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juestrel <juestrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:05:26 by juestrel          #+#    #+#             */
/*   Updated: 2024/06/05 16:25:32 by juestrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../libft/libft.h"

void	delete_empty_nodes(t_token_list *head)
{
	t_token_list	*previous;
	t_token_list	*temp;

	temp = NULL;
	while (head != NULL)
	{
		previous = head->prev;
		if (*head->token == '\0')
		{
			previous->next = head->next;
			if (head->next != NULL)
				head->next->prev = previous;
			temp = head;
			head = head->next;
			free(temp->token);
			free(temp);
			temp = NULL;
			continue ;
		}
		head = head->next;
	}
}

void	expand_variables(t_token_list **head, t_lst_env **lst_env,
		t_pipex *str_pipe)
{
	t_token_list	*temp;

	temp = *head;
	while (temp != NULL)
	{
		if (temp->token_identifer == EXPRESSION)
			temp->token = find_env_var(temp->token, lst_env, str_pipe);
		temp = temp->next;
	}
}

unsigned int	find_last_env_index(char *text, unsigned int env_i)
{
	unsigned int	i;

	i = env_i;
	while (text[i] != '\0' && ft_isspace(text[i]) == false && text[i] != '\"')
	{
		if ((text[i] == '$' || (ft_isalnum(text[i]) == false && text[i] != '?'
					&& text[i] != '_')) && i != env_i)
			break ;
		i++;
	}
	return (i);
}
