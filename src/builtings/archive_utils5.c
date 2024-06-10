/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   archive_utils5.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juestrel <juestrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 12:02:46 by mfuente-          #+#    #+#             */
/*   Updated: 2024/06/10 14:34:18 by juestrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../libft/libft.h"

static char	**order_matrix(char **order_env);
static char	**create_matrix_env(char **order_env, int size_env,
				t_lst_env *temp);

void	ft_echo_hd_normi(bool open, int fd, char delimiter)
{
	char	line[1];

	if (open == true)
	{
		fd = here_doc_echo(delimiter);
		printf("\n");
		while (read(fd, line, 1) > 0)
		{
			write(1, line, 1);
		}
		close(fd);
	}
}

void	pwd_null_error(void)
{
	printf("Error obtaining PWD\n");
	exit(EXIT_FAILURE);
}

void	export_void(t_lst_env **lst_env)
{
	int			i;
	int			size_env;
	char		**order_env;
	t_lst_env	*temp;

	temp = *lst_env;
	size_env = ft_lstsize_ms(*lst_env);
	order_env = malloc((size_env + 1) * sizeof(char *));
	if (!order_env)
	{
		free(order_env);
		error_msgs(TOKEN_MALLOC_FAILURE);
	}
	order_env = create_matrix_env(order_env, size_env, temp);
	order_env = order_matrix(order_env);
	i = 0;
	while (order_env[i] != NULL)
	{
		printf("declare -x %s\n", order_env[i]);
		i++;
	}
	free(order_env);
}

static char	**order_matrix(char **order_env)
{
	int		i;
	int		j;
	char	*aux;

	i = 0;
	while (order_env[i] != NULL)
	{
		j = 0;
		while (order_env[j + 1] != NULL)
		{
			if (order_env[j][0] > order_env[j + 1][0])
			{
				aux = order_env[j];
				order_env[j] = order_env[j + 1];
				order_env[j + 1] = aux;
			}
			else
				j++;
		}
		i++;
	}
	return (order_env);
}

static char	**create_matrix_env(char **order_env, int size_env, t_lst_env *temp)
{
	int	i;

	i = 0;
	while (i < size_env)
	{
		order_env[i] = temp->text;
		temp = temp->next;
		i++;
	}
	order_env[i] = NULL;
	return (order_env);
}
