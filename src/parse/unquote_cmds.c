/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unquote_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juestrel <juestrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 16:11:26 by juestrel          #+#    #+#             */
/*   Updated: 2024/06/07 12:50:34 by juestrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../libft/libft.h"

static void	find_quotes(t_ast *node);
static void	get_quote_index(t_ast *node, int quote_array[2], unsigned int i);
static bool	quotes_terminated(t_ast *node);
void		set_new_str(t_ast *node, int quote_array[2]);

void	unquote_cmds(t_ast *node)
{
	if (node == NULL)
		return ;
	else if (node->parse_identifier == PARSE_CMD)
	{
		find_quotes(node);
		find_quotes_redir(node);
	}
	else if (node->parse_identifier == PARSE_PIPE)
	{
		unquote_cmds(node->left);
		unquote_cmds(node->right);
	}
	else
		return ;
}

static void	find_quotes(t_ast *node)
{
	unsigned int	i;
	int				quote_array[2];

	i = 0;
	quote_array[0] = -1;
	quote_array[1] = -1;
	if (node->args == NULL || *node->args == '\0')
		return ;
	if (ft_strchr(node->args, '\"') == NULL && ft_strchr(node->args,
			'\'') != NULL && quotes_terminated(node) == false)
		return ;
	get_quote_index(node, quote_array, i);
}

static void	get_quote_index(t_ast *node, int quote_array[2], unsigned int i)
{
	char	delimiter;

	delimiter = '\0';
	while (node->args[i] != '\0')
	{
		if (node->args[i] == '\'' || node->args[i] == '\"')
		{
			set_delimiter(&delimiter, node->args, i);
			if (delimiter != '\0' && quote_array[0] == -1)
				quote_array[0] = i;
			else if (delimiter == '\0' && quote_array[0] != -1)
				quote_array[1] = i;
			if (quote_array[0] != -1 && quote_array[1] != -1)
			{
				set_new_str(node, quote_array);
				i = quote_array[1];
				if (ft_strlen(node->args) - 1 < i)
					i = ft_strlen(node->args) - 1;
				quote_array[0] = -1;
				quote_array[1] = -1;
				continue ;
			}
		}
		i++;
	}
}

static bool	quotes_terminated(t_ast *node)
{
	unsigned int	i;
	char			delimiter;

	i = 0;
	delimiter = '\0';
	while (node->args[i] != '\0')
	{
		if (node->args[i] == '\'' || node->args[i] == '\"')
			set_delimiter(&delimiter, node->args, i);
		i++;
	}
	if (delimiter == '\0')
		return (true);
	return (false);
}

void	set_new_str(t_ast *node, int quote_array[2])
{
	int	start_index;

	start_index = 0;
	if (start_index == quote_array[0])
	{
		quotes_at_start(node, quote_array);
		return ;
	}
	quotes_elsewhere(node, quote_array);
}
