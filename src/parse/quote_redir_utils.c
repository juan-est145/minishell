/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_redir_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juestrel <juestrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 12:11:27 by juestrel          #+#    #+#             */
/*   Updated: 2024/06/07 12:31:07 by juestrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../libft/libft.h"

void	redir_quotes_at_start(t_redirections *node, int quote_array[2])
{
	int		start_index;
	int		end_index;
	char	*substr;
	char	*temp;

	start_index = 1;
	end_index = quote_array[1] - 1;
	substr = ft_substr(node->file_location, start_index, end_index);
	temp = substr;
	if (node->file_location[end_index + 2] == '\0')
	{
		free(node->file_location);
		node->file_location = substr;
		return ;
	}
	substr = ft_strjoin(substr, &node->file_location[end_index + 2]);
	free(temp);
	free(node->file_location);
	node->file_location = substr;
	return ;
}

void	redir_quotes_elsewhere(t_redirections *node, int quote_array[2])
{
	int		start_index;
	int		end_index;
	char	*substr;
	char	*temp;
	char	*beginning;

	start_index = quote_array[0] + 1;
	end_index = quote_array[1] - 1;
	substr = ft_substr(node->file_location, start_index, (end_index
				- start_index) + 1);
	beginning = ft_substr(node->file_location, 0, start_index - 1);
	temp = substr;
	substr = ft_strjoin(beginning, substr);
	if (node->file_location[end_index + 2] != '\0')
	{
		free(temp);
		temp = substr;
		substr = ft_strjoin(substr, &node->file_location[end_index + 2]);
		clean_nodes_redir(temp, beginning, node);
		node->file_location = substr;
		return ;
	}
	clean_nodes_redir(temp, beginning, node);
	node->file_location = substr;
}

void	clean_nodes_redir(char *temp, char *beginning, t_redirections *node)
{
	if (temp != NULL)
		free(temp);
	if (beginning != NULL)
		free(beginning);
	if (node->file_location != NULL)
		free(node->file_location);
}
