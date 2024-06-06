/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unquote_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juestrel <juestrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 16:11:26 by juestrel          #+#    #+#             */
/*   Updated: 2024/06/06 18:40:02 by juestrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../libft/libft.h"

static void	find_quotes(t_ast *node);
static bool	quotes_terminated(t_ast *node);
void		set_new_str(t_ast *node, int quote_array[2]);

void	unquote_cmds(t_ast *node)
{
	if (node == NULL)
		return ;
	else if (node->parse_identifier == PARSE_CMD)
		find_quotes(node);
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
	int				quote_array[2];
	unsigned int	i;
	char			delimiter;

	i = 0;
	delimiter = '\0';
	quote_array[0] = -1;
	quote_array[1] = -1;
	if (ft_strchr(node->args, '\"') == NULL && ft_strchr(node->args,
			'\'') != NULL && quotes_terminated(node) == false)
		return ;
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
				quote_array[0] = -1;
				quote_array[1] = -1;
				i = 0;
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
	int		start_index;
	int		end_index;
	char	*substr;
	char	*temp;
    char    *beginning;

	start_index = 0;
	if (start_index == quote_array[0])
    {
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
	start_index = quote_array[0] + 1;
	end_index = quote_array[1] - 1;
	substr = ft_substr(node->args, start_index, (end_index - start_index) + 1);
    beginning = ft_substr(node->args, 0, start_index -1);
	temp = substr;
	substr = ft_strjoin(beginning, substr);
    if (node->args[end_index + 2] != '\0')
    {
        free(temp);
        temp = substr;
        substr = ft_strjoin(substr, &node->args[end_index + 2]);
        free(temp);
        free(beginning);
        free(node->args);
	    node->args = substr;
        return ;
    }
	free(temp);
    free(beginning);
    free(node->args);
	node->args = substr;
}
