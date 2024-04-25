/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   archive_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-est145 <juan-est145@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:15:43 by user42            #+#    #+#             */
/*   Updated: 2024/04/25 12:01:16 by juan-est145      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../../include/minishell.h"

//---------------UTILS----------------------//
void free_matrix(char **matrix)
{
	int i;

	i = 0;
	while (matrix[i] != NULL)
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

// To DO: Fix function | HECHO
void free_lst_env (t_lst_env *lst)
{
	t_lst_env *temp;

	while (lst->next != NULL)
	{
		free(lst->next->text);
		temp = lst;
		lst = lst->next;
		free(temp);
	}
}

int ft_contain(char *text, char search)
{
	int	i;

	i = 0;
	while (text[i])
	{
		if (text[i] == search)
			return (0);
		i++;
	}
	return (1);
}

void	liberar_memoria(char **matr)
{
	int	i;

	i = 0;
	if (matr == NULL)
		return ;
	while (matr[i] != NULL)
	{
		free(matr[i]);
		i++;
	}
	free(matr);
}

void	rellenar(char *palabra, char const *frase, char c)
{
	int	i;

	i = 0;
	while (frase[i] != 0 && frase[i] != c)
	{
		palabra[i] = frase[i];
		i++;
	}
	palabra[i] = '\0';
}

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

int ft_lst_contain_change(t_lst_env **lst, char *search)
{
	t_lst_env	*temp;
	int 		len;
	char		**new;

	new = ft_split(search, '=');
	len = ft_strlen(new[0]);
	temp = *lst;
 	while (temp->next != NULL)
	{
		if (ft_strncmp(temp->next->text, new[0], len) == 0)
		{
			temp->next->text = search;
			free_matrix(new);
			return (0);
		}
		temp = temp->next;
	}
	free_matrix(new);
	return (1);	
}

int ft_lst_contain(t_lst_env **lst, char *search)
{
	t_lst_env	*temp;
	int 		len;
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
t_lst_env	*ft_lstnew_ms(char *content)
{
	t_lst_env	*nodo;

	nodo = malloc(sizeof(t_lst_env));
	if (!nodo)
		return (0);
	nodo->text = content;
	nodo->next = 0;
	return (nodo);
}
