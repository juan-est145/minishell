/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-est145 <juan-est145@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 15:12:37 by juan-est145       #+#    #+#             */
/*   Updated: 2024/04/29 13:19:14 by juan-est145      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../../include/minishell.h"

static t_token_list	*find_tokens(char *full_cmd, t_token_list **token_list);
static char			*save_token(t_token_list **token_list, char *full_cmd,
						unsigned int *start_index, unsigned int *i);
static void			set_delimiter(char *delimiter, char *full_cmd,
						unsigned int i);
static void			token_node_add_last(t_token_list **head,
						t_token_list *node);

t_token_list	*tokenize_cmd(char *full_cmd)
{
	t_token_list	*token_list;

	token_list = NULL;
	if (*full_cmd == '\0')
		return (free(full_cmd), NULL);
	while (ft_isspace(*full_cmd) == true && *full_cmd != '\0')
		full_cmd++;
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
		return (NULL);
	new_node->prev = NULL;
	new_node->next = NULL;
	new_node->token = ft_substr(full_cmd, *start_index, (*i) - (*start_index));
	if (new_node->token == NULL)
		return (NULL);
	add_token_identifiers(new_node);
	*start_index = (*i) + 1;
	token_node_add_last(token_list, new_node);
	return (new_node->token);
}

static void	set_delimiter(char *delimiter, char *full_cmd, unsigned int i)
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
