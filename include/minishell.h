/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juestrel <juestrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 16:20:00 by mfuente-          #+#    #+#             */
/*   Updated: 2024/06/05 16:31:33 by juestrel         ###   ########.fr       */
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

#endif
