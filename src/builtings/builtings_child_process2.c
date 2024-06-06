/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtings_child_process2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juestrel <juestrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 18:52:55 by juestrel          #+#    #+#             */
/*   Updated: 2024/06/06 12:46:09 by juestrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../libft/libft.h"

void	export_process(char *new, t_lst_env **lst_env)
{
	t_lst_env	*node;
	char		*new_env;
	char		**split;
	int			i;

	i = 0;
	split = ft_split(new, ' ');
	while (split[i])
	{
		if (ft_contain(split[i], '=') == 0 && (ft_strlen(split[i]) > 2))
		{
			if (ft_lst_contain_change(lst_env, split[i]) == 0)
				;
			else
			{
				new_env = ft_substr(split[i], 0, ft_strlen(split[i]));
				node = ft_lstnew_ms(new_env);
				ft_lstadd_back_ms(lst_env, node);
			}
		}
		i++;
	}
	free_matrix(split);
	exit(EXIT_SUCCESS);
}

void	export_parent_process(char *new, t_lst_env **lst_env)
{
	t_lst_env	*node;
	char		*new_env;
	char		**split;
	int			i;

	i = 0;
	split = ft_split(new, ' ');
	while (split[i])
	{
		if (ft_contain(split[i], '=') == 0 && (ft_strlen(split[i]) > 2))
		{
			if (ft_lst_contain_change(lst_env, split[i]) == 0)
				;
			else
			{
				new_env = ft_substr(split[i], 0, ft_strlen(split[i]));
				node = ft_lstnew_ms(new_env);
				ft_lstadd_back_ms(lst_env, node);
			}
		}
		i++;
	}
	free_matrix(split);
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
}

void	exit_process(t_ast **head, t_lst_env *lst_env, char *prompt)
{
	clean_ast(*head);
	rl_clear_history();
	free_copie_env(&lst_env);
	free_lst_env(lst_env);
	free(prompt);
	exit(EXIT_SUCCESS);
}
