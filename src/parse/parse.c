/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-est145 <juan-est145@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 19:15:52 by juan-est145       #+#    #+#             */
/*   Updated: 2024/05/01 17:05:34 by juan-est145      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../libft/libft.h"

static t_ast			*precedence_climbing(int precedence,
							t_token_list **copy, bool *syntax_error);
static t_ast			*process_current_token(t_token_list **head,
							bool *syntax_error);
static char				*handle_cmd_args(t_token_list **head);
static t_redirections	*handle_redir(t_token_list **head, bool *syntax_error);

t_ast	*create_ast(t_token_list **head, bool *syntax_error)
{
	t_ast			*ast_head;
	t_token_list	*head_copy;

	head_copy = *head;
	ast_head = precedence_climbing(0, &head_copy, syntax_error);
	clean_tokens(head);
	if (ast_head == NULL && errno == ENOMEM)
		return (NULL);
	if (*syntax_error == true)
		return (printf("Syntax error\n"), clean_ast(ast_head), NULL);
	return (ast_head);
}

static t_ast	*precedence_climbing(int precedence, t_token_list **copy,
		bool *syntax_error)
{
	t_ast				*left;
	t_ast				*right;
	int					updated_prec;
	t_token_identifier	current_parse;

	left = process_current_token(copy, syntax_error);
	if (left == NULL)
		return (NULL);
	while ((*copy) != NULL && token_is_binary_operator(copy) == true
		&& current_precedence(copy) >= precedence)
	{
		current_parse = (*copy)->token_identifer;
		get_next_token(copy);
		if (*copy == NULL)
			return (*syntax_error = true, left);
		updated_prec = current_precedence(copy) + 1;
		right = precedence_climbing(updated_prec, copy, syntax_error);
		if (right == NULL)
			return (malloc_check(left));
		left = join_left_right_nodes(left, right, current_parse);
		if (left == NULL)
			return (NULL);
	}
	return (left);
}

static t_ast	*process_current_token(t_token_list **head, bool *syntax_error)
{
	t_ast	*ast_node;

	ast_node = new_ast_node();
	if (ast_node == NULL)
		return (NULL);
	ast_node->parse_identifier = PARSE_CMD;
	ast_node->redirections = NULL;
	ast_node->args = NULL;
	if (ast_node == NULL)
		return (NULL);
	while (*head != NULL && token_is_binary_operator(head) == false)
	{
		if (*head != NULL && (*head)->token_identifer == EXPRESSION)
			ast_node->args = handle_cmd_args(head);
		if (ast_node->args == NULL)
			return (NULL);
		if (*head != NULL && is_redir((*head)->token_identifer) == true)
			ast_node->redirections = handle_redir(head, syntax_error);
		if (ast_node->redirections == NULL && ast_node->args == NULL)
			return (NULL);
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
		cmds_args = ft_strjoin(cmds_args, " ");
		free(copy_to_free);
		if (cmds_args == NULL)
			return (NULL);
		copy_to_free = cmds_args;
		cmds_args = ft_strjoin(cmds_args, (*head)->token);
		free(copy_to_free);
		if (cmds_args == NULL)
			return (NULL);
		copy_to_free = cmds_args;
		get_next_token(head);
	}
	return (cmds_args);
}

static t_redirections	*handle_redir(t_token_list **head, bool *syntax_error)
{
	t_redirections		*redir_head;
	t_token_identifier	redir_type;
	t_redirections		*redir_tmp;

	redir_head = NULL;
	while (*head != NULL && is_redir((*head)->token_identifer) == true)
	{
		redir_type = (*head)->token_identifer;
		redir_tmp = create_red_node(redir_type);
		if (redir_tmp == NULL)
			return (NULL);
		get_next_token(head);
		if (*head == NULL || (*head)->token_identifer != EXPRESSION)
			return (*syntax_error = true, append_red_node(&redir_head,
					redir_tmp), redir_head);
		redir_tmp->file_location = ft_substr((*head)->token, 0,
				ft_strlen((*head)->token));
		if (redir_tmp->file_location == NULL)
			return (NULL);
		append_red_node(&redir_head, redir_tmp);
		get_next_token(head);
	}
	return (redir_head);
}
