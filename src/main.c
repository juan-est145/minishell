/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-est145 <juan-est145@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:04:01 by juestrel          #+#    #+#             */
/*   Updated: 2024/05/24 14:26:21 by juan-est145      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"

static void			read_input(char *prompt, t_lst_env **lst_env);
static bool			is_input_empty(char *text);
static t_token_list	*start_token_list(char *text, t_lst_env **lst_env);
static t_ast		*execute_ast(t_ast *node, char *prompt, t_pipex *str_pipe);

int	main(int argc, char **argv, char **env)
{
	t_lst_env	*lst_env;
	char		*prompt;

	(void)argc;
	(void)argv;
	lst_env = init_lst_env(env);
	up_env(&lst_env);
	prepare_signals();
	if (lst_env == NULL)
		return (1);
	prompt = initial_print(env);
	read_input(prompt, &lst_env);
	return (0);
}

static void	read_input(char *prompt, t_lst_env **lst_env)
{
	char			*text;
	t_token_list	*head;
	t_pipex			str_pipe;
	bool			syntax_error;

	str_pipe.lst_env = lst_env;
	while (1)
	{
		syntax_error = false;
		text = readline(prompt);
		if (text == NULL)
			exit(0);
		add_history(text);
		if (is_input_empty(text) == true)
			continue ;
		head = start_token_list(text, lst_env);
		if (head == NULL)
			continue ;
		str_pipe.ast_head = create_ast(&head, &syntax_error);
		if (syntax_error == true)
			continue ;
		if (str_pipe.ast_head == NULL && errno == ENOMEM)
			error_msgs(AST_MALLOC_FAILURE);
		execute_ast(str_pipe.ast_head, prompt, &str_pipe);
		clean_ast(str_pipe.ast_head);
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

static t_token_list	*start_token_list(char *text, t_lst_env **lst_env)
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
	expand_variables(&head, lst_env);
	return (head);
}

static t_ast	*execute_ast(t_ast *node, char *prompt, t_pipex *str_pipe)
{
	if (node == NULL)
		return (NULL);
	else if (node->parse_identifier == PARSE_CMD)
		return (read_cmd(node, str_pipe, prompt), node);
	else if (node->parse_identifier == PARSE_PIPE
		&& node->left->parse_identifier == PARSE_CMD
		&& node->right->parse_identifier == PARSE_CMD)
		return (read_pipe(node, str_pipe->lst_env, str_pipe), node);
	execute_ast(node->left, prompt, str_pipe);
	execute_ast(node->right, prompt, str_pipe);
	return (node);
}

// Perhaps there should be another if to check that
// if the current node is a pipe, i'ts left node
// is also a pipe but right node is a cmd, it should
// perhaps only traverse to the left node and then execute
// the right node. Will need to check once we start using
// real pipes
