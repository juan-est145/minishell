/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_miguel.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:38:24 by user42            #+#    #+#             */
/*   Updated: 2024/04/24 15:35:35 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <unistd.h>
#include <readline/history.h>
#include <stdlib.h>
#include "prueba.h"

int main (int argc, char **argv, char **env)
{
    (void)argc;
    (void)argv;
    //printf("%s", ft_getenv(env, "LOGNAME="));
    t_lst_env lst_env;
    bool flag = false;
    int i = 0;
    char *text;
    char *prompt = ft_getenv(env, "LOGNAME=");
    prompt = ft_strjoin(prompt, "$ ");
    while (i++ < 1500)
		printf("\n");
	init_lst_env(env, &lst_env);
    while (flag == false)
    {
        text = readline(prompt);
        add_history(text);
         if (ft_strncmp(text, "pwd\0", 4) == 0 || ft_strncmp(text, "pwd ", 4) == 0)
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
        }
		free(text);
    }
	free_lst_env (&lst_env);
	free(prompt);
    return(0);
}