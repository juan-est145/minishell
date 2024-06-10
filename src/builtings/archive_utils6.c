/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   archive_utils6.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juestrel <juestrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 17:58:03 by mfuente-          #+#    #+#             */
/*   Updated: 2024/06/10 15:29:39 by juestrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../libft/libft.h"

void	export_help(char **split, t_lst_env **lst_env)
{
	if (split[1] == NULL)
	{
		export_void(lst_env);
		exit(EXIT_SUCCESS);
	}
}

void	cd_process_args_error(char **split)
{
	printf("Too many arguments in cd\n");
	free_matrix(split);
	exit(EXIT_FAILURE);
}

void	cd_parent_cleanup(char *fusion, t_str_aux *aux)
{
	if (fusion != NULL)
		free(fusion);
	if (aux->pwd != NULL)
		free(aux->pwd);
	if (aux->old_pwd != NULL)
		free(aux->old_pwd);
	if (aux->split != NULL)
		free_matrix(aux->split);
}

char	*update_env_cd_parent(t_str_aux aux, t_lst_env **lst_env,
		t_pipex *str_pipes, t_ast *node)
{
	char	*fusion;

	fusion = ft_fusion_string("export PWD=", aux.pwd);
	handle_cd_env(lst_env, fusion, str_pipes, node);
	free(fusion);
	if (aux.old_pwd == NULL)
	{
		unset_parent_process("unset OLDPWD", lst_env);
		return (NULL);
	}
	fusion = ft_fusion_string("export OLDPWD=", aux.old_pwd);
	handle_cd_env(lst_env, fusion, str_pipes, node);
	return (fusion);
}

void	export_loop(char **split, t_lst_env **lst_env)
{
	int			i;
	t_lst_env	*node1;
	char		*new_env;

	i = 0;
	while (split[i])
	{
		if (ft_contain(split[i], '=') == 0 && (ft_strlen(split[i]) > 2))
		{
			if (ft_lst_contain_change(lst_env, split[i]) == 0)
				;
			else
			{
				new_env = ft_substr(split[i], 0, ft_strlen(split[i]));
				node1 = ft_lstnew_ms(new_env);
				ft_lstadd_back_ms(lst_env, node1);
			}
		}
		i++;
	}
}
