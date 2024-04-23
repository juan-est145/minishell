/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-est145 <juan-est145@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:57:57 by juan-est145       #+#    #+#             */
/*   Updated: 2024/04/23 16:00:19 by juan-est145      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "minishell.h"

bool	is_redir(t_token_identifier identifier)
{
	if (identifier == REDIR_INSERT || identifier == REDIR_APPEND
		|| identifier == REDIR_INPUT || identifier == REDIR_TERMINAL_LINES)
		return (true);
	return (false);
}
