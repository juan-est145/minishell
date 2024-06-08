/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtings.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juestrel <juestrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:08:25 by juestrel          #+#    #+#             */
/*   Updated: 2024/06/08 15:32:06 by juestrel         ###   ########.fr       */
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
	if (pid == -1)
	{
		printf("Error creating child process, exiting\n");
		free_lst_env(*lst_env);
		clean_ast(str_pipe->ast_head);
		exit(EXIT_FAILURE);
	}
	if (pid == CHILD)
		env_process(lst_env, node, str_pipe, cmd_type);
	if (cmd_type == SIMPLE_CMD)
		wait_pid_return_status(pid, str_pipe);
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
	if (pid == -1)
	{
		printf("Error creating child process, exiting\n");
		free_lst_env(*lst_env);
		clean_ast(str_pipe->ast_head);
		exit(EXIT_FAILURE);
	}
	if (pid == CHILD)
		export_process(new, lst_env);
	free_copie_env(str_pipe->lst_env);
	up_env(str_pipe->lst_env);
	return (pid);
}

// IMITA EL COMANDO UNSET
t_unset_flags	ft_unset_normi(t_lst_env **temp, t_unset_flags flag,
		t_lst_env *previous)
{
	t_lst_env	*aux;

	if ((*temp)->next != NULL)
	{
		aux = *temp;
		previous->next = (*temp)->next;
		free(aux->text);
		free(aux);
		flag = REPEAT_NODE;
	}
	else
	{
		aux = *temp;
		previous->next = NULL;
		free(aux->text);
		free(aux);
		flag = BREAK;
	}
	*temp = previous->next;
	return (flag);
}

t_unset_flags	ft_unset_normi2(char **split, t_lst_env *previous,
		t_unset_flags flag, t_lst_env **temp)
{
	int		i;
	char	**name;

	i = 1;
	name = ft_split((*temp)->text, '=');
	while (split[i])
	{
		if (found_env(name[0], split[i]) == true)
		{
			flag = ft_unset_normi(temp, flag, previous);
			if (flag == BREAK)
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
	if (pid == -1)
	{
		printf("Error creating child process, exiting\n");
		free_lst_env(*lst_env);
		exit(EXIT_FAILURE);
	}
	if (pid == CHILD)
		unset_process(text, lst_env);
	free_copie_env(lst_env);
	up_env(lst_env);
	return (pid);
}
