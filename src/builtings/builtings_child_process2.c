/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtings_child_process2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juestrel <juestrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 18:52:55 by juestrel          #+#    #+#             */
/*   Updated: 2024/06/24 14:21:44 by juestrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../libft/libft.h"

void	export_process(t_ast *node, t_lst_env **lst_env, t_pipex *str_pipe,
		t_process_cmd type_cmd)
{
	char	**split;
	int		fd;

	split = ft_split(node->args, ' ');
	fd = redirect_stdout(node, str_pipe, type_cmd);
	export_help(split, lst_env);
	export_loop(split, lst_env);
	free_matrix(split);
	close(fd);
	exit(EXIT_SUCCESS);
}

void	export_parent_process(t_ast *node, t_lst_env **lst_env,
		t_pipex *str_pipe, t_process_cmd type_cmd)
{
	char	**split;
	int		fd;

	split = ft_split(node->args, ' ');
	fd = redirect_stdout(node, str_pipe, type_cmd);
	if (split[1] == NULL)
		export_void(lst_env);
	else
		export_loop(split, lst_env);
	dup2(0, STDOUT_FILENO);
	free_matrix(split);
	(void)fd;
}

void	unset_process(char *text, t_lst_env **lst_env)
{
	t_lst_env	*temp;
	t_lst_env	*previous;
	bool		flag;
	char		**split;

	flag = false;
	split = ft_split(text, ' ');
	is_first(text, lst_env);
	temp = *lst_env;
	previous = temp;
	while (temp != NULL)
	{
		flag = ft_unset_normi2(split, previous, flag, &temp);
		if (flag == true)
			break ;
		previous = temp;
		temp = temp->next;
	}
	free_matrix(split);
	exit(EXIT_SUCCESS);
}

void	unset_parent_process(char *text, t_lst_env **lst_env)
{
	t_lst_env		*temp;
	t_lst_env		*previous;
	t_unset_flags	flag;
	char			**split;

	flag = NEUTRAL;
	split = ft_split(text, ' ');
	is_first(text, lst_env);
	temp = *lst_env;
	previous = temp;
	while (temp != NULL)
	{
		flag = ft_unset_normi2(split, previous, flag, &temp);
		if (flag == BREAK)
			break ;
		if (flag == REPEAT_NODE)
			flag = NEUTRAL;
		else
		{
			previous = temp;
			temp = temp->next;
		}
	}
	free_matrix(split);
}

void	exit_process(t_ast **head, t_lst_env *lst_env, char *prompt)
{
	char	**split;
	int		exit_value;

	split = ft_split((*head)->args, ' ');
	exit_cleanup(head, lst_env, prompt);
	if (split == NULL)
		exit(EXIT_FAILURE);
	if (split[1] == NULL)
	{
		free_matrix(split);
		exit(EXIT_SUCCESS);
	}
	exit_value = 2;
	if (is_num(split) == true && split[2] == NULL)
		exit_value = ft_atoi(split[1]);
	free_matrix(split);
	exit(exit_value);
}
