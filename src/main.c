/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-est145 <juan-est145@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 11:34:35 by juan-est145       #+#    #+#             */
/*   Updated: 2024/04/22 19:43:24 by juan-est145      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "minishell.h"

int	main(void)
{
	t_token_list	*head;
	char			*string;

	string = "echo \"Hola caracola\" | grep Hola | wc -l";
	head = tokenize_cmd(string);
	create_ast(&head);
	clean_tokens(&head);
	return (0);
}
