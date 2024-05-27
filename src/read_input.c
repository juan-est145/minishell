/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-est145 <juan-est145@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 14:38:51 by juan-est145       #+#    #+#             */
/*   Updated: 2024/05/24 14:52:41 by juan-est145      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"

char	*read_input(char *prompt, t_lst_env **lst_env)
{
	char	*text;

	text = readline(prompt);
	if (text == NULL)
	{
		free(prompt);
		free_copie_env(lst_env);
		free_lst_env(*lst_env);
		exit(0);
	}
	add_history(text);
	return (text);
}
