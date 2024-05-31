/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_ast.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juestrel <juestrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:14:04 by juestrel          #+#    #+#             */
/*   Updated: 2024/05/31 16:45:10 by juestrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESS_AST_H
# define PROCESS_AST_H

# include <sys/types.h>

typedef struct s_ast		t_ast;
typedef struct s_lst_env	t_lst_env;

typedef enum e_process_cmd
{
	SIMPLE_CMD,
	ENTRY_PIPE,
	EXIT_PIPE,
	MIDDLE_PIPE,
}							t_process_cmd;

pid_t						read_cmd(t_ast *node, t_pipex *str_pipe,
								char *prompt, t_process_cmd type_cmd);
void						read_pipe(t_ast *node, t_lst_env **lst_env,
								t_pipex *str_pipe, char *prompt);
#endif
