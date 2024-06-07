/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unquote_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juestrel <juestrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 11:56:02 by juestrel          #+#    #+#             */
/*   Updated: 2024/06/07 12:48:16 by juestrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../libft/libft.h"

static bool	quotes_terminated(t_redirections *node);
static void	get_quote_index_redir(t_redirections *node, int quote_array[2],
				unsigned int i);
static void	set_new_str_redir(t_redirections *node, int quote_array[2]);

void	find_quotes_redir(t_ast *node)
{
	unsigned int	i;
	int				quote_array[2];
	t_redirections	*temp;

	i = 0;
	temp = node->redirections;
	while (temp != NULL)
	{
		quote_array[0] = -1;
		quote_array[1] = -1;
		if (ft_strchr(temp->file_location, '\"') == NULL
			&& ft_strchr(temp->file_location, '\'') != NULL
			&& quotes_terminated(temp) == false)
		{
			temp = temp->next;
			continue ;
		}
		get_quote_index_redir(temp, quote_array, i);
		temp = temp->next;
	}
}

static bool	quotes_terminated(t_redirections *node)
{
	unsigned int	i;
	char			delimiter;

	i = 0;
	delimiter = '\0';
	while (node->file_location[i] != '\0')
	{
		if (node->file_location[i] == '\'' || node->file_location[i] == '\"')
			set_delimiter(&delimiter, node->file_location, i);
		i++;
	}
	if (delimiter == '\0')
		return (true);
	return (false);
}

static void	get_quote_index_redir(t_redirections *node, int quote_array[2],
		unsigned int i)
{
	char	delimiter;

	delimiter = '\0';
	while (node->file_location[i] != '\0')
	{
		if (node->file_location[i] == '\'' || node->file_location[i] == '\"')
		{
			set_delimiter(&delimiter, node->file_location, i);
			if (delimiter != '\0' && quote_array[0] == -1)
				quote_array[0] = i;
			else if (delimiter == '\0' && quote_array[0] != -1)
				quote_array[1] = i;
			if (quote_array[0] != -1 && quote_array[1] != -1)
			{
				set_new_str_redir(node, quote_array);
				i = quote_array[1];
				if (ft_strlen(node->file_location) - 1 < i)
					i = ft_strlen(node->file_location) - 1;
				quote_array[0] = -1;
				quote_array[1] = -1;
				continue ;
			}
		}
		i++;
	}
}

static void	set_new_str_redir(t_redirections *node, int quote_array[2])
{
	int	start_index;

	start_index = 0;
	if (start_index == quote_array[0])
	{
		redir_quotes_at_start(node, quote_array);
		return ;
	}
	redir_quotes_elsewhere(node, quote_array);
}
