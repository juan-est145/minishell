/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_first_pipe_cmd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juestrel <juestrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 17:01:15 by juestrel          #+#    #+#             */
/*   Updated: 2024/05/31 17:08:13 by juestrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../libft/libft.h"

void	find_first_pipe_cmd(t_ast *ast_node)
{
	if (ast_node->left->parse_identifier == PARSE_CMD)
		ast_node->left->simple_or_pipe = ENTRY_PIPE;
	else
		find_first_pipe_cmd(ast_node->left);
}
