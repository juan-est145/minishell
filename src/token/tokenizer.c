/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juestrel <juestrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:05:36 by juestrel          #+#    #+#             */
/*   Updated: 2024/05/23 13:05:46 by juestrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../libft/libft.h"

static t_token_list	*find_tokens(char *full_cmd, t_token_list **token_list);
static char			*save_token(t_token_list **token_list, char *full_cmd,
						unsigned int *start_index, unsigned int *i);
static void			token_node_add_last(t_token_list **head,
						t_token_list *node);

t_token_list	*tokenize_cmd(char *full_cmd)
{
	t_token_list	*token_list;

	token_list = NULL;
	while (ft_isspace(*full_cmd) == true && *full_cmd != '\0')
		full_cmd++;
	if (*full_cmd == '\0')
	{
		token_list = malloc(sizeof(t_token_list));
		token_list->token = malloc(sizeof(char) * 1);
		*token_list->token = '\0';
		token_list->prev = NULL;
		token_list->next = NULL;
		return (token_list);
	}
	if (find_tokens(full_cmd, &token_list) == NULL)
		return (free(full_cmd), NULL);
	return (token_list);
}

static t_token_list	*find_tokens(char *full_cmd, t_token_list **token_list)
{
	size_t			length;
	unsigned int	i;
	unsigned int	start_index;
	char			delimiter;

	i = 0;
	start_index = 0;
	delimiter = '\0';
	length = ft_strlen(full_cmd);
	while (i <= length && full_cmd[start_index] != '\0')
	{
		if ((ft_isspace(full_cmd[i]) == true && delimiter == '\0')
			|| full_cmd[i] == '\0')
		{
			if (save_token(token_list, full_cmd, &start_index, &i) == NULL)
				return (NULL);
		}
		else if (full_cmd[i] == '\"' || full_cmd[i] == '\'')
			set_delimiter(&delimiter, full_cmd, i);
		i++;
	}
	return (*token_list);
}

static char	*save_token(t_token_list **token_list, char *full_cmd,
		unsigned int *start_index, unsigned int *i)
{
	t_token_list	*new_node;

	new_node = malloc(sizeof(t_token_list));
	if (new_node == NULL)
		return (clean_tokens(token_list), NULL);
	new_node->prev = NULL;
	new_node->next = NULL;
	new_node->token = ft_substr(full_cmd, *start_index, (*i) - (*start_index));
	if (new_node->token == NULL)
		return (clean_tokens(token_list), NULL);
	add_token_identifiers(new_node);
	*start_index = (*i) + 1;
	token_node_add_last(token_list, new_node);
	return (new_node->token);
}

void	set_delimiter(char *delimiter, char *full_cmd, unsigned int i)
{
	if (*delimiter == '\0')
		*delimiter = full_cmd[i];
	else if (*delimiter == full_cmd[i])
		*delimiter = '\0';
}

static void	token_node_add_last(t_token_list **head, t_token_list *node)
{
	t_token_list	*temp;

	if (*head == NULL)
		*head = node;
	else
	{
		temp = *head;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = node;
		node->prev = temp;
	}
}
