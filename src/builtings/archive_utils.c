/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   archive_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-est145 <juan-est145@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:15:43 by user42            #+#    #+#             */
/*   Updated: 2024/04/29 17:28:09 by juan-est145      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../libft/libft.h"

//---------------UTILS----------------------//
void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i] != NULL)
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

// To DO: Fix function | HECHO
void	free_lst_env(t_lst_env *lst)
{
	t_lst_env	*temp;

	while (lst != NULL)
	{
		if (lst->text != NULL)
			free(lst->text);
		temp = lst;
		lst = lst->next;
		free(temp);
	}
}

int	ft_contain(char *text, char search)
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
