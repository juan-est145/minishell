/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-est145 <juan-est145@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 19:15:52 by juan-est145       #+#    #+#             */
/*   Updated: 2024/04/23 14:08:06 by juan-est145      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "minishell.h"

static t_AST	*precedence_climbing(int precedence, t_token_list **copy);
static t_AST	*process_current_token(t_token_list **head);
static char		*handle_cmd_args(t_token_list **head);
static char		*handle_redir(t_token_list **head);

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
	t_token_identifier	current_parse;

	(void)current_parse;
	(void)right;
	if ((*copy)->token == NULL)
		return (NULL);
	left = process_current_token(copy);
	if (left == NULL)
		return (NULL);
	while ((*copy) != NULL && token_is_binary_operator(copy) == true
		&& precedence >= current_precedence(copy))
	{
		current_parse = (*copy)->token_identifer;
		get_next_token(copy);
		updated_prec = current_precedence(copy) + 1;
		right = precedence_climbing(updated_prec, copy);
	}
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
		if ((*head)->token_identifer != EXPRESSION)
			ast_node->redirections = handle_redir(head);
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

//TO DO: Check the data type for storing redirections, 
//maybe need to change to **char or  a struct with more information

static char	*handle_redir(t_token_list **head)
{
	(void)head;
	return (NULL);
}