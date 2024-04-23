/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-est145 <juan-est145@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:30:29 by juan-est145       #+#    #+#             */
/*   Updated: 2024/04/23 14:00:44 by juan-est145      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "minishell.h"

bool	token_is_binary_operator(t_token_list **head)
{
	if ((*head)->token_identifer == AND || (*head)->token_identifer == OR
		|| (*head)->token_identifer == PIPE)
		return (true);
	return (false);
}

t_AST	*new_ast_node(void)
{
	t_AST	*new_node;

	new_node = malloc(sizeof(t_AST));
	if (new_node == NULL)
		return (NULL);
	return (new_node);
}

int	current_precedence(t_token_list **head)
{
	if ((*head)->token_identifer == OR || (*head)->token_identifer == AND)
		return (0);
	return (1);
}
