/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-est145 <juan-est145@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 11:34:35 by juan-est145       #+#    #+#             */
/*   Updated: 2024/04/19 16:02:53 by juan-est145      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "minishell.h"

int	main(void)
{
	unsigned int i = 0;
	unsigned int start_index = 0;
	char *string = "echo  \"Ho     ' l'a\"";
	size_t	length;
	t_token_list	*token_list = NULL;
	char delimiter = '\0';
	
	token_list = malloc(sizeof(token_list));
	if (*string == '\0')
		return (free(token_list), 1);
		
	while (ft_isspace(*string) == true && *string != '\0')
		string++;
	length = ft_strlen(string);
	while (i <= length && string[start_index] != '\0')
	{
		if ((ft_isspace(string[i]) == true && delimiter == '\0')|| string[i] == '\0')
		{
			token_list->token = ft_substr(string, start_index, i - start_index);
			start_index = i + 1;
		}
		else if (string[i] == '\"' || string[i] == '\'')
		{
			if (delimiter == '\0')
				delimiter = string[i];
			else if (delimiter == string[i])
				delimiter = '\0';
		}
		i++;
	}
	if (token_list != NULL)
		free(token_list);
	return (0);
}
