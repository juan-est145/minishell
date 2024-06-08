/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   archive_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juestrel <juestrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:07:35 by juestrel          #+#    #+#             */
/*   Updated: 2024/06/08 16:44:45 by juestrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../libft/libft.h"

int	srch_path(char **env, char *search)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(search, env[i], 5) == 0)
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_getenv(char **env, char *search)
{
	char	*result;
	int		i;
	int		env_index;

	i = 0;
	if (env == NULL)
		return (NULL);
	while (search[i] != '\0')
		i++;
	env_index = srch_path(env, search);
	if (env_index == -1)
		return (NULL);
	result = env[env_index] + i;
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
