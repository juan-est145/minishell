/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juestrel <juestrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:04:38 by juestrel          #+#    #+#             */
/*   Updated: 2024/05/23 13:04:45 by juestrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../libft/libft.h"

static char	*search_env_value(char *text, unsigned int *env_i,
				t_lst_env **lst_env, bool *empty_env);
static char	*append_env_value(char *env_value, char *text,
				unsigned int env_start, unsigned int env_end);

char	*find_env_var(char *text, t_lst_env **lst_env)
{
	unsigned int	i;
	char			delimiter;
	char			*temp;
	bool			empty_env;

	i = 0;
	delimiter = '\0';
	temp = NULL;
	while (text[i] != '\0')
	{
		empty_env = false;
		if (text[i] == '\'' || text[i] == '\"')
			set_delimiter(&delimiter, text, i);
		if (text[i] == '$' && ft_isspace(text[i + 1]) \
		== false && text[i + 1] != '\0' && delimiter != '\'')
		{
			temp = search_env_value(text, &i, lst_env, &empty_env);
			free(text);
			text = temp;
			if (empty_env == true)
				continue ;
		}
		i++;
	}
	return (text);
}

static char	*search_env_value(char *text, unsigned int *env_i,
		t_lst_env **lst_env, bool *empty_env)
{
	unsigned int	i;
	char			*env;
	char			*result;
	char			**env_path;

	i = find_last_env_index(text, *env_i);
	env = ft_substr(text, *env_i, i - (*env_i));
	env_path = search_lst_env(env + 1, lst_env);
	if (env_path != NULL)
	{
		result = ft_substr(env_path[1], 0, ft_strlen(env_path[1]));
		free_matrix(env_path);
		free(env);
		env = result;
		result = append_env_value(result, text, *env_i, i);
		*env_i += ft_strlen(env) - 1;
		free(env);
		return (result);
	}
	result = append_env_value("", text, *env_i, i);
	*empty_env = true;
	return (free(env), result);
}

static char	*append_env_value(char *env_value, char *text,
		unsigned int env_start, unsigned int env_end)
{
	char	*result;
	char	*temp;

	result = ft_substr(text, 0, env_start);
	temp = result;
	result = ft_strjoin(result, env_value);
	free(temp);
	temp = result;
	result = ft_strjoin(result, &text[env_end]);
	free(temp);
	return (result);
}