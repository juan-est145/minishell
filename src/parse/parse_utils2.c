/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-est145 <juan-est145@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:57:57 by juan-est145       #+#    #+#             */
/*   Updated: 2024/05/01 15:46:03 by juan-est145      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../libft/libft.h"

static void		clean_node_list(t_redirections **head);

void	clean_ast(t_ast *node)
{
	if (node == NULL)
		return ;
	if (node->args != NULL)
		free(node->args);
	if (node->redirections != NULL)
		clean_node_list(&node->redirections);
	clean_ast(node->left);
	clean_ast(node->right);
	free(node);
}

static void	clean_node_list(t_redirections **head)
{
	t_redirections	*temp;

	while ((*head) != NULL)
	{
		temp = *head;
		if ((*head)->file_location != NULL)
			free((*head)->file_location);
		*head = (*head)->next;
		free(temp);
	}
}

t_redirections	*create_red_node(t_token_identifier red_type)
{
	t_redirections	*new_node;

	new_node = malloc(sizeof(t_redirections));
	if (new_node == NULL)
		return (NULL);
	new_node->redirection_type = red_type;
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}

void	append_red_node(t_redirections **head, t_redirections *node)
{
	t_redirections	*temp;

	if (*head == NULL)
	{
		*head = node;
		return ;
	}
	temp = *head;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = node;
	node->prev = temp;
}

t_ast	*malloc_check(t_ast *left)
{
	if (errno == ENOMEM)
		return (NULL);
	return (left);
}
