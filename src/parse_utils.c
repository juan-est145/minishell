/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-est145 <juan-est145@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:30:29 by juan-est145       #+#    #+#             */
/*   Updated: 2024/04/23 17:07:01 by juan-est145      ###   ########.fr       */
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

t_AST	*join_left_right_nodes(t_AST *left, t_AST *right,
		t_token_identifier current_parse)
{
	t_AST	*new_node;

	new_node = malloc(sizeof(t_AST));
	if (new_node == NULL)
		return (NULL);
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

void	clean_ast(t_AST *node)
{
	if (node == NULL)
		return ;
	if (node->args != NULL)
		free(node->args);
	if (node->redirections != NULL)
		free(node->redirections);
	clean_ast(node->left);
	clean_ast(node->right);
	free(node);
}
