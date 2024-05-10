/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   archive_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfuente- <mfuente-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 13:59:06 by mfuente-          #+#    #+#             */
/*   Updated: 2024/05/10 14:55:08 by mfuente-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../libft/libft.h"

void	aux(char **matr, char const *s, char c)
{
	size_t	cont_aux;
	size_t	cont_s;
	size_t	cont;

	cont_s = 0;
	cont = 0;
	while (s[cont_s])
	{
		cont_aux = 0;
		while (s[cont_aux + cont_s] != 0 && s[cont_aux + cont_s] != c)
			cont_aux++;
		if (cont_aux > 0)
		{
			matr[cont] = malloc((cont_aux + 1) * sizeof(char));
			if (!matr[cont])
				return (liberar_memoria(matr));
			rellenar(matr[cont], (s + cont_s), c);
			cont++;
			cont_s = cont_s + cont_aux;
		}
		else
			cont_s++;
	}
	matr[cont] = NULL;
}

int	ntimes(char const *s, char c)
{
	int	i;
	int	cont;

	i = 0;
	cont = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c && i != 0 && s[i - 1] != c)
		{
			cont++;
		}
		i++;
	}
	if (s[i - 1] != c)
		cont++;
	return (cont);
}

int	ft_lst_contain_change(t_lst_env **lst, char *search)
{
	t_lst_env	*temp;
	char		*result;
	int			len;
	char		**new;

	new = ft_split(search, '=');
	len = ft_strlen(new[0]);
	temp = *lst;
	while (temp != NULL)
	{
		if (ft_strncmp(temp->text, new[0], len) == 0)
		{
			result = ft_substr(search, 0, ft_strlen(search));
			if (temp->text != NULL)
				free(temp->text);
			temp->text = result;
			free_matrix(new);
			return (0);
		}
		temp = temp->next;
	}
	free_matrix(new);
	return (1);
}

int	ft_lst_contain(t_lst_env **lst, char *search)
{
	t_lst_env	*temp;
	int			len;
	char		**new;

	new = ft_split(search, '=');
	len = ft_strlen(new[0]);
	temp = *lst;
	while (temp->next != NULL)
	{
		if (ft_strncmp(temp->next->text, new[0], len) == 0)
		{
			return (0);
		}
		temp = temp->next;
	}
	return (1);
}

t_lst_env	*ft_lstnew_ms(char *content, char **env)
{
	t_lst_env	*nodo;

	nodo = malloc(sizeof(t_lst_env));
	if (!nodo)
		return (NULL);
	nodo->text = content;
	nodo->env = env;
	nodo->next = NULL;
	return (nodo);
}
