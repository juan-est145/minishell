/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-est145 <juan-est145@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:12:47 by juestrel          #+#    #+#             */
/*   Updated: 2024/05/24 14:50:01 by juan-est145      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "builtings.h"
# include "token.h"
# include "parse.h"
# include "pipes.h"
# include "process_ast.h"
# include "errors.h"
# include "set_up.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <errno.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# define RED     	"\x1b[31m"
# define GREEN   	"\x1b[32m"
# define BLUE    	"\x1b[34m"
# define BOLD		"\033[1m"
# define RESET   	"\x1b[0m"

char	*read_input(char *prompt, t_lst_env **lst_env);
#endif
