/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-est145 <juan-est145@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:38:24 by user42            #+#    #+#             */
/*   Updated: 2024/04/30 17:59:18 by juan-est145      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"

static void		read_input(char *prompt, t_lst_env **lst_env);
static t_ast	*execute_ast(t_ast *node, t_lst_env **lst_env, char *prompt,
					t_ast **head);

int	main(int argc, char **argv, char **env)
{
	t_lst_env	*lst_env;
	int			i;
	char		*prompt;

	(void)argc;
	(void)argv;
	i = 0;
	prompt = ft_getenv(env, "LOGNAME=");
	prompt = ft_strjoin(prompt, "$ ");
	while (i++ < 1500)
		printf("\n");
	lst_env = init_lst_env(env);
	if (lst_env == NULL)
		return (1);
	read_input(prompt, &lst_env);
	free_lst_env(lst_env);
	free(prompt);
	return (0);
}

static void	read_input(char *prompt, t_lst_env **lst_env)
{
	char			*text;
	t_token_list	*head;
	t_ast			*ast_head;

	while (1)
	{
		text = readline(prompt);
		add_history(text);
		if (*text == '\0')
		{
			printf("You need to enter a command\n");
			free(text);
			continue ;
		}
		head = tokenize_cmd(text);
		if (head == NULL)
			error_msgs(TOKEN_MALLOC_FAILURE);
		free(text);
		ast_head = create_ast(&head);
		if (ast_head == NULL)
			error_msgs(AST_MALLOC_FAILURE);
		clean_tokens(&head);
		execute_ast(ast_head, lst_env, prompt, &ast_head);
		clean_ast(ast_head);
	}
}

static t_ast	*execute_ast(t_ast *node, t_lst_env **lst_env, char *prompt,
		t_ast **head)
{
	if (node == NULL)
		return (NULL);
	else if (node->parse_identifier == PARSE_CMD)
		return (read_cmd(node, lst_env, head, prompt), node);
	else if (node->parse_identifier == PARSE_PIPE
		&& node->left->parse_identifier == PARSE_CMD
		&& node->right->parse_identifier == PARSE_CMD)
		return (read_pipe(node, *lst_env), node);
	execute_ast(node->left, lst_env, prompt, head);
	execute_ast(node->right, lst_env, prompt, head);
	return (node);
}

// Perhaps there should be another if to check that
// if the current node is a pipe, i'ts left node
// is also a pipe but right node is a cmd, it should
// perhaps only traverse to the left node and then execute
// the right node. Will need to check once we start using
// real pipes
