/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   archive_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:15:43 by user42            #+#    #+#             */
/*   Updated: 2024/04/24 16:55:03 by user42           ###   ########.fr       */
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

// To DO: Fix function
void free_lst_env (t_lst_env *lst)
{
	t_lst_env *temp;
	t_lst_env *aux;

	temp = lst;
	while (temp->next != NULL)
	{
		free(temp->next->text);
		aux = temp;
		temp = temp->next;
		free(aux);
	}
}
int ft_strlen(const char *s)
{
    int i = 0;

    while(s[i] != '\0')
        i++;
    return(i);
}
int ft_contain(char *text, char search)
{
	int i = 0;

	while (text[i])
	{
		if (text[i] == search)
			return (0);
		i++;
	}
	return (1);
}



void	ft_lstadd_back(t_lst_env **lst, t_lst_env *new)
{
	t_lst_env	*temp;

	if (!*lst)
		*lst = new;
	else
	{
		temp = *lst;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}
//	printf("%s\n", temp->next->text);
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

char	**ft_split(char const *s, char c)
{
	char	**final;
	int		palabras;

	if (s == NULL)
		return (NULL);
	palabras = ntimes(s, c);
	final = (char **)malloc((palabras + 1) * sizeof(char *));
	if (!final)
		return (NULL);
	aux(final, s, c);
	return (final);
}


char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*final;
	int		len;
	int		cont;
	int		lentotal;

	cont = 0;
	lentotal = ft_strlen(s1) + ft_strlen(s2) + 1;
	final = (char *)malloc(lentotal * sizeof(char));
	if (!final || !s1 || !s2)
		return (0);
	len = ft_strlen(s1);
	while (len--)
	{
		final[cont] = *s1++;
		cont++;
	}
	len = ft_strlen(s2);
	while (len--)
	{
		final[cont] = *s2++;
		cont++;
	}
	final[cont] = '\0';
	return (final);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int	cont;

	cont = 0;
	while ((s1[cont] != '\0' || s2[cont] != '\0') && 0 < n)
	{
		if (s1[cont] != s2[cont])
			return ((unsigned char)s1[cont] - (unsigned char)s2[cont]);
		cont++;
		n--;
	}
	return (0);
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