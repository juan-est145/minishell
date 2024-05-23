/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juestrel <juestrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:06:30 by juestrel          #+#    #+#             */
/*   Updated: 2024/05/23 13:06:32 by juestrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../libft/libft.h"

bool	token_is_binary_operator(t_token_list **head)
{
	if ((*head)->token_identifer == AND || (*head)->token_identifer == OR
		|| (*head)->token_identifer == PIPE)
		return (true);
	return (false);
}

t_ast	*new_ast_node(void)
{
	t_ast	*new_node;

	new_node = malloc(sizeof(t_ast));
	if (new_node == NULL)
		return (NULL);
	new_node->args = NULL;
	new_node->redirections = NULL;
	new_node->left = NULL;
	new_node->right = NULL;
	return (new_node);
}

int	current_precedence(t_token_list **head)
{
	if ((*head)->token_identifer == OR || (*head)->token_identifer == AND)
		return (0);
	return (1);
}

t_ast	*join_left_right_nodes(t_ast *left, t_ast *right,
		t_token_identifier current_parse)
{
	t_ast	*new_node;

	new_node = malloc(sizeof(t_ast));
	if (new_node == NULL)
		return (free(left), free(right), NULL);
	if (current_parse == PIPE)
		new_node->parse_identifier = PARSE_PIPE;
	else if (current_parse == AND)
		new_node->parse_identifier = PARSE_AND;
	else
		new_node->parse_identifier = PARSE_OR;
	new_node->args = NULL;
	new_node->redirections = NULL;
	new_node->right = right;
	new_node->left = left;
	return (new_node);
}

bool	is_redir(t_token_identifier identifier)
{
	if (identifier == REDIR_INSERT || identifier == REDIR_APPEND
		|| identifier == REDIR_INPUT || identifier == REDIR_TERMINAL_LINES)
		return (true);
	return (false);
}
