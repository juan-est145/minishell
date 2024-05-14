/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-est145 <juan-est145@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 19:46:34 by juan-est145       #+#    #+#             */
/*   Updated: 2024/05/14 14:38:26 by juan-est145      ###   ########.fr       */
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

void	expand_variables(t_token_list **head, t_lst_env **lst_env)
{
	t_token_list	*temp;

	temp = *head;
	while (temp != NULL)
	{
		if (temp->token_identifer == EXPRESSION)
			temp->token = find_env_var(temp->token, lst_env);
		temp = temp->next;
	}
}

char	set_env_delimiter(char delimiter)
{
	if (delimiter == '\0')
		return ('\'');
	return ('\0');
}
