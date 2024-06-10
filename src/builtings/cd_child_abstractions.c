/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_child_abstractions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juestrel <juestrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 17:41:02 by juestrel          #+#    #+#             */
/*   Updated: 2024/06/10 14:47:14 by juestrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../libft/libft.h"

/*void	cd_process_continue(t_pipex *str_pipes, t_lst_env **lst_env,
		char **split)
{
	char	*old_pwd;
	char	*pwd;

	old_pwd = getcwd(NULL, 0);
	if (old_pwd == NULL)
		error_msgs(PWD_ERROR);
	if (split[1] == NULL)
		cd_no_argument(old_pwd, split, lst_env, str_pipes);
	else
	{
		if (errors_cd(old_pwd, split, split, "Could not access directory") == 1)
			exit(EXIT_FAILURE);
		pwd = getcwd(NULL, 0);
		if (pwd == NULL)
			error_msgs(PWD_ERROR);
		handle_cd_env(lst_env, "PIPES", pwd, str_pipes);
	}
	handle_cd_env(lst_env, "PIPES", old_pwd, str_pipes);
}*/
