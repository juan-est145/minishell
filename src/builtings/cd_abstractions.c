/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_abstractions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juestrel <juestrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 16:18:43 by juestrel          #+#    #+#             */
/*   Updated: 2024/06/07 17:21:38 by juestrel         ###   ########.fr       */
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

void	update_env(t_lst_env **lst_env, t_pipex *str_pipes, char *pwd,
		char *old_pwd)
{
	handle_cd_env(lst_env, "export PWD=", pwd, str_pipes);
	if (old_pwd == NULL)
		unset_parent_process("unset OLDPWD", lst_env);
	else
		handle_cd_env(lst_env, "export OLDPWD=", old_pwd, str_pipes);
}

int	old_pwd_failure(t_pipex *str_pipes)
{
	printf("Cannot change directory\n");
	str_pipes->return_cmd_status = 1;
	return (1);
}
