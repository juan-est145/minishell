/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juestrel <juestrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 19:38:52 by juestrel          #+#    #+#             */
/*   Updated: 2024/06/06 20:03:41 by juestrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../libft/libft.h"

static void	clean_nodes(char *temp, char *beginning, t_ast *node);

void	quotes_at_start(t_ast *node, int quote_array[2])
{
	int		start_index;
	int		end_index;
	char	*substr;
	char	*temp;

	start_index = 1;
	end_index = quote_array[1] - 1;
	substr = ft_substr(node->args, start_index, end_index);
	temp = substr;
	if (node->args[end_index + 2] == '\0')
	{
		free(node->args);
		node->args = substr;
		return ;
	}
	substr = ft_strjoin(substr, &node->args[end_index + 2]);
	free(temp);
	free(node->args);
	node->args = substr;
	return ;
}

void	quotes_elsewhere(t_ast *node, int quote_array[2])
{
	int		start_index;
	int		end_index;
	char	*substr;
	char	*temp;
	char	*beginning;

	start_index = quote_array[0] + 1;
	end_index = quote_array[1] - 1;
	substr = ft_substr(node->args, start_index, (end_index - start_index) + 1);
	beginning = ft_substr(node->args, 0, start_index - 1);
	temp = substr;
	substr = ft_strjoin(beginning, substr);
	if (node->args[end_index + 2] != '\0')
	{
		free(temp);
		temp = substr;
		substr = ft_strjoin(substr, &node->args[end_index + 2]);
		clean_nodes(temp, beginning, node);
		node->args = substr;
		return ;
	}
	clean_nodes(temp, beginning, node);
	node->args = substr;
}

static void	clean_nodes(char *temp, char *beginning, t_ast *node)
{
	if (temp != NULL)
		free(temp);
	if (beginning != NULL)
		free(beginning);
	if (node->args != NULL)
		free(node->args);
}
