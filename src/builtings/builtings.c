/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtings.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juestrel <juestrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:08:25 by juestrel          #+#    #+#             */
/*   Updated: 2024/05/30 18:27:16 by juestrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../libft/libft.h"

// IMITA EL COMANDO ENV
pid_t	ft_env(t_lst_env **lst_env, t_ast *node, int fd_pipe[2],
		t_process_cmd cmd_type)
{
	pid_t	pid;

	pid = fork();
	if (pid == CHILD)
		env_process(lst_env, node, fd_pipe, cmd_type);
	return (pid);
}

// IMITA EL COMANDO EXPORT
void	ft_export(char *new, t_lst_env **lst_env)
{
	t_lst_env	*node;
	char		*new_env;
	char		**split;
	int			i;

	// TO DO: CHECK EXPORT WITH PIPES, SEE WHAT HAPPENS
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

static bool	ft_unset_normi2(char **split, t_lst_env *previous, bool flag,
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

void	ft_unset(char *text, t_lst_env **lst_env)
{
	t_lst_env	*temp;
	t_lst_env	*previous;
	bool		flag;
	char		**split;

	// TO DO: CHECK UNSET WITH PIPES, SEE WHAT HAPPENS
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
