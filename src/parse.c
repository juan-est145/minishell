/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-est145 <juan-est145@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 19:15:52 by juan-est145       #+#    #+#             */
/*   Updated: 2024/04/23 13:43:52 by juan-est145      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "minishell.h"

static t_AST	*precedence_climbing(int precedence, t_token_list **copy);
static t_AST	*process_current_token(t_token_list **head);
static char		*handle_cmd_args(t_token_list **head);

t_AST	*create_ast(t_token_list **head)
{
	t_AST			*ast_head;
	t_token_list	**head_copy;

	head_copy = head;
	ast_head = precedence_climbing(0, head_copy);
	return (ast_head);
}

static t_AST	*precedence_climbing(int precedence, t_token_list **copy)
{
	t_AST				*left;
	t_AST				*right;
	int					updated_prec;
	t_parse_identifier	current_parse;

	(void)current_parse;
	(void)updated_prec;
	(void)left;
	(void)right;
	(void)precedence;
	if ((*copy)->token == NULL)
		return (NULL);
	left = process_current_token(copy);
	if (left == NULL)
		return (NULL);
	if (get_next_token(copy) == NULL)
		return (NULL);
	return (left);
}

static t_AST	*process_current_token(t_token_list **head)
{
	t_AST	*ast_node;

	ast_node = new_ast_node();
	ast_node->parse_identifier = PARSE_CMD;
	if (ast_node == NULL)
		return (NULL);
	while (*head != NULL && token_is_binary_operator(head) == false)
	{
		if ((*head)->token_identifer == EXPRESSION)
			ast_node->args = handle_cmd_args(head);
		get_next_token(head);
	}
	return (ast_node);
}

static char	*handle_cmd_args(t_token_list **head)
{
	char	*cmds_args;
	char	*copy_to_free;

	cmds_args = ft_substr((*head)->token, 0, ft_strlen((*head)->token));
	if (cmds_args == NULL)
		return (NULL);
	copy_to_free = cmds_args;
	get_next_token(head);
	while (*head != NULL && (*head)->token_identifer == EXPRESSION)
	{
		cmds_args = ft_strjoin(cmds_args, (*head)->token);
		free(copy_to_free);
		if (cmds_args == NULL)
			return (NULL);
		copy_to_free = cmds_args;
		get_next_token(head);
	}
	return (cmds_args);
}
