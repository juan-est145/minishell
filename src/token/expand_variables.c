/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juestrel <juestrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:04:38 by juestrel          #+#    #+#             */
/*   Updated: 2024/06/05 16:25:26 by juestrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../libft/libft.h"

static char				*search_env_value(char *text, unsigned int *env_i,
							t_lst_env **lst_env,
							t_expand_struct *expand_struct);
static char				*append_env_value(char *env_value, char *text,
							unsigned int env_start, unsigned int env_end);
static t_expand_struct	init_expand_struct(t_pipex *str_pipe);
char					*empty_or_exit_status(char *text, unsigned int *env_i,
							unsigned int i, t_expand_struct *expand_struct);

char	*find_env_var(char *text, t_lst_env **lst_env, t_pipex *str_pipe)
{
	t_expand_struct	expand_struct;
	unsigned int	i;

	expand_struct = init_expand_struct(str_pipe);
	i = 0;
	while (text[i] != '\0')
	{
		expand_struct.empty_env = false;
		if (text[i] == '\'' || text[i] == '\"')
			set_delimiter(&expand_struct.delimiter, text, i);
		if (text[i] == '$' && ft_isspace(text[i + 1]) == false && text[i
				+ 1] != '\0' && expand_struct.delimiter != '\'')
		{
			expand_struct.temp = search_env_value(text, &i, lst_env,
					&expand_struct);
			free(text);
			text = expand_struct.temp;
			if (expand_struct.empty_env == true)
				continue ;
		}
		i++;
	}
	return (text);
}

static t_expand_struct	init_expand_struct(t_pipex *str_pipe)
{
	t_expand_struct	expand_struct;

	expand_struct.delimiter = '\0';
	expand_struct.temp = NULL;
	expand_struct.empty_env = false;
	expand_struct.str_pipe = str_pipe;
	expand_struct.temp_env = NULL;
	return (expand_struct);
}

static char	*search_env_value(char *text, unsigned int *env_i,
		t_lst_env **lst_env, t_expand_struct *expand_struct)
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
	expand_struct->temp_env = env;
	return (empty_or_exit_status(text, env_i, i, expand_struct));
}

char	*empty_or_exit_status(char *text, unsigned int *env_i, unsigned int i,
		t_expand_struct *expand_struct)
{
	char	*result;
	char	*pipex_return_status;
	t_pipex	*str_pipe;

	pipex_return_status = NULL;
	str_pipe = expand_struct->str_pipe;
	if (strncmp(expand_struct->temp_env, "$?",
			ft_strlen(expand_struct->temp_env)) == 0)
	{
		pipex_return_status = ft_itoa(str_pipe->return_cmd_status);
		result = append_env_value(pipex_return_status, text, *env_i, i);
		free(pipex_return_status);
		free(expand_struct->temp_env);
		expand_struct->temp_env = NULL;
		return (result);
	}
	result = append_env_value("", text, *env_i, i);
	expand_struct->empty_env = true;
	free(expand_struct->temp_env);
	expand_struct->temp_env = NULL;
	return (result);
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
