/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-est145 <juan-est145@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 11:34:35 by juan-est145       #+#    #+#             */
/*   Updated: 2024/04/24 14:09:08 by juan-est145      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "minishell.h"

int	main(void)
{
	t_token_list	*head;
	t_AST			*ast_head;
	char			*string;

	string = "echo \"Hola caracola\" | grep Hola | wc -l > prueba.txt";
	head = tokenize_cmd(string);
	ast_head = create_ast(&head);
	clean_tokens(&head);
	clean_ast(ast_head);
	return (0);
}
//"echo \"Hola caracola\" | grep Hola | wc -l"
// "echo \"Hola caracola\" | grep Hola | wc -l > prueba.txt"