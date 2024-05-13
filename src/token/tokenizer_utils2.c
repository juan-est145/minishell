/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-est145 <juan-est145@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 19:46:34 by juan-est145       #+#    #+#             */
/*   Updated: 2024/05/13 18:11:57 by juan-est145      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../libft/libft.h"

static void	find_env_var(char *text, t_lst_env **lst_env);
static char	set_env_delimiter(char delimiter);
static char	*process_env(char *text, unsigned int env_i, t_lst_env **lst_env);

void	delete_empty_nodes(t_token_list *head)
{
	t_token_list	*previous;
	t_token_list	*temp;

	temp = NULL;
	while (head != NULL)
	{
		previous = head->prev;
		if (*head->token == '\0')
		{
			previous->next = head->next;
			if (head->next != NULL)
				head->next->prev = previous;
			temp = head;
			head = head->next;
			free(temp->token);
			free(temp);
			temp = NULL;
			continue ;
		}
		head = head->next;
	}
}

void	expand_variables(t_token_list **head, t_lst_env **lst_env)
{
	t_token_list	*temp;

	temp = *head;
	while (temp != NULL)
	{
		if (temp->token_identifer == EXPRESSION)
			find_env_var(temp->token, lst_env);
		temp = temp->next;
	}
}

static void	find_env_var(char *text, t_lst_env **lst_env)
{
	unsigned int	i;
	char			delimiter;

	i = 0;
	delimiter = '\0';
	while (text[i] != '\0')
	{
		if (text[i] == '\'')
			delimiter = set_env_delimiter(delimiter);
		if (text[i] == '$' && ft_isspace(text[i + 1]) \
		== false && text[i + 1] != '\0' && delimiter == '\0')
			process_env(text, i, lst_env);
		i++;
	}
}

static char	set_env_delimiter(char delimiter)
{
	if (delimiter == '\0')
		return ('\'');
	return ('\0');
}

static char	*process_env(char *text, unsigned int env_i, t_lst_env **lst_env)
{
	unsigned int	i;
	char			*env;

	i = env_i;
	while (text[i] != '\0' && ft_isspace(text[i]) == false)
		i++;
	env = ft_substr(text, 0, i - env_i);
	(void)lst_env;
	return (env);
}
