/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-est145 <juan-est145@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:40:26 by user42            #+#    #+#             */
/*   Updated: 2024/04/25 12:24:33 by juan-est145      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "minishell.h"

typedef enum e_parse_identifier
{
	PARSE_PIPE,
	PARSE_AND,
	PARSE_OR,
	PARSE_CMD
}							t_parse_identifier;

typedef struct s_redirections
{
	t_token_identifier		redirection_type;
	char					*file_location;
	struct s_redirections	*prev;
	struct s_redirections	*next;
}							t_redirections;

typedef struct s_AST
{
	t_parse_identifier		parse_identifier;
	t_redirections			*redirections;
	char					*args;
	struct s_AST			*left;
	struct s_AST			*right;
}							t_AST;

t_AST						*create_ast(t_token_list **head);
t_token_list				*get_next_token(t_token_list **head);
bool						token_is_binary_operator(t_token_list **head);
t_AST						*new_ast_node(void);
int							current_precedence(t_token_list **head);
t_AST						*join_left_right_nodes(t_AST *left, t_AST *right,
								t_token_identifier current_parse);
void						clean_ast(t_AST *node);
bool						is_redir(t_token_identifier identifier);
t_redirections				*create_red_node(t_token_identifier red_type);
void						append_red_node(t_redirections **head,
								t_redirections *node);
#endif