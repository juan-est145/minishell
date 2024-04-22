/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-est145 <juan-est145@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 17:44:18 by juan-est145       #+#    #+#             */
/*   Updated: 2024/04/22 19:13:39 by juan-est145      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "minishell.h"

void	clean_tokens(t_token_list **head)
{
	t_token_list	*temp;

	while (*head != NULL)
	{
		temp = *head;
		*head = (*head)->next;
		if (temp->token != NULL)
			free(temp->token);
		free(temp);
	}
}

void	add_token_identifiers(t_token_list *node)
{
	size_t	token_length;

	token_length = ft_strlen(node->token);
	if (token_length == 1 && *node->token == '|')
		node->token_identifer = PIPE;
	else if (token_length == 1 && *node->token == '>')
		node->token_identifer = REDIR_INSERT;
	else if (token_length == 2 && ft_strnstr(node->token, ">>", 2) != NULL)
		node->token_identifer = REDIR_APPEND;
	else if (token_length == 1 && *node->token == '<')
		node->token_identifer = REDIR_INPUT;
	else if (token_length == 2 && ft_strnstr(node->token, "<<", 2) != NULL)
		node->token_identifer = REDIR_TERMINAL_LINES;
	else if (token_length == 2 && ft_strnstr(node->token, "&&", 2) != NULL)
		node->token_identifer = AND;
	else if (token_length == 2 && ft_strnstr(node->token, "||", 2) != NULL)
		node->token_identifer = OR;
	else
		node->token_identifer = EXPRESSION;
}
