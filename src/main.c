/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfuente- <mfuente-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:38:24 by user42            #+#    #+#             */
/*   Updated: 2024/05/08 12:10:10 by mfuente-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"

static void			read_input(char *prompt, t_lst_env **lst_env);
static bool			is_input_empty(char *text);
static t_token_list	*start_token_list(char *text);
static t_ast		*execute_ast(t_ast *node, t_lst_env **lst_env, char *prompt,
						t_ast **head);

int	main(int argc, char **argv, char **env)
{
	t_lst_env	*lst_env;
	int			i;
	char		*prompt;
	char		*color_prompt;

	(void)argc;
	(void)argv;
	i = 0;
	prompt = ft_getenv(env, "LOGNAME=");
	prompt = ft_strjoin(prompt, "$ ");
	color_prompt = ft_strjoin(GREEN, prompt);
	free(prompt);
	prompt = ft_strjoin(color_prompt, RESET);
	free(color_prompt);
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
	bool			syntax_error;

	while (1)
	{
		syntax_error = false;
		text = readline(prompt);
		add_history(text);
		if (is_input_empty(text) == true)
			continue ;
		head = start_token_list(text);
		if (head == NULL)
			continue ;
		ast_head = create_ast(&head, &syntax_error);
		if (syntax_error == true)
			continue ;
		if (ast_head == NULL && errno == ENOMEM)
			error_msgs(AST_MALLOC_FAILURE);
		execute_ast(ast_head, lst_env, prompt, &ast_head);
		clean_ast(ast_head);
	}
}

static bool	is_input_empty(char *text)
{
	if (*text == '\0')
	{
		printf("You need to enter a command\n");
		free(text);
		return (true);
	}
	return (false);
}

static t_token_list	*start_token_list(char *text)
{
	t_token_list	*head;

	head = tokenize_cmd(text);
	if (head == NULL)
		error_msgs(TOKEN_MALLOC_FAILURE);
	free(text);
	if (*head->token == '\0' && head->next == NULL)
		return (clean_tokens(&head), printf("Syntax error\n"), NULL);
	delete_empty_nodes(head);
	if (tokens_syntax_correct(head) == false)
		return (clean_tokens(&head), printf("Syntax error\n"), NULL);
	return (head);
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
		return (read_pipe(node, lst_env), node);
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
