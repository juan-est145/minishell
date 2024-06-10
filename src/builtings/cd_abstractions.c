/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_abstractions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juestrel <juestrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 16:18:43 by juestrel          #+#    #+#             */
/*   Updated: 2024/06/10 15:42:36 by juestrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../libft/libft.h"

int	cd_too_many_arguments(char **split, t_pipex *str_pipes)
{
	if (split != NULL)
		free_matrix(split);
	printf("Too many arguments in cd\n");
	str_pipes->return_cmd_status = 1;
	return (1);
}

int	old_pwd_failure(t_pipex *str_pipes)
{
	printf("Cannot change directory\n");
	str_pipes->return_cmd_status = 1;
	return (1);
}

int	clean_pwds(t_str_aux aux, t_pipex *str_pipes)
{
	str_pipes->return_cmd_status = 1;
	if (aux.old_pwd != NULL)
		free(aux.old_pwd);
	if (aux.pwd != NULL)
		free(aux.pwd);
	return (1);
}
