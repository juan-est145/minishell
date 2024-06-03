/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtings.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juestrel <juestrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:08:25 by juestrel          #+#    #+#             */
/*   Updated: 2024/06/03 18:39:48 by juestrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../libft/libft.h"

// IMITA EL COMANDO ENV
pid_t	ft_env(t_lst_env **lst_env, t_ast *node, t_pipex *str_pipe,
		t_process_cmd cmd_type)
{
	pid_t	pid;

	pid = fork();
	if (pid == CHILD)
		env_process(lst_env, node, str_pipe, cmd_type);
	if (cmd_type == SIMPLE_CMD)
		waitpid(pid, NULL, 0);
	return (pid);
}

// IMITA EL COMANDO EXPORT
pid_t	ft_export(char *new, t_lst_env **lst_env, t_pipex *str_pipe,
		t_process_cmd type_cmd)
{
	pid_t	pid;

	pid = -1;
	if (type_cmd == SIMPLE_CMD)
	{
		export_parent_process(new, lst_env);
		free_copie_env(str_pipe->lst_env);
		up_env(str_pipe->lst_env);
		return (pid);
	}
	pid = fork();
	if (pid == CHILD)
		export_process(new, lst_env);
	free_copie_env(str_pipe->lst_env);
	up_env(str_pipe->lst_env);
	return (pid);
}

// IMITA EL COMANDO UNSET
bool	ft_unset_normi(t_lst_env **temp, bool flag, t_lst_env *previous)
{
	t_lst_env	*aux;

	if ((*temp)->next != NULL)
	{
		aux = *temp;
		previous->next = (*temp)->next;
		free(aux->text);
		free(aux);
	}
	else
	{
		aux = *temp;
		previous->next = NULL;
		free(aux->text);
		free(aux);
		flag = true;
		return (flag);
	}
	*temp = previous->next;
	return (flag);
}

bool	ft_unset_normi2(char **split, t_lst_env *previous, bool flag,
		t_lst_env **temp)
{
	int		i;
	char	**name;

	i = 1;
	name = ft_split((*temp)->text, '=');
	while (split[i])
	{
		if (ft_strncmp(name[0], split[i], ft_strlen(name[0])) == 0)
		{
			flag = ft_unset_normi(temp, flag, previous);
			if (flag == true)
				break ;
		}
		i++;
	}
	free_matrix(name);
	return (flag);
}

pid_t	ft_unset(char *text, t_lst_env **lst_env, t_process_cmd type_cmd)
{
	pid_t	pid;

	pid = -1;
	if (type_cmd == SIMPLE_CMD)
	{
		unset_parent_process(text, lst_env);
		free_copie_env(lst_env);
		up_env(lst_env);
		return (pid);
	}
	pid = fork();
	if (pid == CHILD)
		unset_process(text, lst_env);
	free_copie_env(lst_env);
	up_env(lst_env);
	return (pid);
}
