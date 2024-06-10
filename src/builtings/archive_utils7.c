/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   archive_utils7.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juestrel <juestrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 14:33:49 by juestrel          #+#    #+#             */
/*   Updated: 2024/06/10 14:34:03 by juestrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../libft/libft.h"

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
