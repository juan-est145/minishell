/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfuente- <mfuente-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 11:57:33 by juan-est145       #+#    #+#             */
/*   Updated: 2024/05/01 10:38:35 by mfuente-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../libft/libft.h"

void	read_cmd(t_ast *node, t_lst_env **lst_env, t_ast **head, char *prompt)
{
	if (ft_strncmp(node->args, "pwd\0", 4) == 0 || ft_strncmp(node->args,
			"pwd ", 4) == 0)
		ft_getpwd(node->args);
	if (ft_strncmp(node->args, "echo ", 4) == 0)
		ft_echo(ft_split(node->args, ' '));
	if (ft_strncmp(node->args, "env\0", 4) == 0)
		ft_env(lst_env, node->args);
	if (ft_strncmp(node->args, "export ", 7) == 0)
		ft_export(node->args, lst_env);
	if (ft_strncmp(node->args, "unset ", 6) == 0)
		ft_unset(node->args, lst_env);
	if (ft_strncmp(node->args, "cd", 2) == 0)
		ft_cd(node->args, lst_env);
	if (ft_strncmp(node->args, "exit", 4) == 0)
		ft_exit(head, *lst_env, prompt);
}

void	read_pipe(t_ast *node, t_lst_env *lst_env)
{
	(void)node;
	(void)lst_env;
}
