/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-est145 <juan-est145@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 13:00:57 by juan-est145       #+#    #+#             */
/*   Updated: 2024/05/14 13:03:02 by juan-est145      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../libft/libft.h"

static char	set_env_delimiter(char delimiter);
static char	*process_env(char *text, unsigned int env_i, t_lst_env **lst_env);

void	find_env_var(char *text, t_lst_env **lst_env)
{
	unsigned int	i;
	char			delimiter;

	i = 0;
	delimiter = '\0';
	while (text[i] != '\0')
	{
		if (text[i] == '\'')
			delimiter = set_env_delimiter(delimiter);
		if (text[i] == '$' && ft_isspace(text[i + 1]) \
		== false && text[i + 1] != '\0' && delimiter == '\0')
			process_env(text, i, lst_env);
		i++;
	}
}

static char	set_env_delimiter(char delimiter)
{
	if (delimiter == '\0')
		return ('\'');
	return ('\0');
}

static char	*process_env(char *text, unsigned int env_i, t_lst_env **lst_env)
{
	unsigned int	i;
	char			*env;
	char			*result;
	char			**env_path;

	i = env_i;
	while (text[i] != '\0' && ft_isspace(text[i]) == false)
		i++;
	env = ft_substr(text, 0, i - env_i);
	env_path = search_lst_env(env + 1, lst_env);
	if (env_path != NULL)
	{
		result = ft_substr(env_path[1], 0, ft_strlen(env_path[1]));
		free_matrix(env_path);
		free(env);
	}
	return (result);
}
