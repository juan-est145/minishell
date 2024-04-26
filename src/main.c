/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfuente- <mfuente-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:38:24 by user42            #+#    #+#             */
/*   Updated: 2024/04/26 17:26:48 by mfuente-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"

static void		read_input(char *prompt, t_lst_env *lst_env);
static t_ast	*execute_ast(t_ast *node, t_lst_env *lst_env);

int	main(int argc, char **argv, char **env)
{
	t_lst_env	lst_env;
	int			i;
	char		*prompt;

	(void)argc;
	(void)argv;
	i = 0;
	prompt = ft_getenv(env, "LOGNAME=");
	prompt = ft_strjoin(prompt, "$ ");
	while (i++ < 1500)
		printf("\n");
	init_lst_env(env, &lst_env);
	read_input(prompt, &lst_env);
	free_lst_env(&lst_env);
	free(prompt);
	return (0);
}

static void	read_input(char *prompt, t_lst_env *lst_env)
{
	bool			flag;
	char			*text;
	t_token_list	*head;
	t_ast			*ast_head;

	flag = false;
	while (flag == false)
	{
		text = readline(prompt);
		add_history(text);
		head = tokenize_cmd(text);
		ast_head = create_ast(&head);
		execute_ast(ast_head, lst_env);
		clean_tokens(&head);
		clean_ast(ast_head);
		free(text);
	}
}

static t_ast	*execute_ast(t_ast *node, t_lst_env *lst_env)
{
	if (node == NULL)
		return (NULL);
	else if (node->parse_identifier == PARSE_CMD)
		return (read_cmd(node, lst_env), node);
	else if (node->parse_identifier == PARSE_PIPE
		&& node->left->parse_identifier == PARSE_CMD
		&& node->right->parse_identifier == PARSE_CMD)
		return (read_pipe(node, lst_env), node);
	execute_ast(node->left, lst_env);
	execute_ast(node->right, lst_env);
	return (node);
}

//Perhaps there should be another if to check that
// if the current node is a pipe, i'ts left node
// is also a pipe but right node is a cmd, it should
// perhaps only traverse to the left node and then execute
// the right node. Will need to check once we start using
// real pipes
