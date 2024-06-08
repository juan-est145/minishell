/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   archive_utils5.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juestrel <juestrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 12:02:46 by mfuente-          #+#    #+#             */
/*   Updated: 2024/06/08 16:09:39 by juestrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../libft/libft.h"

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

bool	found_env(char *env, char *env_to_remove)
{
	if (ft_strlen(env) == ft_strlen(env_to_remove) && ft_strncmp(env,
			env_to_remove, ft_strlen(env)) == 0)
		return (true);
	return (false);
}

bool	is_num(char **split)
{
	int		i;
	bool	flag;

	i = 0;
	flag = true;
	while (split[1][i] != '\0')
	{
		if (ft_isdigit(split[1][i]) == 0)
			flag = false;
		i++;
	}
	return (flag);
}

void	exit_cleanup(t_ast **head, t_lst_env *lst_env, char *prompt)
{
	clean_ast(*head);
	rl_clear_history();
	free_copie_env(&lst_env);
	free_lst_env(lst_env);
	free(prompt);
}
