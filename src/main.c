/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-est145 <juan-est145@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:38:24 by user42            #+#    #+#             */
/*   Updated: 2024/04/26 12:28:01 by juan-est145      ###   ########.fr       */
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
	return (node);
}

/*if (ft_strncmp(text, "pwd\0", 4) == 0 || ft_strncmp(text, "pwd ", 4) == 0)
			ft_getpwd(text, &lst_env);
		if (ft_strncmp(text, "echo ", 4) == 0)
			ft_echo(ft_split(text, ' '));
		if (ft_strncmp(text, "env\0", 4) == 0)
			ft_env(&lst_env, text);
		if (ft_strncmp(text, "export ", 7) == 0)
			ft_export(text, &lst_env);
		if (ft_strncmp(text, "unset ", 6) == 0)
			ft_unset(text, &lst_env);
		if (ft_strncmp(text, "cd ", 3) == 0)
			ft_cd(text, &lst_env);
		if(ft_strncmp(text, "exit", 4) == 0)
		{
			flag = true;
		}*/