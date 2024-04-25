/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfuente- <mfuente-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:38:24 by user42            #+#    #+#             */
/*   Updated: 2024/04/25 19:03:46 by mfuente-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../include/minishell.h"

static void read_input(char *prompt);

int main (int argc, char **argv, char **env)
{
    (void)argc;
    (void)argv;
    t_lst_env lst_env;
    
    int i = 0;
    char *prompt = ft_getenv(env, "LOGNAME=");
    prompt = ft_strjoin(prompt, "$ ");
    while (i++ < 1500)
		printf("\n");
	init_lst_env(env, &lst_env);
    read_input(prompt);
	free_lst_env (&lst_env);
	free(prompt);
    return(0);
}

static void read_input(char *prompt)
{
    bool flag;
    char *text;
    t_token_list	*head;
	t_AST			*ast_head;
    
    flag = false;
    while (flag == false)
    {
        text = readline(prompt);
        add_history(text);
        head = tokenize_cmd(text);
	    ast_head = create_ast(&head);
	    clean_tokens(&head);
	    clean_ast(ast_head);
		free(text);
    }
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