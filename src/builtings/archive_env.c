/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   archive_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-est145 <juan-est145@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:13:48 by user42            #+#    #+#             */
/*   Updated: 2024/04/29 17:27:44 by juan-est145      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../libft/libft.h"

int	srch_path(char **env, char *search)
{
	int	i;

	i = 0;
	while (ft_strncmp(search, env[i], 5) != 0)
	{
		i++;
	}
	return (i);
}

char	*ft_getenv(char **env, char *search)
{
	char	*result;
	int		i;

	i = 0;
	while (search[i] != '\0')
		i++;
	result = env[srch_path(env, search)] + i;
	return (result);
}

// INIZIALIZA LA LISTA DE VARIABLES GLOBALES
t_lst_env	*init_lst_env(char **env)
{
	t_lst_env	*node;
	t_lst_env	*head;
	char		*content;
	int			i;

	i = 0;
	head = NULL;
	while (env[i])
	{
		content = ft_substr(env[i], 0, ft_strlen(env[i]));
		node = ft_lstnew_ms(content);
		if (content == NULL || node == NULL)
			return (free_lst_env(head), NULL);
		ft_lstadd_back_ms(&head, node);
		i++;
	}
	return (head);
}

char	*ft_fusion_string(char *s1, char *s2)
{
	char	*result;
	int		len_total;
	int		i;
	int		j;

	len_total = ft_strlen(s1) + ft_strlen(s2) + 1;
	result = malloc(sizeof(char) * len_total);
	i = 0;
	while (s1[i])
	{
		result[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		result[i] = s2[j];
		i++;
		j++;
	}
	result[i] = '\0';
	return (result);
}
