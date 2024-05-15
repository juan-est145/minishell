/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfuente- <mfuente-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:40:26 by user42            #+#    #+#             */
/*   Updated: 2024/05/15 17:47:38 by mfuente-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include <stdbool.h>

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

typedef struct s_ast
{
	t_parse_identifier		parse_identifier;
	t_redirections			*redirections;
	char					*args;
	struct s_ast			*left;
	struct s_ast			*right;
}							t_ast;

t_ast						*create_ast(t_token_list **head,
								bool *syntax_error);
t_token_list				*get_next_token(t_token_list **head);
bool						token_is_binary_operator(t_token_list **head);
t_ast						*new_ast_node(void);
int							current_precedence(t_token_list **head);
t_ast						*join_left_right_nodes(t_ast *left, t_ast *right,
								t_token_identifier current_parse);
void						clean_ast(t_ast *node);
bool						is_redir(t_token_identifier identifier);
t_redirections				*create_red_node(t_token_identifier red_type);
void						append_red_node(t_redirections **head,
								t_redirections *node);
t_ast						*malloc_check(t_ast *left);
int						redirected_destination(t_redirections **node);//MIO

#endif