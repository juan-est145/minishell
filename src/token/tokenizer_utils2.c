/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-est145 <juan-est145@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 19:46:34 by juan-est145       #+#    #+#             */
/*   Updated: 2024/05/02 20:00:15 by juan-est145      ###   ########.fr       */
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
