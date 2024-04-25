/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   archive_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfuente- <mfuente-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:13:48 by user42            #+#    #+#             */
/*   Updated: 2024/04/25 17:10:31 by mfuente-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../../include/minishell.h"

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

//INIZIALIZA LA LISTA DE VARIABLES GLOBALES
void	init_lst_env(char **env, t_lst_env *lst)
{
	t_lst_env	*aux;
	int			i;

	i = 0;
	while (env[i])
	{
		aux = ft_lstnew_ms(env[i]);
		ft_lstadd_back_ms(&lst, aux);
		i++;
	}
}

char	*ft_fusion_string(char *s1, char *s2)
{
	char	*result;
	int		len_total;
	int		i;
	int		j;

	len_total = ft_strlen(s1) + ft_strlen(s2);
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
