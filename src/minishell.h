/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-est145 <juan-est145@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 11:41:38 by juan-est145       #+#    #+#             */
/*   Updated: 2024/04/22 17:00:30 by juan-est145      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

typedef struct s_token_list
{
	char				*token;
	struct s_token_list	*prev;
	struct s_token_list	*next;
}						t_token_list;

bool					ft_isspace(unsigned char c);
t_token_list			*tokenize_cmd(char *full_cmd);
