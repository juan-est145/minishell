/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-est145 <juan-est145@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 19:15:52 by juan-est145       #+#    #+#             */
/*   Updated: 2024/04/22 19:52:44 by juan-est145      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "minishell.h"

t_AST	*create_ast(t_token_list **head)
{
	t_AST			*ast_head;
	t_token_list	**head_copy;
}

static t_AST	*precedence_climbing(int precedence, t_token_list **copy)
{
	t_AST				*left;
	t_AST				*rigt;
	int					updated_prec;
	t_parse_identifier	current_parse;
}
