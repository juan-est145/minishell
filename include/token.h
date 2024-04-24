/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:37:27 by user42            #+#    #+#             */
/*   Updated: 2024/04/24 16:50:18 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
#define TOKEN_H

#include "minishell.h"
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
}							t_token_identifier;

typedef struct s_token_list
{
	char					*token;
	t_token_identifier		token_identifer;
	struct s_token_list		*prev;
	struct s_token_list		*next;
}							t_token_list;

bool						ft_isspace(unsigned char c);
t_token_list				*tokenize_cmd(char *full_cmd);
void						clean_tokens(t_token_list **head);
void						add_token_identifiers(t_token_list *node);


#endif