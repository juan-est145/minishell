/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfuente- <mfuente-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 16:20:41 by mfuente-          #+#    #+#             */
/*   Updated: 2024/05/27 16:20:42 by mfuente-         ###   ########.fr       */
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
