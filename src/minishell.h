/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-est145 <juan-est145@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 11:41:38 by juan-est145       #+#    #+#             */
/*   Updated: 2024/04/23 16:00:38 by juan-est145      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>

/*	PIPE == '|',
	EXPRESSION == Either a command or it's arguments and flags,
	RED_INSERT == >,
	RED_APPEND == >>,
	RED_INPUT == < ,
	RED_TERMINAL_LINES == <<,
	AND == &&,
	OR == ||
*/

typedef enum e_token_identifier
{
	PIPE,
	EXPRESSION,
	REDIR_INSERT,
	REDIR_APPEND,
	REDIR_INPUT,
	REDIR_TERMINAL_LINES,
	AND,
	OR
}						t_token_identifier;

typedef struct s_token_list
{
	char				*token;
	t_token_identifier	token_identifer;
	struct s_token_list	*prev;
	struct s_token_list	*next;
}						t_token_list;

typedef enum e_parse_identifier
{
	PARSE_PIPE,
	PARSE_AND,
	PARSE_OR,
	PARSE_CMD
}						t_parse_identifier;

typedef struct s_AST
{
	t_parse_identifier	parse_identifier;
	char				*redirections;
	char				*args;
	struct s_AST		*left;
	struct s_AST		*right;
}						t_AST;

bool					ft_isspace(unsigned char c);
t_token_list			*tokenize_cmd(char *full_cmd);
void					clean_tokens(t_token_list **head);
void					add_token_identifiers(t_token_list *node);
t_AST					*create_ast(t_token_list **head);
t_token_list			*get_next_token(t_token_list **head);
bool					token_is_binary_operator(t_token_list **head);
t_AST					*new_ast_node(void);
int						current_precedence(t_token_list **head);
t_AST					*join_left_right_nodes(t_AST *left, t_AST *right,
							t_token_identifier current_parse);
void					clean_ast(t_AST *node);
bool					is_redir(t_token_identifier identifier);
#endif