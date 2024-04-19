/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-est145 <juan-est145@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 11:34:35 by juan-est145       #+#    #+#             */
/*   Updated: 2024/04/19 14:06:14 by juan-est145      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "minishell.h"

int	main(void)
{
	unsigned int i = 0;
	unsigned int start_index = 0;
	char *string = "echoHo'la\"";
	const size_t	length = ft_strlen(string);
	/*char *string = "echo";*/
	t_token_list	*token_list = NULL;
	
	token_list = malloc(sizeof(token_list));
	if (*string == '\0')
		return (free(token_list), 1);
	while (i <= length && string[start_index] != '\0')
	{
		while (ft_isspace(*string) == true && *string != '\0')
			string++;
		if (ft_isspace(string[i]) == true || string[i] == '\0')
		{
			token_list->token = ft_substr(string, start_index, i);
			start_index = i + 1;
		}
		else if (string[i] == '\"' || string[i] == '\'')
		{
			char delimiter = string[i];
			i++;
			while (string[i] != delimiter && i <= length)
			{
				i++;
			}
			token_list->token = ft_substr(string, start_index, i);
			start_index = i + 1;
		}
		i++;
	}
	if (token_list != NULL)
		free(token_list);
	return (0);
}
