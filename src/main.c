/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-est145 <juan-est145@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 11:34:35 by juan-est145       #+#    #+#             */
/*   Updated: 2024/04/22 16:56:05 by juan-est145      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "minishell.h"

int	main(void)
{
	char	*string;

	string = "echo  \"Ho     ' l'a\"";
	tokenize_cmd(string);
	return (0);
}
